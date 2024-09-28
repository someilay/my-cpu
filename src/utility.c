#include "utility.h"

void num2bits(uint64_t num, bit* bits, uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
        bits[i]= (num >> i) & 1;
    }
}

uint64_t bits2num(bit* bits, uint64_t size) {
    uint64_t res = 0;
    for (uint64_t i = 0; i < size; i++) {
        res += ((uint64_t) bits[i]) << i;
    }
    return res;
}
