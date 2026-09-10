#include <stdio.h>
typedef unsigned char byte;

typedef enum {t1, t2, t3, t4, t5, t6} state_t;
state_t state = t1;

byte pc = 0;
byte mar = 0;
byte A = 0;
byte B = 0;
byte ir = 0;
byte ram[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};


void t1_t3 (){
    int Ep, Lm, Cp, Ce, Li, Ei, La, Lb, Eu;
    while (state != t4) {
    switch (state) {
        case t1:
            
            mar = pc;
            state = t2;
            break;
        case t2:
            pc++;
            state = t3;
            break;
        case t3:
            ir = ram[mar];
            mar = ir & 0x0F; // Assuming lower 4 bits are the address
            state = t4;
            break;
    }}

}


































/*void main (){
    switch case (state) {
        case t1:
            mar = pc;
            state = t2;
            break;
        case t2:
            ir = ram[mar];
            pc++;
            state = t3;
            break;
        case t3:
            mar = ir & 0x0F; // Assuming lower 4 bits are the address
            state = t4;
            break;
        case t4:
            A = ram[mar];
            state = t5;
            break;
        case t5:
            B = A + 1; // Example operation
            state = t6;
            break;
        case t6:
            ram[mar] = B; // Store result back to RAM
            state = t1; // Reset to initial state
            break;
    }

}