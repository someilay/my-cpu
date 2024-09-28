#include "defines.h"
#include "utility.h"
#include "arithmetic_units/32_bit_adder.h"

InternalBitAdder32* newInternalBitAdder32() {
    S_MALLOC(ret, InternalBitAdder32);
    AI_MALLOC(ret->adders, FullAdder*, 32);
    for (bit i = 0; i < 32; i++) {
        ret->adders[i] = newFullAdder();
    }
    return ret;
}

BitAdder32* newBitAdder32() {
    S_MALLOC(ret, BitAdder32);
    AIF_MALLOC(ret->inputA, bit, 32, 0);
    AIF_MALLOC(ret->inputB, bit, 32, 0);
    AIF_MALLOC(ret->output, bit, 32, 0);
    ret->inputC = 0;
    ret->c = 0;
    ret->internal = newInternalBitAdder32();
    return ret;
}

void propagateBitAdder32(BitAdder32* node) {
    bit c = node->inputC;
    for (bit i = 0; i < 32; i++) {
        node->internal->adders[i]->inputA = node->inputA[i];
        node->internal->adders[i]->inputB = node->inputB[i];
        node->internal->adders[i]->inputC = c;
        propagateFullAdder(node->internal->adders[i]);
        c = node->internal->adders[i]->c;
        node->output[i] = node->internal->adders[i]->s;
    }
    node->c = c;
}

void printBitAdder32(BitAdder32* node) {
    printf("BitAdder32(inputA=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputA + (7 - i) * 4, 4));
    }
    printf(", inputB=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputB + (7 - i) * 4, 4));
    }
    printf(", inputC=%d, output=0x", node->inputC);
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->output + (7 - i) * 4, 4));
    }
    printf(", c=%d)\n", node->c);
}

void freeInternalBitAdder32(InternalBitAdder32* node) {
    for (bit i = 0; i < 32; i++) {
        freeFullAdder(node->adders[i]);
    }
    free(node->adders);
    free(node);
}

void freeBitAdder32(BitAdder32* node) {
    freeInternalBitAdder32(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->output);
    free(node);
}
