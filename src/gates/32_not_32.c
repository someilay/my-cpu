#include "utility.h"
#include "defines.h"
#include "gates/32_not_32.h"

InternalNot32to32* newInternalNot32to32() {
    S_MALLOC(ret, InternalNot32to32);
    AI_MALLOC(ret->nots, Not*, 32);
    for (bit i = 0; i < 32; i++) {
        ret->nots[i] = newNot();
    }
    return ret;
}

Not32to32* newNot32to32() {
    S_MALLOC(ret, Not32to32);
    AIF_MALLOC(ret->input, bit, 32, 0);
    AIF_MALLOC(ret->output, bit, 32, 0);
    ret->internal = newInternalNot32to32();
    return ret;
}

void propagateNot32to32(Not32to32* node) {
    for (bit i = 0; i < 32; i++) {
        node->internal->nots[i]->input = node->input[i];
        propagateNot(node->internal->nots[i]);
        node->output[i] = node->internal->nots[i]->output;
    }
}

void printNot32to32(Not32to32* node) {
    printf("Not32to32(input=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->input + (7 - i) * 4, 4));
    }
    printf(", output=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->output + (7 - i) * 4, 4));
    }
    printf(")\n");
}

void freeInternalNot32to32(InternalNot32to32* node) {
    for (bit i = 0; i < 32; i++) {
        freeNot(node->nots[i]);
    }
    free(node->nots);
    free(node);
}

void freeNot32to32(Not32to32* node) {
    freeInternalNot32to32(node->internal);
    free(node->input);
    free(node->output);
    free(node);
}
