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
	{ 0x17634745, "module_layout" },
	{ 0x5d1f8068, "cdev_del" },
	{ 0xe3c1d8c, "device_destroy" },
	{ 0x5e3d5305, "cdev_add" },
	{ 0x57ca7652, "cdev_init" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x2f729c13, "class_destroy" },
	{ 0xb09c4b8d, "device_create" },
	{ 0x95d52825, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x1ebbe235, "cdev_alloc" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xc9f5df35, "up" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x695b2cfd, "down_interruptible" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "83E8AB863D79565479DECA0");
