
#include <linux/module.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/pwm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/earlysuspend.h>
#include <linux/io.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/sec_interface.h>
#include <linux/i2c/interface_i2c.h>

extern struct class *sec_class;
static int interface_enable;
static bool interface_probe = true;

static const struct i2c_device_id sec_interface_id[] = {
    {"sec_interface", 0},
    {}
};

MODULE_DEVICE_TABLE(i2c, sec_interface_id);

struct interface_node {
    struct file *owner;
    uint8_t pin;
};

static struct kmem_cache *interface_area_cachep __read_mostly;

static int tca6416_read_reg(struct i2c_client *client, int reg, uint16_t *val)
{
    int err = 0;
    int retry = 3;

    if ((client == NULL) || !(interface_enable == 1)
        || !interface_probe) {
        printk(KERN_ERR "[I/O] Interface is not enabled. %d\n",
               __LINE__);
        return -ENODEV;
    }

    while (retry--) {
        err = i2c_smbus_read_word_data(client, reg << 1);

        if (err >= 0) {
            *val = (uint16_t) err;
            return 0;
        }
        printk(KERN_ERR "[I/O] %s %d %d i2c transfer error\n",
               __func__, __LINE__, err);
        mdelay(10);
    }
    return err;
}

static int tca6416_write_reg(struct i2c_client *client, int reg, uint16_t val)
{
    int err = 0;
    int retry = 3;

    if ((client == NULL) || !(interface_enable == 1)
        || !interface_probe) {
        printk(KERN_ERR "[I/O] Interface is not enabled. %d\n",
               __LINE__);
        return -ENODEV;
    }

    while (retry--) {
        err = i2c_smbus_write_word_data(client,
                reg << 1, val);

        if (err >= 0)
            return 0;

        printk(KERN_DEBUG "[I/O] %s %d %d i2c transfer error\n",
               __func__, __LINE__, err);
        mdelay(10);
    }
    return err;
}

static int tca6416_gpio_direction_input(struct gpio_chip *gc, unsigned off)
{
    struct interface_i2c *chip;
    uint16_t reg_val;
    int ret = 0;

    chip = container_of(gc, struct interface_i2c, gpio_chip);

    mutex_lock(&chip->lock);
    reg_val = chip->reg_direction | (1u << off);

    ret = tca6416_write_reg(chip->client, TCA6416_DIRECTION, reg_val);
    if (ret)
        goto exit;

    chip->reg_direction = reg_val;
    ret = 0;
exit:
    mutex_unlock(&chip->lock);
    return ret;
}


static int tca6416_gpio_direction_output(struct gpio_chip *gc,
        unsigned off, int val)
{
    struct interface_i2c *chip;
    uint16_t reg_val;
    int ret = 0;

    chip = container_of(gc, struct interface_i2c, gpio_chip);

    mutex_lock(&chip->lock);
    /* set output level */
    if (val)
        reg_val = chip->reg_output | (1u << off);
    else
        reg_val = chip->reg_output & ~(1u << off);

    ret = tca6416_write_reg(chip->client, TCA6416_OUTPUT, reg_val);
    if (ret)
        goto exit;

    chip->reg_output = reg_val;

    /* then direction */
    reg_val = chip->reg_direction & ~(1u << off);
    ret = tca6416_write_reg(chip->client, TCA6416_DIRECTION, reg_val);
    if (ret)
        goto exit;

    chip->reg_direction = reg_val;
    ret = 0;
exit:
    mutex_unlock(&chip->lock);
    return ret;
}

static int tca6416_gpio_get_value(struct gpio_chip *gc, unsigned off)
{
    struct interface_i2c *chip;
    uint16_t reg_val;
    int ret = 0;

    chip = container_of(gc, struct interface_i2c, gpio_chip);

    mutex_lock(&chip->lock);
    ret = tca6416_read_reg(chip->client, TCA6416_INPUT, &reg_val);
    mutex_unlock(&chip->lock);
    if (ret < 0) {
        /* NOTE:  diagnostic already emitted; that's all we should
         * do unless gpio_*_value_cansleep() calls become different
         * from their nonsleeping siblings (and report faults).
         */
        return 0;
    }

    return (reg_val & (1u << off)) ? 1 : 0;
}

