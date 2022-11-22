#pragma once
#include "../kernel/typedefs.cpp"
#include "../drivers/io.cpp"
#include "../drivers/colors.cpp"
#include "../drivers/text_print.cpp"
#include "../drivers/keyboard_scan_code_set1.cpp"

struct IDT64{
    uint_16 offset_low;
    uint_16 selector;
    uint_8 ist;
    uint_8 type_attr;
    uint_16 offset_mid;
    uint_32 offset_high;
    uint_32 zero;
};

extern IDT64 _idt[256];
extern uint_64 isr1;
extern "C" void load_idt();

void InitIDT(){
    _idt[1].zero = 0;
	_idt[1].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000ffff));
	_idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000ffff0000) >> 16);
	_idt[1].offset_high = (uint_32)(((uint_64)&isr1 & 0xffffffff00000000) >> 32);
	_idt[1].ist = 0;
	_idt[1].selector = 0x08;
    _idt[1].type_attr = 0x8e;

    RemapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    load_idt();
}

void (*MainKeyboardHandler)(uint_8 scanCode, uint_8 chr, uint_8 color);

extern "C" void isr1_handler(){
    uint_8 scancode = inb(0x60);
    uint_8 chr = 0;

    if(scancode < 0x3A){
        chr = keyboard_set1::ScanCodeLookupTable[scancode];
    }
    if(MainKeyboardHandler != 0){
        MainKeyboardHandler(scancode, chr, 0xa | 0x0f);
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}