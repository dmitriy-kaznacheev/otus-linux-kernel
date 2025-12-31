#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

#include "kernel_stack.h"


//--- push -------------------

static int push(const char *val, const struct kernel_param *kp)
{
  int rc, val_;
  rc = kstrtoint(val, 10, &val_);
  if (rc) {
    pr_err("value '%s' is not valid\n", val);
    return rc;
  }

  stack_push(val_);
  return 0;
}

static const struct kernel_param_ops push_param = {
  .set = push,
  .get = NULL,
};

module_param_cb(push, &push_param, NULL, 0664);
MODULE_PARM_DESC(push, "add element to stack");

//--- pop --------------------

static int pop(char *buf, const struct kernel_param *kp)
{
  int val = stack_pop();
  return sprintf(buf, "%d", val);
}

static const struct kernel_param_ops pop_param = {
  .set = NULL,
  .get = pop,
};

module_param_cb(pop, &pop_param, NULL, 0444);
MODULE_PARM_DESC(pop, "get and delete element from stack");

//--- peek -------------------

static int peek(char *buf, const struct kernel_param *kp)
{
  int val = stack_peek();
  return sprintf(buf, "%d", val);
}

static const struct kernel_param_ops peek_param = {
  .set = NULL,
  .get = peek,
};

module_param_cb(peek, &peek_param, NULL, 0444);
MODULE_PARM_DESC(peek, "get element from stack");

//--- size -------------------

static int size(char *buf, const struct kernel_param *kp)
{
  int val = stack_size();
  return sprintf(buf, "%d", val);
}

static const struct kernel_param_ops size_param = {
  .set = NULL,
  .get = size,
};

module_param_cb(size, &size_param, NULL, 0444);
MODULE_PARM_DESC(size, "get size stack");

//--- is_empty ---------------

static int is_empty(char *buf, const struct kernel_param *kp)
{
  int val = stack_is_empty();
  return sprintf(buf, "%d", val);
}

static const struct kernel_param_ops is_empty_param = {
  .set = NULL,
  .get = is_empty,
};

module_param_cb(is_empty, &is_empty_param, NULL, 0444);
MODULE_PARM_DESC(is_empty, "check if stack is empty");

//--- clear ------------------

static int clear(const char *val, const struct kernel_param *kp)
{
  stack_clear();
  return 0;
}

static const struct kernel_param_ops clear_param = {
  .set = clear,
  .get = NULL,
};

module_param_cb(clear, &clear_param, NULL, 0664);
MODULE_PARM_DESC(clear, "clear stack");

//--- init -------------------

static int __init hw_init(void) {
  pr_info("init\n");
  stack_init();
  return 0;
}

static void __exit hw_exit(void) { 
  stack_destroy();
  pr_info("exit\n");
}

module_init(hw_init);
module_exit(hw_exit);

//--- info -------------------

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kaznacheev Dmitriy");
MODULE_DESCRIPTION("Linux kernel module that implements the stack data structure");
MODULE_VERSION("1.0");

