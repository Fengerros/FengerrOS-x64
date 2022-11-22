#include "../drivers/text_print.cpp"
#include "../drivers/colors.cpp"
#include "../drivers/IDT.cpp"
#include "../drivers/keyboard.cpp"


void loadning_wheel(uint_16 index, uint_8 color = FOREGROUND_LIGHTGREEN | BACKGROUND_BLACK){
    const char* wheel = "|/-\\";
    uint_8 wheel_index = 0;
    
    for (uint_32 i = 0; i < 50; i++)
    {
    
        SetCursorPosition(index);
        PrintString(&wheel[wheel_index], color);
            
        SetCursorPosition(index+1);
        PrintString("   ", color);
        SetCursorPosition(index+2);

        wheel_index++;
        if(wheel_index > 3){
            wheel_index = 0;
        }

        for(uint_32 i = 0; i < 300000; i++){
            asm("nop");
        }
    }
    SetCursorPosition(index);
    PrintString(" ", screen::foreground_color | screen::background_color);
    SetCursorPosition(index);
}