#include <stdio.h>
typedef unsigned char byte;

typedef enum {t1, t2, t3, t4, t5, t6} state_t;
state_t state = t1;

byte pc = 0;
byte mar = 0;
byte A = 0;
byte B = 0;
byte ir = 0;
// 
byte ram[16] = {};
int Ep, Lm, Cp, Ce, Li, Ei, La, Lb, Eu, Lo, Ea;

// tidak ada input, langsung output karena tidak ada instruksi input
// ubah LDA jadi biner atau hexa
// prof mau keliatan waktu LDA 0000 misalnya itu apa yang terjadi di t1-t6

void t1_t3 (){
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
    }

}

int ADD(){
    t1_t3();
    if (state == t4) {
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
    }}
}

int SUB(){
    t1_t3();
    switch (state) {
        if (state == t4) {    
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
                A = A - B;       
                state = t1;
                break;
            // perlu diklarifikasi ulang apakah benar utk case ini
    }}
}
int LDA(){
    t1_t3();
    if (state == t4) {
        switch (state) {
            case t4:
                Lm = 0;      // Lm active low
                Ei = 0;      // Ei active low
                mar = ir & 0x0F; // IR -> MAR
                state = t5;
                break;

            case t5:
                Ce = 0;      // Ce active low
                La = 0;      // La active low
                A = ram[mar];    // RAM -> B
                state = t6;
                break;

            case t6:
                // tidak ada operasi tambahan, kembali ke state awal
                state = t1;
                break;
    }}
}
int OUT(){
    t1_t3();
    if (state == t4) {
        Lo = 0;      // Lm active low
        Ea = 1;      // Ei active low
        mar = ir & 0x0F; // IR -> MAR
        state = t1;
    }
}

int main (){
   printf("0 LDA XXXX");

}


























/*koreksi

mengacu ke pdf prof halaman bawaan 160/162 yang ada dua tabel
tabel kanan:
content = mulai siklus t4 di mana
address = berurutan dari 0 sampai F


tabel kiri:
address = berurutan siklus untuk fetch cycle dan semua instruksi (misal content LDA kan 0011 = 3, jadi di tabel kiri ini LDA siklus t nya mulai di 3H)


*/