static void tca6416_gpio_set_value(struct gpio_chip *gc, unsigned off, int val)
{
    struct interface_i2c *chip;
    uint16_t reg_val;
    int ret = 0;

    chip = container_of(gc, struct interface_i2c, gpio_chip);

    mutex_lock(&chip->lock);
    if (val)
        reg_val = chip->reg_output | (1u << off);
    else
        reg_val = chip->reg_output & ~(1u << off);

    ret = tca6416_write_reg(chip->client, TCA6416_OUTPUT, reg_val);
    if (ret)
        goto exit;

    chip->reg_output = reg_val;
exit:
    mutex_unlock(&chip->lock);
}

static int __devinit device_tca6416_init(struct interface_i2c *chip, int invert)
{
    int ret;

    ret = tca6416_read_reg(chip->client, TCA6416_OUTPUT, &chip->reg_output);
    if (ret)
        goto out;

    printk(KERN_DEBUG "[I/O] TCA6416A OUTPUT: %04x\n", chip->reg_output);

    ret = tca6416_read_reg(chip->client, TCA6416_DIRECTION,
                   &chip->reg_direction);
    if (ret)
        goto out;

    printk(KERN_DEBUG "[I/O] TCA6416A DIRECTION: %04x\n", chip->reg_direction);

    /* set platform specific polarity inversion */
    ret = tca6416_write_reg(chip->client, TCA6416_INVERT, invert);
    if (ret)
        goto out;
    return 0;
out:
    return ret;
}

