obj-m = hello.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.mod.*
	rm -rf *.o
	rm -rf *.ko
	rm -rf *.order
	rm -rf *.symvers
