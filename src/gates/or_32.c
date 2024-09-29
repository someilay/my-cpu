#include "defines.h"
#include "utility.h"
#include "gates/or_32.h"

InternalOr32* newInternalOr32() {
    S_MALLOC(ret, InternalOr32);
    ret->orA = newOr16();
    ret->orB = newOr16();
    ret->orC = newOr();
    return ret;
}

Or32* newOr32() {
    S_MALLOC(ret, Or32);
    AIF_MALLOC(ret->input, bit, 32, 0);
    ret->output = 0;
    ret->internal = newInternalOr32();
    return ret;
}

void propagateOr32(Or32* node) {
    memcpy(node->internal->orA->input, node->input, sizeof(bit) * 16);
    memcpy(node->internal->orB->input, node->input + 16, sizeof(bit) * 16);
    propagateOr16(node->internal->orA);
    propagateOr16(node->internal->orB);

    node->internal->orC->inputA = node->internal->orA->output;
    node->internal->orC->inputB = node->internal->orB->output;
    propagateOr(node->internal->orC);

    node->output = node->internal->orC->output;
}

void printOr32(Or32* node) {
    printf("Or32(input=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->input + (7 - i) * 4, 4));
    }
    printf(", output=%d)\n", node->output);
}

void freeInternalOr32(InternalOr32* node) {
    freeOr16(node->orA);
    freeOr16(node->orB);
    freeOr(node->orC);
    free(node);
}

void freeOr32(Or32* node) {
    freeInternalOr32(node->internal);
    free(node->input);
    free(node);
}
