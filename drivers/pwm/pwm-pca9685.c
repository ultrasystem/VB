/*
 * Driver for PCA9685 16-channel 12-bit PWM LED controller
 *
 * Copyright (C) 2013 Steffen Trumtrar <s.trumtrar@pengutronix.de>
 *
 * based on the pwm-twl-led.c driver
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/pwm.h>
#include <linux/delay.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/i2c/interface_pwm.h>

#include <plat/gpio-cfg.h>
#include <mach/gpio-midas.h>

#define PCA9685_MODE1		0x00
#define PCA9685_MODE2		0x01
#define PCA9685_SUBADDR1	0x02
#define PCA9685_SUBADDR2	0x03
#define PCA9685_SUBADDR3	0x04
#define PCA9685_ALLCALLADDR	0x05
#define PCA9685_LEDX_ON_L	0x06
#define PCA9685_LEDX_ON_H	0x07
#define PCA9685_LEDX_OFF_L	0x08
#define PCA9685_LEDX_OFF_H	0x09

#define PCA9685_ALL_LED_ON_L	0xFA
#define PCA9685_ALL_LED_ON_H	0xFB
#define PCA9685_ALL_LED_OFF_L	0xFC
#define PCA9685_ALL_LED_OFF_H	0xFD
#define PCA9685_PRESCALE	0xFE

#define PCA9685_NUMREGS		0xFF
#define PCA9685_MAXCHAN		0x10

#define LED_FULL		(1 << 4)
#define MODE1_SLEEP		(1 << 4)
#define MODE2_INVRT		(1 << 4)
#define MODE2_OUTDRV		(1 << 2)

#define LED_N_ON_H(N)	(PCA9685_LEDX_ON_H + (4 * (N)))
#define LED_N_ON_L(N)	(PCA9685_LEDX_ON_L + (4 * (N)))
#define LED_N_OFF_H(N)	(PCA9685_LEDX_OFF_H + (4 * (N)))
#define LED_N_OFF_L(N)	(PCA9685_LEDX_OFF_L + (4 * (N)))

struct pca9685 {
    struct pwm_chip chip;
    struct regmap *regmap;
    int active_cnt;
};

static inline struct pca9685 *to_pca(struct pwm_chip *chip)
{
    return container_of(chip, struct pca9685, chip);
}

static int pca9685_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
                  int duty_ns, int period_ns)
{
    struct pca9685 *pca = to_pca(chip);
    unsigned long long duty;
    unsigned int reg;

    pr_info("%s: config pwm device: %x (%x)\n", __func__, pwm, pca);

    if (duty_ns < 1) {
        if (pwm->hwpwm >= PCA9685_MAXCHAN)
            reg = PCA9685_ALL_LED_OFF_H;
        else
            reg = LED_N_OFF_H(pwm->hwpwm);

        regmap_write(pca->regmap, reg, LED_FULL);

        return 0;
    }

    if (duty_ns == period_ns) {
        if (pwm->hwpwm >= PCA9685_MAXCHAN)
            reg = PCA9685_ALL_LED_ON_H;
        else
            reg = LED_N_ON_H(pwm->hwpwm);

        regmap_write(pca->regmap, reg, LED_FULL);

        return 0;
    }

    duty = 4096 * (unsigned long long)duty_ns;
    duty = DIV_ROUND_UP_ULL(duty, period_ns);

    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_OFF_L;
    else
        reg = LED_N_OFF_L(pwm->hwpwm);

    regmap_write(pca->regmap, reg, (int)duty & 0xff);

    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_OFF_H;
    else
        reg = LED_N_OFF_H(pwm->hwpwm);

    regmap_write(pca->regmap, reg, ((int)duty >> 8) & 0xf);

    return 0;
}

static int pca9685_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
    struct pca9685 *pca = to_pca(chip);
    unsigned int reg;

    /*
     * The PWM subsystem does not support a pre-delay.
     * So, set the ON-timeout to 0
     */
    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_ON_L;
    else
        reg = LED_N_ON_L(pwm->hwpwm);

    regmap_write(pca->regmap, reg, 0);

    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_ON_H;
    else
        reg = LED_N_ON_H(pwm->hwpwm);

    regmap_write(pca->regmap, reg, 0);

    /*
     * Clear the full-off bit.
     * It has precedence over the others and must be off.
     */
    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_OFF_H;
    else
        reg = LED_N_OFF_H(pwm->hwpwm);

    regmap_update_bits(pca->regmap, reg, LED_FULL, 0x0);

    return 0;
}

static void pca9685_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
    struct pca9685 *pca = to_pca(chip);
    unsigned int reg;

    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_OFF_H;
    else
        reg = LED_N_OFF_H(pwm->hwpwm);

    regmap_write(pca->regmap, reg, LED_FULL);

    /* Clear the LED_OFF counter. */
    if (pwm->hwpwm >= PCA9685_MAXCHAN)
        reg = PCA9685_ALL_LED_OFF_L;
    else
        reg = LED_N_OFF_L(pwm->hwpwm);

    regmap_write(pca->regmap, reg, 0x0);
}

