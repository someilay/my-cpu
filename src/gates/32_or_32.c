#include "utility.h"
#include "defines.h"
#include "gates/32_or_32.h"

InternalOr32to32* newInternalOr32to32() {
    S_MALLOC(ret, InternalOr32to32);
    AI_MALLOC(ret->ors, Or*, 32);
    for (bit i = 0; i < 32; i++) {
        ret->ors[i] = newOr();
    }
    return ret;
}

Or32to32* newOr32to32() {
    S_MALLOC(ret, Or32to32);
    AIF_MALLOC(ret->inputA, bit, 32, 0);
    AIF_MALLOC(ret->inputB, bit, 32, 0);
    AIF_MALLOC(ret->output, bit, 32, 0);
    ret->internal = newInternalOr32to32();
    return ret;
}

void propagateOr32to32(Or32to32* node) {
    for (bit i = 0; i < 32; i++) {
        node->internal->ors[i]->inputA = node->inputA[i];
        node->internal->ors[i]->inputB = node->inputB[i];
        propagateOr(node->internal->ors[i]);
        node->output[i] = node->internal->ors[i]->output;
    }
}

void printOr32to32(Or32to32* node) {
    printf("Or32to32(inputA=0x");
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

void freeInternalOr32to32(InternalOr32to32* node) {
    for (bit i = 0; i < 32; i++) {
        freeOr(node->ors[i]);
    }
    free(node->ors);
    free(node);
}

void freeOr32to32(Or32to32* node) {
    freeInternalOr32to32(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->output);
    free(node);
}
