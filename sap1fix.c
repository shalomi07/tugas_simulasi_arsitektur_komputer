#include <stdio.h>
#include <stdint.h>

typedef enum {t1, t2, t3, t4, t5, t6} state_t;

state_t state = t1;

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
};

int Ep, Lm, Cp, Ce, Li, Ei, La, Lb, Eu, Lo, Ea, Su;

// harusnya per t
// tidak usah fungsi fetch


void fetch(void) {
    switch (state) {
        // 1 = active high
        // 0 = active low
        case t1:
            Ep = 1;
            Lm = 0;
            mar = pc;

            printf("T1 : PC -> MAR\n");
            printf("     Ep = 1\n");
            printf("     Lm = 0\n");

            state = t2;
            break;

        case t2:
            Cp = 1;
            pc++;

            printf("T2 : PC + 1\n");
            printf("     Cp = 1\n");

            state = t3;
            break;

        case t3:
            Ce = 0;
            Li = 0;
            ir = ram[mar];

            printf("T3 : RAM -> IR\n");
            printf("     Ce = 0\n");
            printf("     Li = 0\n");

            state = t4;
            break;
    }
}

uint8_t decode(void) {
    return (ir >> 4) & 0x0F;
}

void LDA(void) {
    while (state != t1) {
        switch (state) {

            case t4:
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                state = t5;
                break;

            case t5:
                Ce = 0;
                La = 0;
                A = ram[mar];
                state = t6;
                break;

            case t6:
                state = t1;
                break;

            default:
                break;
        }
    }
}
/*void ADD_SUB(void) {
    uint8_t opcode = decode();
    while (state != t1) {
        switch (state) {
            case t4:
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                state = t5;
                break;

            case t5:
                Ce = 0;
                Lb = 0;
                B = ram[mar];
                state = t6;
                break;

            case t6:
                La = 0;
                Eu = 1;

                if (opcode == 0x1) {
                    // ADD
                    Su = 0;
                    A = A + B;
                } else if (opcode == 0x2) {
                    // SUB
                    Su = 1;
                    A = A - B;
                }
                state = t1;
                break;
            }
        }
    } */

void ADD(void) {
    while (state != t1) {
        switch (state) {

            case t4:
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                state = t5;
                break;

            case t5:
                Ce = 0;
                Lb = 0;
                B = ram[mar];
                state = t6;
                break;

            case t6:
                La = 0;
                Eu = 1;
                A = A + B;
                state = t1;
                break;

            default:
                break;
        }
    }
}

void SUB(void) {
    while (state != t1) {
        switch (state) {

            case t4:
                Lm = 0;
                Ei = 0;
                mar = ir & 0x0F;
                state = t5;
                break;

            case t5:
                Ce = 0;
                Lb = 0;
                B = ram[mar];
                state = t6;
                break;

            case t6:
                La = 0;
                Eu = 1;
                Su = 1;
                A = A - B;
                state = t1;
                break;

            default:
                break;
        }
    }
}


void OUT(void) {
    switch (state) {

        case t4:
            Lo = 0;
            printf("Output = %d\n", A);
            state = t1;
            break;

        default:
            break;
    }
}



void execute(void) {
    uint8_t opcode = decode();

    switch (opcode) {

        case 0x0:
            LDA();
            break;

        /* case 0x1:
        case 0x2:
            ADD_SUB();
            break; */
        
        case 0x1:
            ADD();
            break;

        case 0x2:
            SUB();
            break;

        case 0xE:
            OUT();
            break;

        case 0xF:
            printf("HLT\n");
            break;
    }
}

int main(void) {
    printf("======== PROGRAM SIMULASI KOMPUTER SAP-1 ========\n\n");

    printf("0 : LDA 5\n");
    printf("1 : ADD 6\n");
    printf("2 : SUB 7\n");
    printf("3 : OUT\n");
    printf("4 : HLT\n");
    printf("5 : %d\n", ram[5]);
    printf("6 : %d\n", ram[6]);
    printf("7 : %d\n\n", ram[7]);

    printf("======== PROSES ========\n");

    while (1) {

        printf("\nPC = %d\n", pc);

        fetch();

        fetch();

        fetch();

        
        uint8_t opcode = decode();

        printf("IR = 0x%02X\n", ir);


        if (opcode == 0xF) {
            printf("Instruksi : HLT\n");
            printf("\n======== PROGRAM SELESAI ========\n");
            printf("Hasil akhir A = %d\n", A);
            break;
        }


        switch (opcode) {
            case 0x0:
                printf("Instruksi : LDA %d\n", ir & 0x0F);
                printf("T4-T6 : LDA\n");
                execute();
                printf("A = %d\n", A);
                break;

            /*case 0x1:
            case 0x2:
                printf("Instruksi : %s %d\n", (opcode == 0x1) ? "ADD" : "SUB", ir & 0x0F);
                printf("T4-T6 : %s\n", (opcode == 0x1) ? "ADD" : "SUB");
                execute();
                printf("A = %d\n", A);
                break; */
            
            case 0x1:
                printf("Instruksi : ADD %d\n", ir & 0x0F);
                printf("T4-T6 : ADD\n");
                execute();
                printf("A = %d\n", A);
                break;

            case 0x2:
                printf("Instruksi : SUB %d\n", ir & 0x0F);
                printf("T4-T6 : SUB\n");
                execute();
                printf("A = %d\n", A);
                break;

            case 0xE:
                printf("Instruksi : OUT\n");
                printf("T4 : A -> Output\n");
                execute();
                break;

            default:
                printf("Instruksi tidak dikenal.\n");
                return 1;
        }
    }

    return 0;
}