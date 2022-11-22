#include "../drivers/text_print.cpp"
#include "../drivers/colors.cpp"
#include "../drivers/IDT.cpp"

extern const char ASCII_logo[];

extern "C" void _start(){
    InitIDT();
    ClearScreen(BACKGROUND_MAGENTA);

    SetCursorPosition(PositionFromCoordinates(0, 0));
    PrintStringFromFile(ASCII_logo, FOREGROUND_LIGHTGREEN | BACKGROUND_BLACK);
    SetCursorPosition(PositionFromCoordinates(0, 15));
    PrintString("Welcome to the OS!", FOREGROUND_LIGHTGREEN | BACKGROUND_BLUE);
    SetCursorPosition(PositionFromCoordinates(0, 16));
    PrintString("Press any key to continue...", FOREGROUND_LIGHTGREEN | BACKGROUND_BLUE);


    return;
}