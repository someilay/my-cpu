#include "defines.h"
#include "arithmetic_units/8_bit_adder.h"

InternalBitAdder8* newInternalBitAdder8() {
    S_MALLOC(ret, InternalBitAdder8);
    ret->bitAdderA = newBitAdder4();
    ret->bitAdderB = newBitAdder4();
    return ret;
}

BitAdder8* newBitAdder8() {
    S_MALLOC(ret, BitAdder8);
    ret->internal = newInternalBitAdder8();
    AIF_MALLOC(ret->inputA, bit, 8, 0);
    AIF_MALLOC(ret->inputB, bit, 8, 0);
    AIF_MALLOC(ret->output, bit, 8, 0);
    ret->inputC = 0;
    ret->c = 0;
    return ret;
}

void propagateBitAdder8(BitAdder8* node) {
    memcpy(node->internal->bitAdderA->inputA, node->inputA, sizeof(bit) * 4);
    memcpy(node->internal->bitAdderA->inputB, node->inputB, sizeof(bit) * 4);
    memcpy(node->internal->bitAdderB->inputA, node->inputA + 4, sizeof(bit) * 4);
    memcpy(node->internal->bitAdderB->inputB, node->inputB + 4, sizeof(bit) * 4);

    node->internal->bitAdderA->inputC = node->inputC;
    propagateBitAdder4(node->internal->bitAdderA);

    node->internal->bitAdderB->inputC = node->internal->bitAdderA->c;
    propagateBitAdder4(node->internal->bitAdderB);

    node->c = node->internal->bitAdderB->c;
    memcpy(node->output, node->internal->bitAdderA->output, sizeof(bit) * 4);
    memcpy(node->output + 4, node->internal->bitAdderB->output, sizeof(bit) * 4);
}

void printBitAdder8(BitAdder8* node) {
    printf("BitAdder8(inputA=0b");
    for (bit i = 0; i < 8; i++) {
        printf("%d", node->inputA[7 - i]);
    }
    printf(", inputB=0b");
    for (bit i = 0; i < 8; i++) {
        printf("%d", node->inputB[7 - i]);
    }
    printf(", inputC=%d, output=0b", node->inputC);
    for (bit i = 0; i < 8; i++) {
        printf("%d", node->output[7 - i]);
    }
    printf(", c=%d)\n", node->c);
}

void freeInternalBitAdder8(InternalBitAdder8* node) {
    freeBitAdder4(node->bitAdderA);
    freeBitAdder4(node->bitAdderB);
    free(node);
}

void freeBitAdder8(BitAdder8* node) {
    freeInternalBitAdder8(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->output);
    free(node);
}
