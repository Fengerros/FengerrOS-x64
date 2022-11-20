#pragma once

void outb(unsigned short port, unsigned char data){
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

unsigned char inb(unsigned short port){
    unsigned char data;
    asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}