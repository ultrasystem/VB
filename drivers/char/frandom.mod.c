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
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xe9175784, "device_create" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0xff8debe0, "cdev_add" },
	{ 0x3d7f8a78, "cdev_init" },
	{ 0xd2da45e1, "__class_create" },
	{ 0x16b9035f, "class_destroy" },
	{ 0xedbfe806, "device_destroy" },
	{ 0x10585594, "cdev_del" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xb9a3235a, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x27e1a049, "printk" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x7a728ef4, "up" },
	{ 0x1c3f30f, "down_interruptible" },
	{ 0x37a0cba, "kfree" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

