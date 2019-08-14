cmd_drivers/vhost/vhost_scsi.o := ld -m elf_x86_64  -z max-page-size=0x200000    -r -o drivers/vhost/vhost_scsi.o drivers/vhost/scsi.o 