static int pca9685_pwm_request(struct pwm_chip *chip, struct pwm_device *pwm)
{
    struct pca9685 *pca = to_pca(chip);

    pr_info("%s: request pwm device: %x (%x)\n", __func__, pwm, pca);

    if (pca->active_cnt++ == 0)
        return regmap_update_bits(pca->regmap, PCA9685_MODE1,
                      MODE1_SLEEP, 0x0);

    return 0;
}

static void pca9685_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
    struct pca9685 *pca = to_pca(chip);

    if (--pca->active_cnt == 0)
        regmap_update_bits(pca->regmap, PCA9685_MODE1, MODE1_SLEEP,
                   MODE1_SLEEP);
}

static const struct pwm_ops pca9685_pwm_ops = {
    .enable = pca9685_pwm_enable,
    .disable = pca9685_pwm_disable,
    .config = pca9685_pwm_config,
    .request = pca9685_pwm_request,
    .free = pca9685_pwm_free,
    .owner = THIS_MODULE,
};

static struct regmap_config pca9685_regmap_i2c_config = {
    .reg_bits = 8,
    .val_bits = 8,
    .max_register = PCA9685_NUMREGS,
    .cache_type = REGCACHE_NONE,
};

int interface_pwm_enable(bool to_gpios)
{
    int state;

    pr_info("%s:to_gpios=%d\n", __func__, to_gpios);

    /* TOUCH_EN is always an output */
    if (to_gpios) {
        if (gpio_request(GPIO_PWM_SCL, "GPIO_TSP_SCL"))
            pr_err("failed to request gpio(GPIO_PWM_SCL)\n");
        if (gpio_request(GPIO_PWM_SDA, "GPIO_TSP_SDA"))
            pr_err("failed to request gpio(GPIO_PWM_SDA)\n");

        gpio_direction_output(GPIO_PWM_INT, 0);
        s3c_gpio_cfgpin(GPIO_PWM_INT, S3C_GPIO_OUTPUT);
        s3c_gpio_setpull(GPIO_PWM_INT, S3C_GPIO_PULL_NONE);

        gpio_direction_output(GPIO_PWM_SCL, 0);
        s3c_gpio_cfgpin(GPIO_PWM_SCL, S3C_GPIO_OUTPUT);
        s3c_gpio_setpull(GPIO_PWM_SCL, S3C_GPIO_PULL_NONE);

        gpio_direction_output(GPIO_PWM_SDA, 0);
        s3c_gpio_cfgpin(GPIO_PWM_SDA, S3C_GPIO_OUTPUT);
        s3c_gpio_setpull(GPIO_PWM_SDA, S3C_GPIO_PULL_NONE);

    } else {
        gpio_direction_output(GPIO_PWM_INT, 1);
        gpio_direction_input(GPIO_PWM_INT);
        s3c_gpio_cfgpin(GPIO_PWM_INT, S3C_GPIO_SFN(0xf));
        /*s3c_gpio_cfgpin(GPIO_PWM_INT, S3C_GPIO_INPUT); */
        s3c_gpio_setpull(GPIO_PWM_INT, S3C_GPIO_PULL_NONE);
        /*S3C_GPIO_PULL_UP */

        gpio_direction_output(GPIO_PWM_SCL, 1);
        gpio_direction_input(GPIO_PWM_SCL);
        s3c_gpio_cfgpin(GPIO_PWM_SCL, S3C_GPIO_SFN(3));
        s3c_gpio_setpull(GPIO_PWM_SCL, S3C_GPIO_PULL_NONE);

        gpio_direction_output(GPIO_PWM_SDA, 1);
        gpio_direction_input(GPIO_PWM_SDA);
        s3c_gpio_cfgpin(GPIO_PWM_SDA, S3C_GPIO_SFN(3));
        s3c_gpio_setpull(GPIO_PWM_SDA, S3C_GPIO_PULL_NONE);

        //state = s3c_gpio_getcfg(GPIO_PWM_SDA);

        gpio_free(GPIO_PWM_SCL);
        gpio_free(GPIO_PWM_SDA);
    }
    return 0;
}

static void pwm_pwr_on_reset(struct i2c_client *client)
{
    struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
    struct interface_pwm_platform_data *pdata = client->dev.platform_data;

    if(pdata == NULL) {
        return ;
    }

    i2c_lock_adapter(adapter);
    interface_pwm_enable(true);

    msleep(50);
    pdata->led_power_on(1);
    pdata->bus_power_on(1);
    pdata->power_on(1);
    msleep(300);

    gpio_direction_output(pdata->gpio_sda, 0);
    gpio_direction_output(pdata->gpio_scl, 0);
    gpio_direction_output(pdata->gpio_int, 0);

    msleep(250);

    interface_pwm_enable(false);
    i2c_unlock_adapter(adapter);

    /* TODO: Seems long enough for the firmware to boot.
     * Find the right value */
    msleep(250);
}

