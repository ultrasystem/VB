#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x2047c109, "module_layout" },
	{ 0xb78c61e8, "param_ops_bool" },
	{ 0x567a0886, "usb_deregister" },
	{ 0x7ff217bd, "usb_register_driver" },
	{ 0xb9a3235a, "kmalloc_caches" },
	{ 0xcfcaa0f2, "led_classdev_register" },
	{ 0xc0567eb, "input_ff_destroy" },
	{ 0x4ccf6ac2, "input_ff_create_memless" },
	{ 0xdb8a0950, "input_set_capability" },
	{ 0xefa6365c, "__mutex_init" },
	{ 0xd80541ec, "input_free_device" },
	{ 0x85946a85, "input_register_device" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x347f2373, "usb_alloc_urb" },
	{ 0x44a202c3, "usb_alloc_coherent" },
	{ 0x6e09af16, "input_allocate_device" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0x5c89ca36, "dev_set_drvdata" },
	{ 0xa5505535, "usb_free_coherent" },
	{ 0x264f3c36, "usb_free_urb" },
	{ 0x45266069, "input_unregister_device" },
	{ 0x6d22f9c1, "mutex_unlock" },
	{ 0x7f1f872b, "mutex_lock" },
	{ 0x27e1a049, "printk" },
	{ 0x9fe4b354, "input_set_abs_params" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x1b3f81d4, "input_event" },
	{ 0xd36a5fe, "usb_submit_urb" },
	{ 0x37a0cba, "kfree" },
	{ 0x79bd1f72, "led_classdev_unregister" },
	{ 0x4df8f7ad, "usb_kill_urb" },
	{ 0x275b8027, "dev_get_drvdata" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic58isc42ip00*");
MODULE_ALIAS("usb:v045Ep*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v045Ep*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v046Dp*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v046Dp*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v0738p*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v0738p*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v0E6Fp*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v0E6Fp*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v1430p*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v1430p*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v146Bp*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v146Bp*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v1BADp*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v1BADp*d*dc*dsc*dp*icFFisc5Dip81*");
MODULE_ALIAS("usb:v0F0Dp*d*dc*dsc*dp*icFFisc5Dip01*");
MODULE_ALIAS("usb:v0F0Dp*d*dc*dsc*dp*icFFisc5Dip81*");