static void tca6416_setup_gpio(struct interface_i2c *chip, int gpios)
{
    struct gpio_chip *gc;

    gc = &chip->gpio_chip;

    gc->direction_input  = tca6416_gpio_direction_input;
    gc->direction_output = tca6416_gpio_direction_output;
    gc->get = tca6416_gpio_get_value;
    gc->set = tca6416_gpio_set_value;
    gc->can_sleep = 1;

    gc->base = chip->pdata->gpio_start;
    gc->ngpio = gpios;
    gc->label = chip->client->name;
    gc->dev = &chip->client->dev;
    gc->owner = THIS_MODULE;
    gc->names = chip->name;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static int sec_interface_early_suspend(struct early_suspend *h)
{
    struct interface_i2c *chip = container_of(h, struct interface_i2c, early_suspend);

    disable_irq(chip->irq);

    interface_enable = 0;
    printk(KERN_DEBUG "[I/O] sec_interface_early_suspend");

    if (interface_enable < 0) {
        printk(KERN_DEBUG "[I/O] ---%s---interface_enable: %d\n",
               __func__, interface_enable);
        return 0;
    }

    /* disable ldo18 */
    chip->pdata->led_power_on(0);

    /* disable ldo11 */
    chip->pdata->power_on(0);

    return 0;
}

static int sec_interface_late_resume(struct early_suspend *h)
{
    struct interface_i2c *chip =
        container_of(h, struct interface_i2c, early_suspend);

    printk(KERN_DEBUG "[I/O] sec_interface_late_resume");

    chip->pdata->power_on(1);
    msleep(10);
    /* enable ldo11 */
    chip->pdata->power_on(1);

    if (interface_enable < 0) {
        printk(KERN_DEBUG "[I/O] ---%s---interface_enable: %d\n",
               __func__, interface_enable);
        return 0;
    }
    msleep(50);
    interface_enable = 1;

    enable_irq(chip->irq);
    return 0;
}
#endif

static int tca6416_gpio_to_irq(struct gpio_chip *gc, unsigned off)
{
    struct interface_i2c *chip;

    chip = container_of(gc, struct interface_i2c, gpio_chip);
    return chip->irq_base + off;
}

static void tca6416_irq_mask(struct irq_data *d)
{
    struct interface_i2c *chip = irq_data_get_irq_chip_data(d);

    chip->irq_mask &= ~(1 << (d->irq - chip->irq_base));
}

static void tca6416_irq_unmask(struct irq_data *d)
{
    struct interface_i2c *chip = irq_data_get_irq_chip_data(d);

    chip->irq_mask |= 1 << (d->irq - chip->irq_base);
}

static void tca6416_irq_bus_lock(struct irq_data *d)
{
    struct interface_i2c *chip = irq_data_get_irq_chip_data(d);

    mutex_lock(&chip->irq_lock);
}

static void tca6416_irq_bus_sync_unlock(struct irq_data *d)
{
    struct interface_i2c *chip = irq_data_get_irq_chip_data(d);
    uint16_t new_irqs;
    uint16_t level;

    /* Look for any newly setup interrupt */
    new_irqs = chip->irq_trig_fall | chip->irq_trig_raise;
    new_irqs &= ~chip->reg_direction;

    while (new_irqs) {
        level = __ffs(new_irqs);
        tca6416_gpio_direction_input(&chip->gpio_chip, level);
        new_irqs &= ~(1 << level);
    }

    mutex_unlock(&chip->irq_lock);
}

static int tca6416_irq_set_type(struct irq_data *d, unsigned int type)
{
    struct interface_i2c *chip = irq_data_get_irq_chip_data(d);
    uint16_t level = d->irq - chip->irq_base;
    uint16_t mask = 1 << level;

    if (!(type & IRQ_TYPE_EDGE_BOTH)) {
        dev_err(&chip->client->dev, "irq %d: unsupported type %d\n",
            d->irq, type);
        return -EINVAL;
    }

    if (type & IRQ_TYPE_EDGE_FALLING)
        chip->irq_trig_fall |= mask;
    else
        chip->irq_trig_fall &= ~mask;

    if (type & IRQ_TYPE_EDGE_RISING)
        chip->irq_trig_raise |= mask;
    else
        chip->irq_trig_raise &= ~mask;

    return 0;
}

static struct irq_chip tca6416_irq_chip = {
    .name			= "tca6416",
    .irq_mask		= tca6416_irq_mask,
    .irq_unmask		= tca6416_irq_unmask,
    .irq_bus_lock		= tca6416_irq_bus_lock,
    .irq_bus_sync_unlock	= tca6416_irq_bus_sync_unlock,
    .irq_set_type		= tca6416_irq_set_type,
};

static uint16_t tca6416_irq_pending(struct interface_i2c *chip)
{
    uint16_t cur_stat;
    uint16_t old_stat;
    uint16_t pending;
    uint16_t trigger;
    int ret = 0;

    ret = tca6416_read_reg(chip->client, TCA6416_INPUT, &cur_stat);
    if (ret)
        return 0;

    /* Remove output pins from the equation */
    cur_stat &= chip->reg_direction;

    old_stat = chip->irq_stat;
    trigger = (cur_stat ^ old_stat) & chip->irq_mask;

    if (!trigger)
        return 0;

    chip->irq_stat = cur_stat;

    pending = (old_stat & chip->irq_trig_fall) |
          (cur_stat & chip->irq_trig_raise);
    pending &= trigger;

    return pending;
}

static irqreturn_t tca6416_irq_handler(int irq, void *devid)
{
    struct interface_i2c *chip = devid;
    uint16_t pending;
    uint16_t level;

    pending = tca6416_irq_pending(chip);

    if (!pending)
        return IRQ_HANDLED;

    do {
        level = __ffs(pending);
        handle_nested_irq(level + chip->irq_base);

        pending &= ~(1 << level);
    } while (pending);

    return IRQ_HANDLED;
}

static int tca6416_irq_setup(struct interface_i2c *chip,
                 const struct i2c_device_id *id)
{
    struct i2c_client *client = chip->client;
    struct interface_platform_data *pdata = client->dev.platform_data;
    int ret = 0;

    if (pdata->irq_base != -1) {
        int lvl;

        ret = tca6416_read_reg(chip->client, TCA6416_INPUT, &chip->irq_stat);
        if (ret)
            goto out_failed;

        printk(KERN_DEBUG "[I/O] TCA6416A INPUT: %04x\n", chip->irq_stat);

        /*
         * There is no way to know which GPIO line generated the
         * interrupt.  We have to rely on the previous read for
         * this purpose.
         */
        chip->irq_stat &= chip->reg_direction;
        chip->irq_base = pdata->irq_base;
        mutex_init(&chip->irq_lock);

        for (lvl = 0; lvl < chip->gpio_chip.ngpio; lvl++) {
            int irq = lvl + chip->irq_base;

            irq_set_chip_data(irq, chip);
            irq_set_chip(irq, &tca6416_irq_chip);
            irq_set_nested_thread(irq, true);
#ifdef CONFIG_ARM
            set_irq_flags(irq, IRQF_VALID);
#else
            irq_set_noprobe(irq);
#endif
        }

        ret = request_threaded_irq(client->irq, NULL, tca6416_irq_handler,
                                   IRQF_TRIGGER_RISING |
                                   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
                                   dev_name(&client->dev), chip);
        if (ret < 0) {
            dev_err(&client->dev, "failed to request irq %d\n",
                client->irq);
            interface_probe = false;
            goto out_failed;
        }

        chip->gpio_chip.to_irq = tca6416_gpio_to_irq;
    }

    return 0;

out_failed:
    dev_err(&client->dev, "failed to init irq %d, err=%d\n",
        client->irq, ret);
    chip->irq_base = -1;
    return ret;
}

static void tca6416_irq_teardown(struct interface_i2c *chip)
{
    if (chip->irq_base != -1)
        free_irq(chip->client->irq, chip);
}

static ssize_t tca6416_input_reg_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret;
    uint16_t reg = 0;
    struct interface_i2c *it_i2c = dev_get_drvdata(dev);

    ret = tca6416_read_reg(it_i2c->client, TCA6416_INPUT, &reg);
    if(ret)
        pr_info("[I/O] %s: input register read error: %d\n", __func__, ret);

    ret = sprintf(buf, "%04x\n", reg);
    pr_info("[I/O] %s: input register=%d\n", __func__, reg);

    return ret;
}

