#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hw_init(void) {
  pr_info("init\n");
  return 0;
}

static void __exit hw_exit(void) { 
  pr_info("exit\n"); 
}

module_init(hw_init);
module_exit(hw_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kaznacheev Dmitriy");
MODULE_DESCRIPTION("Hello World module for Linux kernel");
MODULE_VERSION("1.0");

