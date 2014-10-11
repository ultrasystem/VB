#ifndef _LINUX_INTERFACE_I2C_H
#define _LINUX_INTERFACE_I2C_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/hrtimer.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/delay.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif


#define TCA6416_INPUT		0
#define TCA6416_OUTPUT		1
#define TCA6416_INVERT		2
#define TCA6416_DIRECTION	3

#define TCA6416_PINS        16

#define I2C_M_WR 0		/* for i2c */

/* LDO Regulator */
#if defined(CONFIG_MACH_M0)\
	|| defined(CONFIG_MACH_C1)\
	|| defined(CONFIG_MACH_M3)\
	|| defined(CONFIG_MACH_T0)
#define	TK_REGULATOR_NAME	"touchkey"
#else
#define	TK_REGULATOR_NAME	"touch"
#endif

struct interface_platform_data {
	int gpio_sda;
	int gpio_scl;
	int gpio_int;
    unsigned gpio_start;
    uint16_t invert;
    int	 irq_base;
	void (*init_platform_hw)(void);
	int (*suspend) (void);
	int (*resume) (void);
	int (*power_on) (bool);
	int (*led_power_on) (bool);
    int (*bus_power_on) (bool);
	int (*reset_platform_hw)(void);
};

/*Parameters for i2c driver*/
struct interface_i2c {
	struct i2c_client *client;
    struct gpio_chip gpio_chip;
	struct early_suspend early_suspend;
	struct mutex lock;
	struct device	*dev;
	int irq;
    struct mutex irq_lock;
    uint16_t irq_mask;
    uint16_t irq_stat;
    uint16_t irq_trig_raise;
    uint16_t irq_trig_fall;
    int	 irq_base;
    struct interface_platform_data *pdata;
	char *name;
	int (*power)(int on);
	struct work_struct update_work;
	int update_status;
    uint16_t reg_input;
    uint16_t reg_output;
    uint16_t reg_direction;
    uint16_t reg_invert;
    void *gpio_base;
};

#endif /* _LINUX_CYPRESS_TOUCHKEY_I2C_H */
