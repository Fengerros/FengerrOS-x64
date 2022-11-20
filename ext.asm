[org 0x7e00]


mov bx, MSG
call println_string

jmp $

%include "bootloader_functions/print_string.asm"


MSG:
    db "Extend memory working...", 0

times 2048 - ($-$$) db 0