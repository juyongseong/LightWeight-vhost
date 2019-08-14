cmd_drivers/vhost/vhost_vsock.o := ld -m elf_x86_64  -z max-page-size=0x200000    -r -o drivers/vhost/vhost_vsock.o drivers/vhost/vsock.o 
