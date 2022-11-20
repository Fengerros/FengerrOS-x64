gdt_nulldesc:
    dd 0
    dd 0

gdt_codedesc:
    dw 0xffff   ;limit
    dw 0x0000   ;base (low)
    db 0x00   ;base (mid)
    db 10011010b    ;access
    db 11001111b    ;granularity    
    db 0x00   ;base (high)

gdt_datadesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nulldesc - 1
        dd gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc