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
#include <linux/regmap.h>
#include <linux/slab.h>

struct pwm_device {
    struct device *dev;
    struct list_head node;
    const char *label;
    unsigned int pwm_id;
    struct i2c_client *client;
    int active_cnt;
};

static LIST_HEAD(pwm_list);


static int pwm_read_reg(struct i2c_client *client, int reg, uint8_t *val)
{
    int err = 0;
    int retry = 3;

    if (client == NULL) {
        printk(KERN_ERR "[PWM] chip is not enabled. %d\n",
               __LINE__);
        return -ENODEV;
    }

    while (retry--) {
        err = i2c_smbus_read_byte_data(client, reg << 1);

        if (err >= 0) {
            *val = (uint8_t) err;
            return 0;
        }
        printk(KERN_ERR "[PWM] %s %d %d i2c transfer error\n",
               __func__, __LINE__, err);
        mdelay(10);
    }
    return err;
}

static int pwm_write_reg(struct i2c_client *client, int reg, uint8_t val)
{
    int err = 0;
    int retry = 3;

    if (client == NULL) {
        printk(KERN_ERR "[PWM] chip is not enabled. %d\n",
               __LINE__);
        return -ENODEV;
    }

    while (retry--) {
        err = i2c_smbus_write_byte_data(client,
                reg << 1, val);

        if (err >= 0)
            return 0;

        printk(KERN_DEBUG "[PWM] %s %d %d i2c transfer error\n",
               __func__, __LINE__, err);
        mdelay(10);
    }
    return err;
}


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


void pwm_disable(struct pwm_device *pwm)
{
    int ret;

    ret = abx500_mask_and_set_register_interruptible(pwm->dev,
                AB8500_MISC, AB8500_PWM_OUT_CTRL7_REG,
                1 << (pwm->pwm_id-1), DISABLE_PWM);
    if (ret < 0)
        dev_err(pwm->dev, "%s: Failed to disable PWM, Error %d\n",
                            pwm->label, ret);
    return;
}
EXPORT_SYMBOL(pwm_disable);

struct pwm_device *pwm_request(int pwm_id, const char *label)
{
    struct pwm_device *pwm;

    list_for_each_entry(pwm, &pwm_list, node) {
        if (pwm->pwm_id == pwm_id) {
            pwm->label = label;
            pwm->pwm_id = pwm_id;

            if (pwm->active_cnt++ == 0)
                regmap_update_bits(pwm->regmap, PCA9685_MODE1, MODE1_SLEEP, 0x0);

            return pwm;
        }
    }

    return ERR_PTR(-ENOENT);
}
EXPORT_SYMBOL(pwm_request);

void pwm_free(struct pwm_device *pwm)
{
    pwm_disable(pwm);

    if (--pwm->active_cnt == 0)
        regmap_update_bits(pwm->regmap, PCA9685_MODE1, MODE1_SLEEP,
                   MODE1_SLEEP);
}
EXPORT_SYMBOL(pwm_free);


static struct regmap_config pca9685_regmap_i2c_config = {
    .reg_bits = 8,
    .val_bits = 8,
    .max_register = PCA9685_NUMREGS,
    .cache_type = REGCACHE_NONE,
};

static int pca9685_pwm_probe(struct i2c_client *client,
                const struct i2c_device_id *id)
{
    struct interface_pwm_platform_data *pdata = client->dev.platform_data;
    struct pwm_device *pca;
    int ret;
    int mode2;

    if(pdata == NULL) {
        printk(KERN_ERR "%s: no pdata\n", __func__);
        return -ENODEV;
    }

    /*Check I2C functionality */
    ret = i2c_check_functionality(client->adapter, I2C_FUNC_I2C);
    if (ret == 0) {
        printk(KERN_ERR "[I/O] No I2C functionality found\n");
        ret = -ENODEV;
        return ret;
    }

    pca = devm_kzalloc(&client->dev, sizeof(*pca), GFP_KERNEL);
    if (!pca)
        return -ENOMEM;

    i2c_set_clientdata(client, pca);

    pwm_read_reg(client, PCA9685_MODE2, &mode2);

    if(pdata->invert)
        mode2 |= MODE2_INVRT;
    else
        mode2 &= ~MODE2_INVRT;

    if(pdata->open_drain)
        mode2 &= ~MODE2_OUTDRV;
    else
        mode2 |= MODE2_OUTDRV;

    pwm_write_reg(client, PCA9685_MODE2, mode2);

    /* clear all "full off" bits */
    pwm_write_reg(client, PCA9685_ALL_LED_OFF_L, 0);
    pwm_write_reg(client, PCA9685_ALL_LED_OFF_H, 0);

    pca->dev = &client->dev;
    pca->client = client;
    pca->pwm_id = -1;
    list_add_tail(&pca->node, &pwm_list);

    return 0;
}

static int pca9685_pwm_remove(struct i2c_client *client)
{
    struct pwm_device *pca = i2c_get_clientdata(client);

    regmap_update_bits(pca->regmap, PCA9685_MODE1, MODE1_SLEEP,
               MODE1_SLEEP);

    list_del(&pwm->node);
    return 0;
}

static const struct i2c_device_id pca9685_id[] = {
    { "interface_pwm", 0 },
    { /* sentinel */ },
};
MODULE_DEVICE_TABLE(i2c, pca9685_id);

static struct i2c_driver pca9685_i2c_driver = {
    .driver = {
        .name = "interface_pwm",
        .owner = THIS_MODULE,
    },
    .probe = pca9685_pwm_probe,
    .remove = pca9685_pwm_remove,
    .id_table = pca9685_id,
};

module_i2c_driver(pca9685_i2c_driver);

MODULE_AUTHOR("Steffen Trumtrar <s.trumtrar@pengutronix.de>");
MODULE_DESCRIPTION("PWM driver for PCA9685");
MODULE_LICENSE("GPL");