static ssize_t tca6416_test_pins(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret;
    int i = 0;
    uint16_t reg;
    struct interface_i2c *chip = dev_get_drvdata(dev);
    struct pwm_device *pwm = NULL;

    pwm = pwm_request(129, "sec_interface_pwm");
    if(pwm == NULL) {

        pr_info("[I/O] %s: request PWM %d failed", __func__, 0);
    } else {
        pr_info("[I/O] %s: request PWM %d success", __func__, 0);
        pwm_config(pwm, HZ_TO_NS(200), HZ_TO_NS(400));
        pwm_enable(pwm);
    }


    for(;i<TCA6416_PINS;i++) {
        ret = gpio_request(INTERFACE_GPIO(i), "sec_interface");
        if(ret) {
            pr_info("[I/O] %s: request gpio %d error: %d\n", __func__, INTERFACE_GPIO(i), ret);
            continue;
        }

        pr_info("[I/O] %s: request gpio %d successed\n", __func__, INTERFACE_GPIO(i));

        gpio_direction_output(INTERFACE_GPIO(i), 1);
        gpio_free(INTERFACE_GPIO(i));
    }
    ret = tca6416_read_reg(chip->client, TCA6416_OUTPUT, &reg);
    if(ret)
        pr_info("[I/O] %s: output register read error: %d\n", __func__, ret);

    ret = sprintf(buf, "%04x\n", reg);
    pr_info("[I/O] %s: output register=%d\n", __func__, reg);

    return ret;
}

