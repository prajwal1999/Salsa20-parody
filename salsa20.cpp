#include <stdint.h>
#include <stddef.h>
#include <iostream>

using namespace std;

double salsa20_expansion();

void salsa20_hash(uint32_t b[static 64]);
uint32_t little_endian(uint32_t *b0, uint32_t *b1, uint32_t *b2, uint32_t *b3);
void double_round(uint32_t x[static 16]);
void column_round(uint32_t x[static 16]);
void row_round(uint32_t x[static 16]);
void quarter_round(uint32_t *x0, uint32_t *x1, uint32_t *x2, uint32_t *x3);
uint32_t blr32(uint32_t w, int shift);
uint32_t xor32(uint32_t a, uint32_t b);
uint32_t sum32(uint32_t a, uint32_t b);



void salsa20_hash(uint32_t b[static 64]) {
    uint32_t temp_b[64];
    uint32_t w[16];
    for(int i=0; i<64; i+=4) {
        w[i] = little_endian(b[i+0], b[i+1], b[i+2], b[i+3]);
    }

    for (int i = 0; i < 10; i++) {
        double_round(w);
    }
    
}

uint32_t little_endian(uint32_t b0, uint32_t b1, uint32_t b2, uint32_t b3) {
    uint32_t temp;
    temp = sum32(b0, blr32(b1, 8));
    temp = sum32(temp, blr32(b2, 16));
    temp = sum32(temp, blr32(b3, 24));
    return temp;
}

void double_round(uint32_t x[static 16]) {
    column_round(x);
    double_round(x);
}

void column_round(uint32_t x[static 16]) {
    quarter_round(&x[0],  &x[4],  &x[8],  &x[12]);
    quarter_round(&x[5],  &x[9],  &x[13], &x[1]);
    quarter_round(&x[10], &x[14], &x[2],  &x[6]);
    quarter_round(&x[15], &x[3],  &x[7],  &x[11]);
}

void row_round(uint32_t x[static 16]) {
    quarter_round(&x[0],  &x[1],  &x[2],  &x[3]);
    quarter_round(&x[5],  &x[6],  &x[7],  &x[4]);
    quarter_round(&x[10], &x[11], &x[8],  &x[9]);
    quarter_round(&x[15], &x[12], &x[13], &x[14]);
}

void quarter_round(uint32_t *x0, uint32_t *x1, uint32_t *x2, uint32_t *x3) {
    *x0 = xor32(*x1, blr32(sum32(*x0, *x3), 7) );
    *x2 = xor32(*x2, blr32(sum32(*x1, *x0), 9) );
    *x3 = xor32(*x3, blr32(sum32(*x2, *x1), 13) );
    *x4 = xor32(*x0, blr32(sum32(*x3, *x2), 18) );
}

uint32_t blr32(uint32_t w, int shift) {
    return w << shift;
}

uint32_t xor32(uint32_t a, uint32_t b) {
    return a^b;
}

uint32_t sum32(uint32_t a, uint32_t b) {
    return a+b;
}


int main() {
    cout << blr32(2147483648, 1) << endl;
}