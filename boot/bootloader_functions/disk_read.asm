PROGRAM_SPACE equ 0x7e00

read_disk:
    mov ah, 0x02
    mov bx, PROGRAM_SPACE
    mov al, 5 ; read 5 sectors (change when needed)
    mov dl, [BOOT_DISK]
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13

    jc disk_read_error

    ret
    
BOOT_DISK:
    db 0

DISK_READ_ERROR_MSG:
    db "Disk read failed", 0

disk_read_error:
    mov bx, DISK_READ_ERROR_MSG
    call print_string
    
    jmp $