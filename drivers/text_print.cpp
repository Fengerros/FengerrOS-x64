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

uint_16 PositionFromCoordinates(uint_8 x, uint_8 y){
    return y * VGA_WIDTH + x;
}

void PrintString(const char* string){
    uint_8* charPtr = (uint_8*)string;
    uint_16 index = CursorPosition;
    while(*charPtr != 0){
        switch (*charPtr)
        {
        case 10:
            index += VGA_WIDTH;
            break;
        case 13:
            index -= index % VGA_WIDTH;
            break;
        default:
            *(VGA_MEMORY + index * 2) = *charPtr;
            index++;
            break;
        }
        charPtr++;
    }
    SetCursorPosiition(index);
}

char hexToStringOutput[128];
template<typename T>
const char* HexToString(T value){
  T* valPtr = &value;
  uint_8* ptr;
  uint_8 temp;
  uint_8 size = (sizeof(T)) * 2 - 1;
  uint_8 i;
  for (i = 0; i < size; i++){
    ptr = ((uint_8*)valPtr + i);
    temp = ((*ptr & 0xF0) >> 4);
    hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
    temp = ((*ptr & 0x0F));
    hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
  }
  hexToStringOutput[size + 1] = 0;
  return hexToStringOutput;
}

char integerToStringOutput[128];
template<typename T>
const char* IntegerToString(T value) {

	uint_8 isNegative = 0;

	if (value < 0) {
		isNegative = 1;
		value *= -1;
		integerToStringOutput[0] = '-';
	}

	uint_8 size = 0;
	uint_64 sizeTester = (uint_64)value;
	while (sizeTester / 10 > 0) {
		sizeTester /= 10;
		size++;
	}

	uint_8 index = 0;
	uint_64 newValue = (uint_64)value;
	while (newValue / 10 > 0) {
		uint_8 remainder = newValue % 10;
		newValue /= 10;
		integerToStringOutput[isNegative + size - index] = remainder + 48; 
		index++;
	}
	uint_8 remainder = newValue % 10;
	integerToStringOutput[isNegative + size - index] = remainder + 48;
	integerToStringOutput[isNegative + size + 1] = 0;
	return integerToStringOutput;
}
