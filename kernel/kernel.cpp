#include "../drivers/text_print.cpp"
#include "../drivers/colors.cpp"
#include "../drivers/IDT.cpp"
#include "../drivers/keyboard.cpp"
#include "../drivers/loading_animation.cpp"

extern const char ASCII_logo[];

extern "C" void _start(){
    
    screen::background_color = BACKGROUND_BLACK;
    screen::foreground_color = FOREGROUND_LIGHTGREEN;

    text::color = FOREGROUND_LIGHTGREEN;
    text::background_color = BACKGROUND_BLACK;

    InitIDT();
    MainKeyboardHandler = KeyboardHandler;

    ClearScreen(screen::foreground_color | screen::background_color);
    SetCursorPosition(PositionFromCoordinates(0, 0));
    PrintStringFromFile(ASCII_logo, FOREGROUND_LIGHTGREEN | BACKGROUND_BLACK);
    SetCursorPosition(PositionFromCoordinates(0, 10));
    PrintString("Welcome to the OS!", FOREGROUND_LIGHTGREEN | BACKGROUND_BLUE);
    SetCursorPosition(PositionFromCoordinates(0, 11));
    PrintString("Press any key to continue...\n\n\r", FOREGROUND_LIGHTGREEN | BACKGROUND_BLUE);
    PrintString("\\>", FOREGROUND_LIGHTGREEN | BACKGROUND_RED);
    PrintString(" ", FOREGROUND_LIGHTGREEN | BACKGROUND_BLACK);

    loadning_wheel(PositionFromCoordinates(45, 5));

    SetCursorPosition(PositionFromCoordinates(4, 13));
    InitIDT();
    MainKeyboardHandler = KeyboardHandler;

    return;
}