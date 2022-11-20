#include "../drivers/text_print.cpp"

extern "C" void _start(){
    SetCursorPosiition(PositionFromCoordinates(10, 20));
    return;
}