static DEVICE_ATTR(input_reg, S_IRUGO | S_IWUSR | S_IWGRP,
           tca6416_input_reg_show, NULL);
static DEVICE_ATTR(test_pin, S_IRUGO | S_IWUSR | S_IWGRP,
           tca6416_test_pins, NULL);

static struct attribute *interface_attributes[] = {
    &dev_attr_input_reg.attr,
    &dev_attr_test_pin.attr,
    NULL,
};

static struct attribute_group interface_attr_group = {
    .attrs = interface_attributes,
};

static int interface_open(struct inode *inode, struct file *file)
{
    struct interface_node *idata;
    nonseekable_open(inode, file);

    idata = kmem_cache_zalloc(interface_area_cachep, GFP_KERNEL);
    if (unlikely(!idata))
        return -ENOMEM;

    idata->pin = 0;

    return 0;
}

static int interface_release(struct inode *ignored, struct file *file)
{
    struct interface_node *idata = file->private_data;

    if(idata->pin > 0) {
        gpio_direction_input(idata->pin);
        gpio_free(idata->pin);
    }

    kmem_cache_free(interface_area_cachep, idata);
    return 0;
}


static long interface_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct interface_node *idata = file->private_data;
    long ret = -EINVAL;
    struct interface_request req;

    switch (cmd) {
    case INTERFACE_IOCTL_REQUEST:

        if(idata->pin != 0) {
            printk(KERN_ERR "[I/O]: This context is busy.\n");
            return -EINVAL;
        }

        if (unlikely(copy_from_user(&req, (void __user *)arg, sizeof(req)))) {

            printk(KERN_ERR "[I/O]: can not copy user data.\n");
            return -EFAULT;
        }

        if((req.pin < INTERFACE_GPIO(0)) || (req.pin >= INTERFACE_GPIO(TCA6416_PINS))) {
            printk(KERN_ERR "[I/O]: %d Pin is invalid.\n", req.pin);
            return -EINVAL;
        }

        ret = gpio_request(INTERFACE_GPIO(req.pin), "sec_interface");
        if(ret) {
            pr_info("[I/O]: request gpio %d error: %ld\n", INTERFACE_GPIO(req.pin), ret);
            return ret;
        }

        if(req.mode == INTERFACE_INPUT) {
            ret = gpio_direction_input(INTERFACE_GPIO(req.pin));
        } else {
            ret = gpio_direction_output(INTERFACE_GPIO(req.pin), req.default_value);
        }

        if(ret) {
            pr_info("[I/O]: set gpio %d to mode(%d) error: %ld\n", INTERFACE_GPIO(req.pin), req.mode, ret);
            gpio_free(INTERFACE_GPIO(req.pin));
            return ret;
        }

        idata->pin = INTERFACE_GPIO(req.pin);
        break;
    default:
        break;
    }

    return ret;
}


static ssize_t interface_read(struct file *file, char __user *buf,
               size_t len, loff_t *pos)
{
    struct interface_node *idata = file->private_data;
    int ret = 0;
    uint8_t val;

    if(idata->pin == 0) {
        return -EINVAL;
    }

    val = gpio_get_value(idata->pin);
    ret = copy_to_user(buf, &val, sizeof(val));
    if(ret == 0) {
        return sizeof(val);
    }

    return -EIO;
}

static ssize_t interface_write(struct file *file, const char __user *buf,
               size_t len, loff_t *pos)
{
    struct interface_node *idata = file->private_data;
    int ret = 0;
    uint8_t val;

    if(idata->pin == 0) {
        return -EINVAL;
    }

    if(len != sizeof(uint8_t)) {
        return -EINVAL;
    }

    ret = copy_from_user(&val, buf, len);

    val = gpio_get_value(idata->pin);
    ret = copy_to_user(buf, &val, sizeof(val));
    if(ret == 0) {
        return sizeof(val);
    }

    return -EIO;
}