static int pca9685_pwm_probe(struct i2c_client *client,
                const struct i2c_device_id *id)
{
    struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
    struct device_node *np = client->dev.of_node;
    struct interface_pwm_platform_data *pdata = client->dev.platform_data;
    struct pca9685 *pca;
    int ret;
    int mode2 = 0;

    printk(KERN_DEBUG "[PWM] %s startup...\n", __func__);

    if (pdata == NULL) {
        ret = PTR_ERR(pdata);
        dev_err(&client->dev, "Failed to initialize (pdata is null): %d\n",
            ret);
        return ret;
    }

    if (!i2c_check_functionality(adapter, I2C_FUNC_I2C)) {
        dev_err(&client->dev, "Failed to initialize adapter.\n");
        return -EIO;
    }

    pca = devm_kzalloc(&client->dev, sizeof(*pca), GFP_KERNEL);
    if (!pca)
        return -ENOMEM;

    pwm_pwr_on_reset(client);

    pca->regmap = devm_regmap_init_i2c(client, &pca9685_regmap_i2c_config);
    if (IS_ERR(pca->regmap)) {
        ret = PTR_ERR(pca->regmap);
        dev_err(&client->dev, "Failed to initialize register map: %d\n",
            ret);
        return ret;
    }

    i2c_set_clientdata(client, pca);

    ret = regmap_read(pca->regmap, PCA9685_MODE2, &mode2);
    printk(KERN_DEBUG "[PWM] %s mode2 read: %x, ret: %d\n", __func__, mode2, ret);

#ifdef CONFIG_OF
    if (of_property_read_bool(np, "invert"))
#else
    if( pdata->invert )
#endif
        mode2 |= MODE2_INVRT;
    else
        mode2 &= ~MODE2_INVRT;

#ifdef CONFIG_OF
    if (of_property_read_bool(np, "open-drain"))
#else
    if( pdata->open_drain )
#endif
        mode2 &= ~MODE2_OUTDRV;
    else
        mode2 |= MODE2_OUTDRV;

    ret = regmap_write(pca->regmap, PCA9685_MODE2, mode2);
    printk(KERN_DEBUG "[PWM] %s mode2 write: %x, ret: %d\n", __func__, mode2, ret);

    /* clear all "full off" bits */
    regmap_write(pca->regmap, PCA9685_ALL_LED_OFF_L, 0);
    regmap_write(pca->regmap, PCA9685_ALL_LED_OFF_H, 0);

    pca->chip.ops = &pca9685_pwm_ops;
    /* add an extra channel for ALL_LED */
    pca->chip.npwm = PCA9685_MAXCHAN + 1;

    pca->chip.dev = &client->dev;
    pca->chip.base = pdata->base;
    pca->chip.can_sleep = true;
    device_init_wakeup(&client->dev, 1);

    ret = pwmchip_add(&pca->chip);

    printk(KERN_DEBUG "[PWM] %s init success done, chip base: %d.\n", __func__, pdata->base);
    return ret;
}

static int pca9685_pwm_remove(struct i2c_client *client)
{
    struct pca9685 *pca = i2c_get_clientdata(client);

    regmap_update_bits(pca->regmap, PCA9685_MODE1, MODE1_SLEEP,
               MODE1_SLEEP);

    return pwmchip_remove(&pca->chip);
}

static const struct i2c_device_id pca9685_id[] = {
    { "sec_interface_pwm", 0 },
    { /* sentinel */ },
};
MODULE_DEVICE_TABLE(i2c, pca9685_id);

#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND)
static int pwm_suspend(struct device *dev)
{
        struct i2c_client *client = to_i2c_client(dev);
        struct pca9685 *chip = i2c_get_clientdata(client);

        dev_info(&client->dev, "[PWM] chip suspend\n");

        return 0;
}

static int pwm_resume(struct device *dev)
{
        struct i2c_client *client = to_i2c_client(dev);
        struct pca9685 *chip = i2c_get_clientdata(client);

        dev_info(&client->dev, "[PWM] chip resume\n");

        return 0;
}

static SIMPLE_DEV_PM_OPS(pwm_dev_pm_ops,
                          pwm_suspend, pwm_resume);
#endif

static struct i2c_driver pca9685_i2c_driver = {
    .driver = {
        .name = "sec_interface_pwm",
        .owner = THIS_MODULE,
#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND)
        .pm   = &pwm_dev_pm_ops,
#endif
    },
    .probe = pca9685_pwm_probe,
    .remove = pca9685_pwm_remove,
    .id_table = pca9685_id,
};

static int __init pca9685_i2c_init(void)
{
    printk(KERN_DEBUG "[PWM] %s add device!\n", __func__);
    return i2c_add_driver(&pca9685_i2c_driver);

}

static void __exit pca9685_i2c_exit(void)
{
    i2c_del_driver(&pca9685_i2c_driver);
}

module_init(pca9685_i2c_init);
module_exit(pca9685_i2c_exit);

MODULE_AUTHOR("Steffen Trumtrar <s.trumtrar@pengutronix.de>");
MODULE_DESCRIPTION("PWM driver for PCA9685");
MODULE_LICENSE("GPL");
