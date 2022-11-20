[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

mov bx, HELLO_WORLD_MSG
call println_string

call read_disk

mov bx, PROGRAM_SPACE
call print_string

jmp $

%include "bootloader_functions/print_string.asm"
%include "bootloader_functions/disk_read.asm"

times 510-($-$$) db 0
dw 0xaa55

db "hello disk :3", 0
times 2048 - ($-$$) db 0