static unsigned interface_poll(struct file *file, struct poll_table_struct *wait)
{
    return 0;
}

static struct file_operations interface_fops = {
    .owner = THIS_MODULE,
    .open = interface_open,
    .release = interface_release,
    .read = interface_read,
    .write = interface_write,
    .poll = interface_poll,
    .llseek = no_llseek,
    .unlocked_ioctl = interface_ioctl,
    .compat_ioctl = interface_ioctl,
};

static struct miscdevice interface_misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "sec_interface",
    .fops = &interface_fops,
};

static int i2c_interface_probe(struct i2c_client *client,
    const struct i2c_device_id *id)
{
    struct interface_platform_data *pdata = client->dev.platform_data;
    struct interface_i2c *it_i2c;
    unsigned char data;
    int ret;

    if (pdata == NULL) {

        uint16_t reg_output = 0, reg_direction = 0;

        ret = tca6416_read_reg(client, TCA6416_OUTPUT, &reg_output);

        printk(KERN_DEBUG "[I/O] TCA6416A OUTPUT: %04x, ret: %d\n", reg_output,ret);

        ret = tca6416_read_reg(client, TCA6416_DIRECTION,
                       &reg_direction);

        printk(KERN_DEBUG "[I/O] TCA6416A TCA6416_DIRECTION: %04x, ret: %d\n", reg_direction,ret);

        printk(KERN_ERR "%s: no pdata\n", __func__);
        return -ENODEV;
    }

    printk(KERN_DEBUG "[I/O] SCL: %d, SDA: %d, INT: %d, GPIO Base: %x, IRQ Base: %x, Pins: %d\n",
           pdata->gpio_scl,
           pdata->gpio_sda,
           pdata->gpio_int,
           pdata->gpio_start,
           pdata->irq_base,
           TCA6416_PINS
           );

    /*Check I2C functionality */
    ret = i2c_check_functionality(client->adapter, I2C_FUNC_I2C);
    if (ret == 0) {
        printk(KERN_ERR "[I/O] No I2C functionality found\n");
        ret = -ENODEV;
        return ret;
    }

    /*Obtain kernel memory space for touchkey i2c */
    it_i2c = kzalloc(sizeof(struct interface_i2c), GFP_KERNEL);
    if (NULL == it_i2c) {
        printk(KERN_ERR "[I/O] failed to allocate it_i2c.\n");
        return -ENOMEM;
    }

    if (pdata == NULL) {
        printk(KERN_ERR "[I/O] no platform data.\n");
        ret = -EINVAL;
        goto out_failed;
    }

    /*it_i2c*/
    it_i2c->pdata = pdata;
    mutex_init(&it_i2c->lock);
    it_i2c->client = client;
    it_i2c->irq = client->irq;
    it_i2c->name = "sec_interface";

    dev_info(&client->dev, "TCA6416 Name: %s\n", client->name);

    /*
    it_i2c->pdata->led_power_on(1);
    msleep(10);
    it_i2c->pdata->power_on(1);
    msleep(50);
    */

    interface_enable = 1;
    data = 1;

    /* initialize cached registers from their original values.
     * we can't share this chip with another i2c master.
     */
    tca6416_setup_gpio(it_i2c, TCA6416_PINS);
    device_tca6416_init(it_i2c, pdata->invert);

    /*sysfs*/
    it_i2c->dev = device_create(sec_class, NULL, 0, NULL, "sec_interface");

    if (IS_ERR(it_i2c->dev)) {
        printk(KERN_ERR "Failed to create device(it_i2c->dev)!\n");
    } else {
        dev_set_drvdata(it_i2c->dev, it_i2c);
        ret = sysfs_create_group(&it_i2c->dev->kobj,
                    &interface_attr_group);
        if (ret) {
            printk(KERN_ERR
                "[I/O]: failed to create sysfs group\n");
        }
    }

    it_i2c->interface_misc = &interface_misc;

    ret = tca6416_irq_setup(it_i2c, id);
    if (ret)
        goto out_failed;

    ret = gpiochip_add(&it_i2c->gpio_chip);
    if (ret) {
        dev_info(&client->dev, "tca6416 add gpio failed, err = %d\n", ret);
        goto out_failed_irq;
    }

    i2c_set_clientdata(client, it_i2c);
#ifdef CONFIG_HAS_EARLYSUSPEND
    it_i2c->early_suspend.suspend =
        (void *)sec_interface_early_suspend;
    it_i2c->early_suspend.resume =
        (void *)sec_interface_late_resume;
    register_early_suspend(&it_i2c->early_suspend);
#endif

    device_init_wakeup(&client->dev, 1);
    return 0;

out_failed_irq:
    tca6416_irq_teardown(it_i2c);
out_failed:
    kfree(it_i2c);
    return ret;
}


