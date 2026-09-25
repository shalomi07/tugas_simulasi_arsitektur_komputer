#include <stdio.h>
#include <stdint.h>

typedef enum {t1, t2, t3, t4, t5, t6} state_t;

state_t initial_state = t1;
state_t state, current_state;

uint8_t pc = 0;
uint8_t mar = 0;
uint8_t A = 0;
uint8_t B = 0;
uint8_t ir = 0;

uint8_t ram[16] = {
    0x05, // LDA 5 = 0000 0101
    0x16, // ADD 6 = 0001 0110 
    0x27, // SUB 7 = 0010 0111
    0xE0, 
    0xF0,
    20, 
    15, 
    2, 
    0x00, 
    0x00,
    0x00, 
    0x00, 
    0x00, 
    0x00, 
    0x00, 
    0x00
    // LDA = 0x0
    // ADD = 0x1
    // SUB = 0x2
};

int Ep, Lm, Cp, Ce, Li, Ei, La, Lb, Eu, Lo, Ea, Su;


uint8_t decode(void) {
    return (ir >> 4) & 0x0F;
}

state_t state_machine (state_t current_state){
    // jika terima HLT, sampai t3 saja
    // jika terima OUT, sampai t4 saja
    uint8_t opcode = decode();

    switch (current_state) {
        case t1:
            Ep = 1;
            Lm = 0;
            mar = pc;

            printf("T1 : PC -> MAR\n");
            printf("     Ep = 1\n");
            printf("     Lm = 0\n");

            break;

        case t2:
            Cp = 1;
            pc++;

            printf("T2 : PC + 1\n");
            printf("     Cp = 1\n");

            break;

        case t3:
            if (opcode == 0xF) {
                printf("Instruksi : HLT\n");
                printf("\n======== PROGRAM SELESAI ========\n");
                printf("Hasil akhir A = %d\n", A);
                state = t1; // kembali ke state awal
                break;
            }
            Ce = 0;
            Li = 0;
            ir = ram[mar];

            printf("T3 : RAM -> IR\n");
            printf("     Ce = 0\n");
            printf("     Li = 0\n");

            break;

        case t4:
            if (opcode == 0x0){
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                break;
            } else if (opcode == 0x1){
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                break;
            } else if (opcode == 0x2){
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                break;
            } else if (opcode == 0xE){
                Lo = 0;
                printf("Output = %d\n", A);
                break;
            }

        case t5:
             if (opcode == 0x0){
                Ce = 0;
                La = 0;
                A = ram[mar];
                break;
            } else if (opcode == 0x1){
                Ce = 0;
                Lb = 0;
                B = ram[mar];
                break;
            } else if (opcode == 0x2){
                Ce = 0;
                Lb = 0;
                B = ram[mar];
                break;
            }

        case t6:
             if (opcode == 0x0){
                LDA();
            } else if (opcode == 0x1){
                La = 0;
                Eu = 1;
                A = A + B;
                break;
            } else if (opcode == 0x2){
                La = 0;
                Eu = 1;
                Su = 1;
                A = A - B;
                break;
            }
        default:
            printf("Instruksi tidak dikenal.\n");
            break;


    }
    if (opcode == 0xF || opcode == 0xE || current_state == t6 || current_state == t3 || current_state == t4) {
        return t1;
    } else {
        return current_state + 1;
    }
}

void simulate_state(state_t state){
    while (1){
        current_state = state_machine(state);
    }
}

void main(){
    state_t current_state = initial_state;
    simulate_state(current_state);
}

// bedanya ADD & SUB = SUB ada sinyal Su untuk invers (komplemen)