#pragma once
#include "../drivers/io.cpp"
#include "../kernel/typedefs.cpp"

#define VGA_MEMORY (uint_8*)0xb8000
#define VGA_WIDTH 80

uint_16 CursorPosition;

void SetCursorPosiition(uint_16 positions){
    
    if(positions > VGA_WIDTH * 25 || positions < 0){
        positions = 0;
    }

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint_8)(positions & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8)((positions >> 8) & 0xFF));

    CursorPosition = positions;
}

unsigned short PositionFromCoordinates(uint_16 x, uint_8 y){
    return y * VGA_WIDTH + x;
}