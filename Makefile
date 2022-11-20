all: bootloader.img

run: all
	qemu-system-x86_64 -drive file=bootloader.img,format=raw,index=0,media=disk

bootloader.img : boot.bin ext.bin 
	cat $^ > bootloader.img

ext.bin : ext.asm
	nasm -f bin $< -o $@

boot.bin : bootloader.asm
	nasm -f bin $< -o $@

clean:
	rm -fr *.bin *.o *.dis *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o