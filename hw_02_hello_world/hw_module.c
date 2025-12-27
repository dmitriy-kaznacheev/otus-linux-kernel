#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

#define MAX_SIZE 255

static char my_str[MAX_SIZE] = {0};
static char ch_val= '\0';
static int idx = 0;

//--- idx --------------------

static int set_idx(const char *val, const struct kernel_param *)
{
  int rc, idx_;
  rc = kstrtoint(val, 10, &idx_);
  if (rc) {
    pr_err("value '%s' is not a valid index\n", val);
    return rc;
  }

  if ((idx_ < 0) || (idx_ >= MAX_SIZE)) {
    pr_err("value '%d' is out of range [0..%d]\n", idx_, MAX_SIZE-1);
    return -ERANGE;
  }

  idx = idx_;
  pr_info("idx = %d\n", idx);
  return 0;
}

static int get_idx(char *buf, const struct kernel_param *)
{
  return sprintf(buf, "%d", idx);
}

static const struct kernel_param_ops idx_param = {
  .set = set_idx,
  .get = get_idx,
};

module_param_cb(idx, &idx_param, &idx, 0664);
MODULE_PARM_DESC(idx, "index of the character in 'my_str'");

//--- ch_val -----------------

static int set_val(const char *val, const struct kernel_param *)
{
  size_t len = strlen(val);
  if (len != 1) {
    pr_err("one character is expected\n");
    return -EINVAL;
  }

  if ((val[0] < 0x20) || (val[0] > 0x7E)) {
    pr_err("code '0x%x' is not a printable ascii character\n", (int)val[0]);
    return -ERANGE;
  }

  ch_val = val[0];
  my_str[idx] = ch_val;
  pr_info("ch_val = %c\n", ch_val);
  return 0;
}

static int get_val(char *buf, const struct kernel_param *)
{
  buf[0] = my_str[idx];
  buf[1] = '\0';
  return 1;
}

static const struct kernel_param_ops val_param = {
  .set = set_val,
  .get = get_val,
};

module_param_cb(ch_val, &val_param, &ch_val, 0664);
MODULE_PARM_DESC(ch_val, "value of the character to set in 'my_str' in the 'idx' position");

//--- my_str -----------------

static int set_mystr(const char *val, const struct kernel_param *)
{
  pr_err("value '%s' cannot be set, parameter is read-only\n", val);
  return -EINVAL;
}

static int get_mystr(char *buf, const struct kernel_param *)
{
  return sprintf(buf, "%s", my_str);
}

static const struct kernel_param_ops str_param = {
  .set = set_mystr,
  .get = get_mystr,
};

module_param_cb(my_str, &str_param, &my_str, 0444);
MODULE_PARM_DESC(my_str, "read-only resulting string 'mystr'");

//--- init -------------------

static int __init hw_init(void) {
  pr_info("init\n");
  return 0;
}

static void __exit hw_exit(void) { 
  pr_info("exit\n"); 
}

module_init(hw_init);
module_exit(hw_exit);

//--- info -------------------

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kaznacheev Dmitriy");
MODULE_DESCRIPTION("Hello World module for Linux kernel");
MODULE_VERSION("1.0");

