detect_cpuid:
    pushfd
    pop eax

    mov ecx, eax

    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jz no_cpuid

    ret

detect_longmode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz no_longmode
    ret

no_longmode:
    hlt

no_cpuid:
    hlt