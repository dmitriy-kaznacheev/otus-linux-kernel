KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

MODULE_NAME := hw_module
obj-m += $(MODULE_NAME).o

CLANG_FORMAT := clang-format
CLANG_FORMAT_FLAGS += -i
FORMAT_FILES := *.c

PYTHON := python3

.PHONY: build clean format check start stop

build:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean: 
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

format:
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(FORMAT_FILES)

check:
	@$(PYTHON) check_module.py

start:
	insmod $(PWD)/$(MODULE_NAME).ko

stop:
	rmmod $(MODULE_NAME)

