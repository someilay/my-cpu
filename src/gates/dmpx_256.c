#include "defines.h"
#include "utility.h"
#include "gates/dmpx_256.h"

InternalDeMultiplexer256* newInternalDeMultiplexer256() {
    S_MALLOC(ret, InternalDeMultiplexer256);
    AI_MALLOC(ret->dmpxS, DeMultiplexer16*, 16);
    for (int32_t i = 0; i < 16; i++) {
        ret->dmpxS[i] = newDmpx16();
    }
    ret->dmpxM = newDmpx16();
    return ret;
}

DeMultiplexer256* newDmpx256() {
    S_MALLOC(ret, DeMultiplexer256);
    AIF_MALLOC(ret->output, bit, 256, 0);
    AIF_MALLOC(ret->select, bit, 8, 0);
    ret->internal = newInternalDeMultiplexer256();
    ret->input = 0;
    return ret;
}

void propagateDmpx256(DeMultiplexer256* node) {
    node->internal->dmpxM->input = node->input;
    memcpy(node->internal->dmpxM->select, node->select + 4, B4);
    propagateDmpx16(node->internal->dmpxM);
    for (int32_t i = 0; i < 16; i++) {
        node->internal->dmpxS[i]->input = node->internal->dmpxM->output[i];
        memcpy(node->internal->dmpxS[i]->select, node->select, B4);
        propagateDmpx16(node->internal->dmpxS[i]);
        memcpy(node->output + 16 * i, node->internal->dmpxS[i]->output, B16);
    }
}

void printDmpx256(DeMultiplexer256* node) {
    printf("DeMultiplexer256(input=%d", node->input);
    printf(", select=0x%lx%lx", bits2num(node->select + 4, 4), bits2num(node->select, 4));
    printf(", output=");
    bit isZero = 1;
    for (int32_t i = 0; i < 256; i++) {
        if (node->output[i]) {
            printf("%d-th bit is one", i);
            isZero = 0;
            break;
        }
    }
    if (isZero) {
        printf("all zeros");
    }
    printf(")\n");
}

void freeInternalDeMultiplexer256(InternalDeMultiplexer256* node) {
    freeDmpx16(node->dmpxM);
    for (int32_t i = 0; i < 16; i++) {
        freeDmpx16(node->dmpxS[i]);
    }
    free(node->dmpxS);
    free(node);
}

void freeDmpx256(DeMultiplexer256* node) {
    freeInternalDeMultiplexer256(node->internal);
    free(node->select);
    free(node->output);
    free(node);
}
