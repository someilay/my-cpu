#include "defines.h"
#include "utility.h"
#include "gates/or_8.h"

InternalOr8* newInternalOr8() {
    S_MALLOC(ret, InternalOr8);
    ret->orA = newOr4();
    ret->orB = newOr4();
    ret->orC = newOr();
    return ret;
}

Or8* newOr8() {
    S_MALLOC(ret, Or8);
    AIF_MALLOC(ret->input, bit, 8, 0);
    ret->output = 0;
    ret->internal = newInternalOr8();
    return ret;
}

void propagateOr8(Or8* node) {
    memcpy(node->internal->orA->inputs, node->input, sizeof(bit) * 4);
    memcpy(node->internal->orB->inputs, node->input + 4, sizeof(bit) * 4);
    propagateOr4(node->internal->orA);
    propagateOr4(node->internal->orB);

    node->internal->orC->inputA = node->internal->orA->output;
    node->internal->orC->inputB = node->internal->orB->output;
    propagateOr(node->internal->orC);

    node->output = node->internal->orC->output;
}

void printOr8(Or8* node) {
    printf("Or8(input=0x");
    for (bit i = 0; i < 2; i++) {
        printf("%lx", bits2num(node->input + (1 - i) * 4, 4));
    }
    printf(", output=%d)\n", node->output);
}

void freeInternalOr8(InternalOr8* node) {
    freeOr4(node->orA);
    freeOr4(node->orB);
    freeOr(node->orC);
    free(node);
}

void freeOr8(Or8* node) {
    freeInternalOr8(node->internal);
    free(node->input);
    free(node);
}
