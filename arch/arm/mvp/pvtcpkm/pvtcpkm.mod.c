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
	{ 0xf61a8cb8, "module_put" },
	{ 0x777f747d, "CommSvc_Unlock" },
	{ 0x2eb3c64f, "CommSvc_Lock" },
	{ 0x7d11c268, "jiffies" },
	{ 0xb8ead4d6, "CommSvc_Alloc" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0xb86e4ab9, "random32" },
	{ 0x810b3618, "param_ops_string" },
	{ 0x465757c3, "cpu_present_mask" },
	{ 0xc98f0e7, "queue_delayed_work_on" },
	{ 0xe5a19a7c, "__alloc_workqueue_key" },
	{ 0x74c134b9, "__sw_hweight32" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xe1d61c3a, "cancel_delayed_work_sync" },
	{ 0xc7a38209, "destroy_workqueue" },
	{ 0xdcff54fe, "flush_workqueue" },
	{ 0xddc16c88, "flush_delayed_work" },
	{ 0x7426f76c, "init_timer_key" },
	{ 0xcdc7fecf, "queue_delayed_work" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x6bcb6e07, "__might_sleep" },
	{ 0xe1533cce, "kernel_getpeername" },
	{ 0xa6c5fbea, "CommSvc_GetState" },
	{ 0xbf129423, "kernel_connect" },
	{ 0x1dce9de8, "kernel_accept" },
	{ 0x53dd7ea0, "kernel_listen" },
	{ 0x7b38f74b, "kernel_getsockopt" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x28a81b58, "kernel_getsockname" },
	{ 0xc71e9635, "kernel_bind" },
	{ 0xee94a344, "CommSvc_RegisterImpl" },
	{ 0xda890776, "nf_register_hooks" },
	{ 0x341dbfa3, "__per_cpu_offset" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xb9a3235a, "kmalloc_caches" },
	{ 0x7eed8d81, "kobject_init_and_add" },
	{ 0x34220a09, "kmem_cache_alloc" },
	{ 0xdffd923, "Mvpkm_FindVMNamedKSet" },
	{ 0x7b5b0b2f, "put_pid" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0x8d522714, "__rcu_read_lock" },
	{ 0x43e27750, "pid_task" },
	{ 0x6fa2623c, "find_get_pid" },
	{ 0x97255bdf, "strlen" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xae0a58c7, "kernel_setsockopt" },
	{ 0x6e04b501, "CommSvc_GetTranspInitArgs" },
	{ 0x5f754e5a, "memset" },
	{ 0x42224298, "sscanf" },
	{ 0x624999df, "init_net" },
	{ 0xa03bb3dc, "__put_net" },
	{ 0x202c73d0, "kobject_put" },
	{ 0xe84dd843, "kobject_del" },
	{ 0xbe4b7616, "nf_unregister_hooks" },
	{ 0x4ffa8140, "CommSvc_UnregisterImpl" },
	{ 0x62e93e41, "kernel_sock_ioctl" },
	{ 0x675bdd8d, "sock_create_kern" },
	{ 0x4bc78a46, "mutex_lock_interruptible" },
	{ 0x71c90087, "memcmp" },
	{ 0xabeae8b, "sock_release" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x7b1010cc, "Mvpkm_vmwareUid" },
	{ 0x27e1a049, "printk" },
	{ 0x26477c07, "__vmalloc" },
	{ 0x38e8378d, "pgprot_kernel" },
	{ 0x7f1f872b, "mutex_lock" },
	{ 0x999e8297, "vfree" },
	{ 0x419c4694, "CommSvc_WriteVec" },
	{ 0xd2a5ef25, "kernel_recvmsg" },
	{ 0x5dd22014, "kernel_sock_shutdown" },
	{ 0xf412c9ca, "CommSvc_Write" },
	{ 0x6d22f9c1, "mutex_unlock" },
	{ 0xb8f37b78, "mutex_trylock" },
	{ 0x311b7963, "_raw_spin_unlock" },
	{ 0xc2161e33, "_raw_spin_lock" },
	{ 0xaebb58d2, "kernel_sendmsg" },
	{ 0x37a0cba, "kfree" },
	{ 0x7b6b8445, "sk_free" },
	{ 0xf77ea1e4, "CommSvc_ScheduleAIOWork" },
	{ 0xdfd4df13, "CommSvc_Zombify" },
	{ 0x922260b3, "CommSvc_DispatchUnlock" },
	{ 0xefa6365c, "__mutex_init" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=commkm,mvpkm";


MODULE_INFO(srcversion, "606EE0797294E45A3318567");
