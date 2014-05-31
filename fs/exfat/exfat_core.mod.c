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
	{ 0xfe5d4bb2, "sys_tz" },
	{ 0x405c1144, "get_seconds" },
	{ 0x7a728ef4, "up" },
	{ 0xb5a0e267, "down" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x5f754e5a, "memset" },
	{ 0x8496b81, "mark_page_accessed" },
	{ 0x24b74417, "sync_blockdev" },
	{ 0x4f0ee668, "__lock_buffer" },
	{ 0x603955f8, "unlock_buffer" },
	{ 0x77217c72, "mark_buffer_dirty" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0x6bcb6e07, "__might_sleep" },
	{ 0x8d66a3a, "warn_slowpath_fmt" },
	{ 0x19e15adb, "__bread" },
	{ 0xf6ad7a62, "__getblk" },
	{ 0x5920ee07, "sb_set_blocksize" },
	{ 0x84b183ae, "strncmp" },
	{ 0x97255bdf, "strlen" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0xb9a3235a, "kmalloc_caches" },
	{ 0xb24ef1ab, "sync_dirty_buffer" },
	{ 0x37a0cba, "kfree" },
	{ 0xfdb19ae6, "__brelse" },
	{ 0xe52592a, "panic" },
	{ 0x27e1a049, "printk" },
	{ 0x9d669763, "memcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

