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
	{ 0xb293b59, "no_llseek" },
	{ 0x5babd120, "kmem_cache_destroy" },
	{ 0xa96fc24a, "misc_deregister" },
	{ 0x67b008dd, "misc_register" },
	{ 0xc7733d93, "kmem_cache_create" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x72542c85, "__wake_up" },
	{ 0x74c97f9c, "_raw_spin_unlock_irqrestore" },
	{ 0xbd7083bc, "_raw_spin_lock_irqsave" },
	{ 0x780f2390, "hrtimer_start" },
	{ 0xb190a2b0, "hrtimer_init" },
	{ 0x84b183ae, "strncmp" },
	{ 0x9d669763, "memcpy" },
	{ 0x41e92619, "__init_waitqueue_head" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0xfc033b85, "shmem_file_setup" },
	{ 0xaafbf0c9, "shmem_set_file" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0xcd2dd739, "nonseekable_open" },
	{ 0x37a0cba, "kfree" },
	{ 0xfb12582c, "fput" },
	{ 0xc84fff66, "kmem_cache_free" },
	{ 0x76789af4, "hrtimer_cancel" },
	{ 0x6d22f9c1, "mutex_unlock" },
	{ 0x7f1f872b, "mutex_lock" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