static int i2c_interface_remove(struct i2c_client *client)
{
    struct interface_i2c *chip = i2c_get_clientdata(client);
    int ret = 0;

    dev_info(&client->dev, "i2c interface removed.\n");

    ret = gpiochip_remove(&chip->gpio_chip);
    if (ret) {
        dev_err(&client->dev, "%s failed, %d\n",
                "gpiochip_remove()", ret);
        return ret;
    }

#ifdef CONFIG_HAS_EARLYSUSPEND
    unregister_early_suspend(&chip->early_suspend);
#endif

    tca6416_irq_teardown(chip);

    kfree(chip);
    return 0;
}

#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND)
static int tca6416_suspend(struct device *dev)
{
        struct i2c_client *client = to_i2c_client(dev);
        struct interface_i2c *chip = i2c_get_clientdata(client);

        dev_info(&client->dev, "tca6416_suspend\n");

        if (device_may_wakeup(dev))
                enable_irq_wake(chip->irq);

        return 0;
}

static int tca6416_resume(struct device *dev)
{
        struct i2c_client *client = to_i2c_client(dev);
        struct interface_i2c *chip = i2c_get_clientdata(client);

        dev_info(&client->dev, "tca6416_resume\n");

        if (device_may_wakeup(dev))
                disable_irq_wake(chip->irq);

        return 0;
}

static SIMPLE_DEV_PM_OPS(tca6416_dev_pm_ops,
                          tca6416_suspend, tca6416_resume);
#endif

struct i2c_driver interface_i2c_driver = {
    .driver = {
        .name = "sec_interface_driver",
#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND)
        .pm   = &tca6416_dev_pm_ops,
#endif
    },
    .id_table = sec_interface_id,
    .probe = i2c_interface_probe,
    .remove = i2c_interface_remove,
};

static int __init interface_init(void)
{
    int ret = 0;

    interface_area_cachep = kmem_cache_create("interface_area_cache",
                      sizeof(struct interface_node),0, 0, NULL);
    if (unlikely(!interface_area_cachep)) {
        printk(KERN_ERR "[I/O]: failed to create slab cache\n");
        return -ENOMEM;
    }

    ret = misc_register(&interface_misc);
    if (unlikely(ret)) {
        printk(KERN_ERR "[I/O]: failed to register misc device!\n");
    }

    ret = i2c_add_driver(&interface_i2c_driver);

    if (ret) {
        printk(KERN_ERR
           "[I/O] registration failed, module not inserted.ret= %d\n",
           ret);
    }

    return ret;
}

static void __exit interface_exit(void)
{
    int ret;
    printk(KERN_DEBUG "[I/O] %s\n", __func__);

    kmem_cache_destroy(interface_area_cachep);
    i2c_del_driver(&interface_i2c_driver);

    ret = misc_deregister(&interface_misc);
    if (unlikely(ret))
        printk(KERN_ERR "[I/O]: failed to unregister misc device!\n");
}

module_init(interface_init);
module_exit(interface_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("@@@");
MODULE_DESCRIPTION("I/O Interface");
