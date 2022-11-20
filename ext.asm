jmp enter_protected_mode

%include "bootloader_functions/gdt.asm"
%include "bootloader_functions/print_string.asm"

enter_protected_mode:
    call enable_a20
    
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp codeseg:start_protected_mode

enable_a20:
    in al, 0x92
    or al, 0x2
    out 0x92, al

    ret

[bits 32]
%include "bootloader_functions/CPUID.asm"
%include "bootloader_functions/simple_paging.asm"

start_protected_mode:
    mov ax, dataseg
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov [0xb8000], byte '-'
    mov [0xb8000 + 1], byte 0xa
    mov [0xb8002], byte '-'
    mov [0xb8000 + 3], byte 0xb
    mov [0xb8004], byte '>'
    mov [0xb8000 + 5], byte 0xc

    call detect_cpuid
    call detect_longmode
    call set_up_identity_paging
    call edit_gdt

    jmp codeseg:start_64bit

[bits 64]
[extern _start]

start_64bit:
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20
    mov ecx, 500
    rep stosq

    call _start
    jmp $

times 2048 - ($-$$) db 0