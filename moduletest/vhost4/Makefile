obj-m = vhost_net.o
vhost_net-y := net.o


default:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	rm -rf *.mod.*
	rm -rf *.o*
	rm -rf *.ko
	rm -rf *.order
	rm -rf *.symvers
