all: OS-image.img

run: all
	qemu-system-x86_64 -drive file=OS-image.img,format=raw,index=0,media=disk

OS-image.img : bootloader.bin kernel.bin 
	cat $^ > $@

kernel.bin : link.ld kernel.o ext.o bin.o
	x86_64-elf-ld -T "link.ld"

kernel.o : kernel/kernel.cpp
	x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "$<" -o "$@"

bin.o : boot/bin.asm
	nasm -f elf64 $< -o $@

ext.o : boot/ext.asm
	nasm -f elf64 $< -o $@

bootloader.bin : boot/bootloader.asm
	nasm -f bin -I 'boot/bootloader_functions' $< -o $@

clean:
	rm -fr *.bin *.o *.dis *.img *.tmp
	rm -fr kernel/*.o boot/*.bin drivers/*.o