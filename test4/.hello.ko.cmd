cmd_/home/jy-os/lab/test4/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o /home/jy-os/lab/test4/hello.ko /home/jy-os/lab/test4/hello.o /home/jy-os/lab/test4/hello.mod.o ;  true