#include "defines.h"
#include "arithmetic_units/4_bit_adder.h"

InternalBitAdder4* newInternalBitAdder4() {
    S_MALLOC(ret, InternalBitAdder4);
    AI_MALLOC(ret->adders, FullAdder*, 4);
    for (bit i = 0; i < 4; i++) {
        ret->adders[i] = newFullAdder();
    }
    return ret;
}

BitAdder4* newBitAdder4() {
    S_MALLOC(ret, BitAdder4);
    ret->internal = newInternalBitAdder4();
    AIF_MALLOC(ret->inputA, bit, 4, 0);
    AIF_MALLOC(ret->inputB, bit, 4, 0);
    AIF_MALLOC(ret->output, bit, 4, 0);
    ret->inputC = 0;
    ret->c = 0;
    return ret;
}

void propagateBitAdder4(BitAdder4* node) {
    bit carry = node->inputC;
    for (bit i = 0; i < 4; i++) {
        node->internal->adders[i]->inputA = node->inputA[i];
        node->internal->adders[i]->inputB = node->inputB[i];
        node->internal->adders[i]->inputC = carry;
        propagateFullAdder(node->internal->adders[i]);
        carry = node->internal->adders[i]->c;
        node->output[i] = node->internal->adders[i]->s;
    }
    node->c = carry;
}

void printBitAdder4(BitAdder4* node) {
    printf("BitAdder4(inputA=0b");
    for (bit i = 0; i < 4; i++) {
        printf("%d", node->inputA[3 - i]);
    }
    printf(", inputB=0b");
    for (bit i = 0; i < 4; i++) {
        printf("%d", node->inputB[3 - i]);
    }
    printf(", inputC=%d, output=0b", node->inputC);
    for (bit i = 0; i < 4; i++) {
        printf("%d", node->output[3 - i]);
    }
    printf(", c=%d)\n", node->c);
}

void freeInternalBitAdder4(InternalBitAdder4* node) {
    for (bit i = 0; i < 4; i++) {
        freeFullAdder(node->adders[i]);
    }
    free(node->adders);
    free(node);
}

void freeBitAdder4(BitAdder4* node) {
    freeInternalBitAdder4(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->output);
    free(node);
}
