#pragma once
#include "../drivers/text_print.cpp"
#include "../drivers/colors.cpp"
#include "../drivers/IDT.cpp"
#include "../kernel/typedefs.cpp"

bool LeftShiftPressed = false;
bool RightShiftPressed = false;
uint_8 LastScancode;

namespace text{
    uint_8 color = FOREGROUND_LIGHTGREEN;
    uint_8 background_color = BACKGROUND_BLACK;
}
void StandardKeyboardHandler(uint_8 scanCode, uint_8 chr, uint_8 color) {
	if (chr != 0) {
		switch (LeftShiftPressed | RightShiftPressed)
		{
		case true:
			PrintChar(chr - 32, color);
			break;
		case false:
			PrintChar(chr, color);
			break;
		}

	}
	else {
		switch (scanCode) {
		case 0x0E: //Backspace
			SetCursorPosition(CursorPosition - 1);
			PrintChar(' ', screen::foreground_color | screen::background_color);
			SetCursorPosition(CursorPosition - 1);
			break;
		case 0x2A: //Left Shift
			LeftShiftPressed = true;
			break;
		case 0xAA: //Left Shift Released
			LeftShiftPressed = false;
            break;
		case 0x36: //Right Shift
			RightShiftPressed = true;
			break;
		case 0xB6: //Right Shift Released
			RightShiftPressed = false;
			break;
		case 0x1C: //Enter
			PrintString("\n\r");
			break;
		}
	}
}

void KeyboardHandler0xE0(uint_8 scanCode) {
	switch (scanCode)
	{
	case 0x50:
		SetCursorPosition(CursorPosition + VGA_WIDTH);
		break;
	case 0x48:
		SetCursorPosition(CursorPosition - VGA_WIDTH);
		break;
    case 0x4B:
        SetCursorPosition(CursorPosition - 1);
        break;
    case 0x4D:
        SetCursorPosition(CursorPosition + 1);
        break;
	default:
		break;
	}

}

void KeyboardHandler(uint_8 scanCode, uint_8 chr, uint_8 color) {

	switch (LastScancode) {
	case 0xE0:
		KeyboardHandler0xE0(scanCode);
		break;
	default:
		StandardKeyboardHandler(scanCode, chr, text::color | text::background_color);
	}

	LastScancode = scanCode;
}