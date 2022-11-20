print_string:    
    mov ah, 0x0e
    .loop:
        mov al, [bx]
        cmp al, 0x00
        je .end
        int 0x10
        inc bx
        jmp .loop
    .end:
    ret

println_string:
    call print_string
    mov bx, NEW_LINE
    call print_string
    ret

HELLO_WORLD_MSG:
    db 'Hello World :3', 0

NEW_LINE:
    db 0x0a, 0x0d
    db 0