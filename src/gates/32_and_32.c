#include "utility.h"
#include "defines.h"
#include "gates/32_and_32.h"

InternalAnd32to32* newInternalAnd32to32() {
    S_MALLOC(ret, InternalAnd32to32);
    AI_MALLOC(ret->ands, And*, 32);
    for (bit i = 0; i < 32; i++) {
        ret->ands[i] = newAnd();
    }
    return ret;
}

And32to32* newAnd32to32() {
    S_MALLOC(ret, And32to32);
    AIF_MALLOC(ret->inputA, bit, 32, 0);
    AIF_MALLOC(ret->inputB, bit, 32, 0);
    AIF_MALLOC(ret->output, bit, 32, 0);
    ret->internal = newInternalAnd32to32();
    return ret;
}

void propagateAnd32to32(And32to32* node) {
    for (bit i = 0; i < 32; i++) {
        node->internal->ands[i]->inputA = node->inputA[i];
        node->internal->ands[i]->inputB = node->inputB[i];
        propagateAnd(node->internal->ands[i]);
        node->output[i] = node->internal->ands[i]->output;
    }
}

void printAnd32to32(And32to32* node) {
    printf("And32to32(inputA=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputA + (7 - i) * 4, 4));
    }
    printf(", inputB=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputB + (7 - i) * 4, 4));
    }
    printf(", output=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->output + (7 - i) * 4, 4));
    }
    printf(")\n");
}

void freeInternalAnd32to32(InternalAnd32to32* node) {
    for (bit i = 0; i < 32; i++) {
        freeAnd(node->ands[i]);
    }
    free(node->ands);
    free(node);
}

void freeAnd32to32(And32to32* node) {
    freeInternalAnd32to32(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->output);
    free(node);
}
