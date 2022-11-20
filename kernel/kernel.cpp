#include "../drivers/text_print.cpp"

extern "C" void _start(){
    SetCursorPosiition(PositionFromCoordinates(0, 3));
    PrintString("Uruchomiono system...\n\rKernel...\n\rdziala!...\n\rWszystko dziala!\n\r");
    PrintString(IntegerToString(123));
    return;
}