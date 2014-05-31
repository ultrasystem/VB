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
	{ 0x567a0886, "usb_deregister" },
	{ 0x67b27ec1, "tty_std_termios" },
	{ 0x27e1a049, "printk" },
	{ 0xae0fb35b, "put_tty_driver" },
	{ 0xb7563e1a, "tty_unregister_driver" },
	{ 0x7ff217bd, "usb_register_driver" },
	{ 0xb1a142c5, "tty_register_driver" },
	{ 0x41944867, "tty_set_operations" },
	{ 0x2e2947f9, "alloc_tty_driver" },
	{ 0x8949858b, "schedule_work" },
	{ 0xddbc1a97, "tty_wakeup" },
	{ 0xa683e231, "tty_port_block_til_ready" },
	{ 0xf400a1c, "tty_port_tty_set" },
	{ 0x34c801bf, "tty_port_close_end" },
	{ 0xefbb98b, "tty_port_close_start" },
	{ 0x59e02cc4, "usb_autopm_get_interface_async" },
	{ 0x71c90087, "memcmp" },
	{ 0x2f27f078, "tty_get_baud_rate" },
	{ 0x66437f56, "tty_port_hangup" },
	{ 0x48f4fb6c, "usb_autopm_put_interface" },
	{ 0x9858ceca, "usb_autopm_get_interface" },
	{ 0x69af8f54, "tty_flip_buffer_push" },
	{ 0xcb636b1d, "tty_insert_flip_string_fixed_flag" },
	{ 0x74c97f9c, "_raw_spin_unlock_irqrestore" },
	{ 0xbd7083bc, "_raw_spin_lock_irqsave" },
	{ 0xb9a3235a, "kmalloc_caches" },
	{ 0x23c446ec, "tty_register_device" },
	{ 0xd7ce673f, "usb_get_intf" },
	{ 0x23ef139e, "usb_driver_claim_interface" },
	{ 0xb983ac24, "_dev_info" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x603f2873, "device_create_file" },
	{ 0x6039dc7b, "dev_warn" },
	{ 0x347f2373, "usb_alloc_urb" },
	{ 0x44a202c3, "usb_alloc_coherent" },
	{ 0x1c10cca2, "tty_port_init" },
	{ 0xefa6365c, "__mutex_init" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0x61628100, "usb_ifnum_to_if" },
	{ 0x9e6be1b0, "usb_control_msg" },
	{ 0xf9629bd9, "usb_driver_release_interface" },
	{ 0x5c89ca36, "dev_set_drvdata" },
	{ 0x95577978, "device_remove_file" },
	{ 0x37a0cba, "kfree" },
	{ 0x264f3c36, "usb_free_urb" },
	{ 0xa6c0bd57, "usb_put_intf" },
	{ 0x4143254c, "tty_unregister_device" },
	{ 0x9d669763, "memcpy" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xa5505535, "usb_free_coherent" },
	{ 0x311b7963, "_raw_spin_unlock" },
	{ 0xc2161e33, "_raw_spin_lock" },
	{ 0x4205ad24, "cancel_work_sync" },
	{ 0x4df8f7ad, "usb_kill_urb" },
	{ 0x6d22f9c1, "mutex_unlock" },
	{ 0x7f1f872b, "mutex_lock" },
	{ 0x275b8027, "dev_get_drvdata" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x2a3aa678, "_test_and_clear_bit" },
	{ 0xc212a112, "_raw_spin_unlock_irq" },
	{ 0xd59daefe, "_raw_spin_lock_irq" },
	{ 0x75507a4c, "usb_autopm_put_interface_async" },
	{ 0x7d11c268, "jiffies" },
	{ 0xefd80b2e, "tty_hangup" },
	{ 0xb1553169, "tty_kref_put" },
	{ 0x3cf91b5c, "tty_port_tty_get" },
	{ 0xbd54bb9f, "dev_err" },
	{ 0xd36a5fe, "usb_submit_urb" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0870p0001d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0E8Dp0003d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0E8Dp3329d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0482p0203d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v079Bp000Fd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0ACEp1602d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0ACEp1608d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0ACEp1611d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p7000d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0803p3095d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0572p1321d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0572p1324d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0572p1328d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p6425d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D91d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D92d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D93d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D95d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D96d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D97d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D99d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v22B8p2D9Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0572p1329d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0572p1340d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v05F9p4002d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1BBBp0003d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1576p03B1d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0421p042Dd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04D8d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04C9d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0419d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p044Dd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0001d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0475d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0508d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0418d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0425d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0486d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04DFd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p000Ed*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0445d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p042Fd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p048Ed*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0420d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04E6d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04B2d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0134d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p046Ed*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p002Fd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0088d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p00FCd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0042d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p00B0d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p00ABd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0481d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0007d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0071d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04F0d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0070d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p00E9d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0099d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0128d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p008Fd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p00A0d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p007Bd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0094d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p003Ad*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p00E9d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0108d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p01F5d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p02E3d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0178d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p010Ed*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p02D9d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p01D0d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0223d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0275d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p026Cd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0154d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p04CEd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p01D4d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0302d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p0335d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v0421p03CDd*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v04E7p6651d*dc*dsc*dp*ic02isc02ipFF*");
MODULE_ALIAS("usb:v03EBp0030d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0694pFF00d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v04D8p000Bd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip00*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip01*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip02*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip03*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip04*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip05*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ip06*");
