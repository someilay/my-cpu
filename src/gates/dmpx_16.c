#include "defines.h"
#include "utility.h"
#include "gates/dmpx_16.h"

InternalDeMultiplexer16* newInternalDeMultiplexer16() {
    S_MALLOC(ret, InternalDeMultiplexer16);
    AI_MALLOC(ret->dmpxS, DeMultiplexer4*, 4);
    for (bit i = 0; i < 4; i++) {
        ret->dmpxS[i] = newDmpx4();
    }
    ret->dmpxM = newDmpx4();
    return ret;
}

DeMultiplexer16* newDmpx16() {
    S_MALLOC(ret, DeMultiplexer16);
    AIF_MALLOC(ret->output, bit, 16, 0);
    AIF_MALLOC(ret->select, bit, 4, 0);
    ret->internal = newInternalDeMultiplexer16();
    ret->input = 0;
    return ret;
}

void propagateDmpx16(DeMultiplexer16* node) {
    node->internal->dmpxM->selectA = node->select[2];
    node->internal->dmpxM->selectB = node->select[3];
    node->internal->dmpxM->input = node->input;
    propagateDmpx4(node->internal->dmpxM);
    for (bit i = 0; i < 4; i++) {
        node->internal->dmpxS[i]->selectA = node->select[0];
        node->internal->dmpxS[i]->selectB = node->select[1];
        node->internal->dmpxS[i]->input = node->internal->dmpxM->outputs[i];
        propagateDmpx4(node->internal->dmpxS[i]);
        memcpy(node->output + 4 * i, node->internal->dmpxS[i]->outputs, B4);
    }
}

void printDmpx16(DeMultiplexer16* node) {
    printf("DeMultiplexer16(input=%d", node->input);
    printf(", select=0x%lx", bits2num(node->select, 4));
    printf(", output=0x");
    for (bit i = 0; i < 4; i++) {
        printf("%lx", bits2num(node->output + (3 - i) * 4, 4));
    }
    printf(")\n");
}

void freeInternalDeMultiplexer16(InternalDeMultiplexer16* node) {
    freeDmpx4(node->dmpxM);
    for (bit i = 0; i < 4; i++) {
        freeDmpx4(node->dmpxS[i]);
    }
    free(node->dmpxS);
    free(node);
}

void freeDmpx16(DeMultiplexer16* node) {
    freeInternalDeMultiplexer16(node->internal);
    free(node->select);
    free(node->output);
    free(node);
}
