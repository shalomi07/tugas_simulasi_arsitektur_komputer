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
int Ep, Lm, Cp, Ce, Li, Ei, La, Lb, Eu;

void t1_t3 (){
    while (state != t4) {
    switch (state) {
        case t1:
            Ep = 1; // active high
            Lm = 0; // active low
            mar = pc;
            state = t2;
            break;
        case t2:
            Cp = 1; // active high
            pc++;
            state = t3;
            break;
        case t3:
            Ce = 0; // active low
            Li = 0; // active low
            ir = ram[mar];
            state = t4;
            break;
    }}

}

int ADD(int a){
    switch (state) {
        case t4:
            Lm = 0;      // LM active low
            Ei = 0;      // EI active low
            mar = ir & 0x0F; // IR -> MAR
            state = t5;
            break;

        case t5:
            Ce = 0;      // CE active low
            Lb = 0;      // LB active low
            B = ram[mar];    // RAM -> B
            state = t6;
            break;

        case t6:
            La = 0;      // LA active low
            Eu = 1;      // EU active high
            A = A + B;       // A + B -> A
            state = t1;
            break;
    }
}

int SUB(){}
int LDA(){}
int OUT(){}





































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