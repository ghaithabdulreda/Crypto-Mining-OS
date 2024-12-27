#!/bin/bash

rm *.o
rm *.bin
rm *.flp
rm *.img
rm *.vdi

nasm -f bin bootloader.asm -o main.bin || { echo "Failed to assemble bootloader"; exit 1; }

nasm -f elf 32/kernel_entry.asm -o kernel_entry.o 
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -mtune=intel -g -c 32/kernel.cpp -o kernel.o 
/usr/local/i386elfgcc/bin/i386-elf-ld -o full_kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o  --oformat binary


cat main.bin full_kernel.bin > main.flp

dd if=/dev/zero of=os.img bs=512 count=2048

dd if=main.bin of=os.img conv=notrunc
dd if=full_kernel.bin of=os.img bs=512 seek=1 conv=notrunc


VBoxManage convertfromraw os.img main.vdi --format VDI

echo "DONE"


rm *.o
rm *.bin
# rm *.flp
# rm *.img
# rm *.vdi