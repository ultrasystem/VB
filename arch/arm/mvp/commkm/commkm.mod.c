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
	{ 0x2f103932, "QP_Notify" },
	{ 0x7b8e14b0, "QP_DequeueCommit" },
	{ 0x7b4459bd, "QP_DequeueSegment" },
	{ 0x87be76bf, "QP_DequeueReset" },
	{ 0x54983252, "QP_DequeueSpace" },
	{ 0x789f40c2, "QP_EnqueueCommit" },
	{ 0x2bfe57a4, "QP_EnqueueSegment" },
	{ 0x2008083d, "QP_EnqueueReset" },
	{ 0xf32e4cd0, "QP_EnqueueSpace" },
	{ 0xb9a3235a, "kmalloc_caches" },
	{ 0xf28222f2, "QP_RegisterDetachCB" },
	{ 0x2534317e, "QP_Attach" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0x669d57c5, "QP_UnregisterListener" },
	{ 0x79ee379d, "QP_RegisterListener" },
	{ 0x4e902d0b, "QP_Detach" },
	{ 0x42224298, "sscanf" },
	{ 0x810b3618, "param_ops_string" },
	{ 0x465757c3, "cpu_present_mask" },
	{ 0xc98f0e7, "queue_delayed_work_on" },
	{ 0xe5a19a7c, "__alloc_workqueue_key" },
	{ 0x74c134b9, "__sw_hweight32" },
	{ 0xe1d61c3a, "cancel_delayed_work_sync" },
	{ 0xc7a38209, "destroy_workqueue" },
	{ 0xdcff54fe, "flush_workqueue" },
	{ 0xddc16c88, "flush_delayed_work" },
	{ 0x7426f76c, "init_timer_key" },
	{ 0xcdc7fecf, "queue_delayed_work" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x6bcb6e07, "__might_sleep" },
	{ 0x7d11c268, "jiffies" },
	{ 0x71c90087, "memcmp" },
	{ 0xb8f37b78, "mutex_trylock" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0xf83178bd, "finish_wait" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x32f80ea9, "prepare_to_wait" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x341dbfa3, "__per_cpu_offset" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x311b7963, "_raw_spin_unlock" },
	{ 0xc2161e33, "_raw_spin_lock" },
	{ 0x37a0cba, "kfree" },
	{ 0xefa6365c, "__mutex_init" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x41e92619, "__init_waitqueue_head" },
	{ 0x72542c85, "__wake_up" },
	{ 0xb368ec89, "_raw_spin_unlock_bh" },
	{ 0x8bd94317, "_raw_spin_lock_bh" },
	{ 0xf61a8cb8, "module_put" },
	{ 0x6d22f9c1, "mutex_unlock" },
	{ 0x4bc78a46, "mutex_lock_interruptible" },
	{ 0x5fe6c44c, "Mvpkm_CommEvUnregisterProcessCB" },
	{ 0xabeae8b, "sock_release" },
	{ 0x27e1a049, "printk" },
	{ 0xa4b01c6f, "Mvpkm_CommEvRegisterProcessCB" },
	{ 0xc71e9635, "kernel_bind" },
	{ 0x675bdd8d, "sock_create_kern" },
	{ 0xaebb58d2, "kernel_sendmsg" },
	{ 0xfa2a45e, "__memzero" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mvpkm";


MODULE_INFO(srcversion, "3EDC81FF5DA7227B8828223");
