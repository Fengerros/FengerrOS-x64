#include "../drivers/text_print.cpp"
#include "../drivers/colors.cpp"

extern "C" void _start(){
    ClearScreen();

    SetCursorPosiition(PositionFromCoordinates(0, 0));
    PrintString("hello :3", FOREGROUND_LIGHTGREEN | BACKGROUND_BLACK);

    return;
}