all: bootloader.img

run: all
	qemu-system-x86_64 -drive file=bootloader.img,format=raw,index=0,media=disk

%.img : %.asm
	nasm $< -f bin -I 'bootloader_functions' -o $@

clean:
	rm -fr *.bin *.o *.dis *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o