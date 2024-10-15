#include "defines.h"
#include "utility.h"
#include "gates/dmpx_65kb.h"

InternalDeMultiplexer65kb* newInternalDeMultiplexer65kb() {
    S_MALLOC(ret, InternalDeMultiplexer65kb);
    AI_MALLOC(ret->dmpxS, DeMultiplexer256*, 256);
    for (int32_t i = 0; i < 256; i++) {
        ret->dmpxS[i] = newDmpx256();
    }
    ret->dmpxM = newDmpx256();
    return ret;
}

DeMultiplexer65kb* newDmpx65kb() {
    S_MALLOC(ret, DeMultiplexer65kb);
    AIF_MALLOC(ret->output, bit, 65536, 0);
    AIF_MALLOC(ret->select, bit, 16, 0);
    ret->internal = newInternalDeMultiplexer65kb();
    ret->input = 0;
    return ret;
}

void propagateDmpx65kb(DeMultiplexer65kb* node) {
    node->internal->dmpxM->input = node->input;
    memcpy(node->internal->dmpxM->select, node->select + 8, B8);
    propagateDmpx256(node->internal->dmpxM);
    for (int32_t i = 0; i < 256; i++) {
        node->internal->dmpxS[i]->input = node->internal->dmpxM->output[i];
        //memcpy(node->internal->dmpxS[i]->select, node->select, B8);
        propagateDmpx256(node->internal->dmpxS[i]);
        //memcpy(node->output + 256 * i, node->internal->dmpxS[i]->output, sizeof(bit) * 256);
    }
}

void printDmpx65kb(DeMultiplexer65kb* node) {
    printf("DeMultiplexer65kb(input=%d", node->input);
    printf(", select=0x");
    for (int32_t i = 0; i < 4; i++) {
        printf("%lx", bits2num(node->select + (3 - i) * 4, 4));
    }
    printf(", output=");
    bit isZero = 1;
    for (int32_t i = 0; i < 65536; i++) {
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

void freeInternalDeMultiplexer65kb(InternalDeMultiplexer65kb* node) {
    freeDmpx256(node->dmpxM);
    for (int32_t i = 0; i < 256; i++) {
        freeDmpx256(node->dmpxS[i]);
    }
    free(node->dmpxS);
    free(node);
}

void freeDmpx65kb(DeMultiplexer65kb* node) {
    freeInternalDeMultiplexer65kb(node->internal);
    free(node->select);
    free(node->output);
    free(node);
}
