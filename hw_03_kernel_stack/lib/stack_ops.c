#include <linux/kernel.h>

#include "kernel_stack.h"


void stack_init(void)
{
  pr_info("stack init\n");
}

int stack_push(int val)
{
  pr_info("push '%d'\n", val);
  return 1;
}

int stack_pop(void)
{
  pr_info("pop\n");
  return 777;
}

int stack_peek(void)
{
  pr_info("peek\n");
  return 777;
}

int stack_is_empty(void)
{
  pr_info("is_empty\n");
  return 1;
}

int stack_size(void)
{
  pr_info("size\n");
  return 3;
}

void stack_clear(void)
{
  pr_info("clear\n");
}

void stack_destroy(void)
{
  pr_info("stack destroy\n");
}

