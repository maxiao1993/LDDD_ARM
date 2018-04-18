obj-m :=cur_multi_globalmem.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(shell uname -r)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions Module.symvers .Makefile.swp
