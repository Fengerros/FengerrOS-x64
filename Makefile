all: OS-image.img

run: all
	qemu-system-x86_64 -drive file=OS-image.img,format=raw,index=0,media=disk

OS-image.img : bootloader.bin kernel.bin 
	cat $^ > $@

kernel.bin : kernel.tmp
	objcopy -O binary $^ $@

kernel.tmp : kernel.o ext.o
	x86_64-elf-ld -o kernel.tmp -Ttext 0x7e00 ext.o kernel.o

kernel.o : kernel/kernel.cpp
	x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "$<" -o "$@"

ext.o : boot/ext.asm
	nasm -f elf64 $< -o $@

bootloader.bin : boot/bootloader.asm
	nasm -f bin -I 'boot/bootloader_functions' $< -o $@

clean:
	rm -fr *.bin *.o *.dis *.img *.tmp
	rm -fr kernel/*.o boot/*.bin drivers/*.o