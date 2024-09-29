#include "defines.h"
#include "utility.h"
#include "gates/or_16.h"

InternalOr16* newInternalOr16() {
    S_MALLOC(ret, InternalOr16);
    ret->orA = newOr8();
    ret->orB = newOr8();
    ret->orC = newOr();
    return ret;
}

Or16* newOr16() {
    S_MALLOC(ret, Or16);
    AIF_MALLOC(ret->input, bit, 16, 0);
    ret->output = 0;
    ret->internal = newInternalOr16();
    return ret;
}

void propagateOr16(Or16* node) {
    memcpy(node->internal->orA->input, node->input, sizeof(bit) * 8);
    memcpy(node->internal->orB->input, node->input + 8, sizeof(bit) * 8);
    propagateOr8(node->internal->orA);
    propagateOr8(node->internal->orB);

    node->internal->orC->inputA = node->internal->orA->output;
    node->internal->orC->inputB = node->internal->orB->output;
    propagateOr(node->internal->orC);

    node->output = node->internal->orC->output;
}

void printOr16(Or16* node) {
    printf("Or16(input=0x");
    for (bit i = 0; i < 4; i++) {
        printf("%lx", bits2num(node->input + (3 - i) * 4, 4));
    }
    printf(", output=%d)\n", node->output);
}

void freeInternalOr16(InternalOr16* node) {
    freeOr8(node->orA);
    freeOr8(node->orB);
    freeOr(node->orC);
    free(node);
}

void freeOr16(Or16* node) {
    freeInternalOr16(node->internal);
    free(node->input);
    free(node);
}
