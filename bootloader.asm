[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

mov bx, BOOTLOADER_MSG
call println_string

call read_disk

jmp PROGRAM_SPACE

jmp $

%include "bootloader_functions/print_string.asm"
%include "bootloader_functions/disk_read.asm"

BOOTLOADER_MSG:
    db "Bootloader boot up...", 0

times 510-($-$$) db 0
dw 0xaa55