cmd_drivers/vhost/vhost_scsi.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o drivers/vhost/vhost_scsi.ko drivers/vhost/vhost_scsi.o drivers/vhost/vhost_scsi.mod.o ;  true
