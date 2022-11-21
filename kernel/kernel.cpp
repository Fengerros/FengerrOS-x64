#include "../drivers/text_print.cpp"

extern "C" void _start(){
    SetCursorPosiition(1000);
    PrintString("hello :3", 0xa);
    return;
}