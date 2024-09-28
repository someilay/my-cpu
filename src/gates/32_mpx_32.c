#include "utility.h"
#include "defines.h"
#include "gates/32_mpx_32.h"

InternalMultiplexer32to32* newInternalMultiplexer32to32() {
    S_MALLOC(ret, InternalMultiplexer32to32);
    AI_MALLOC(ret->mpxs, Multiplexer*, 32);
    for (bit i = 0; i < 32; i++) {
        ret->mpxs[i] = newMpx();
    }
    return ret;
}

Multiplexer32to32* newMpx32to32() {
    S_MALLOC(ret, Multiplexer32to32);
    AIF_MALLOC(ret->inputA, bit, 32, 0);
    AIF_MALLOC(ret->inputB, bit, 32, 0);
    AIF_MALLOC(ret->output, bit, 32, 0);
    ret->select = 0;
    ret->internal = newInternalMultiplexer32to32();
    return ret;
}

void propagateMpx32to32(Multiplexer32to32* node) {
    for (bit i = 0; i < 32; i++) {
        node->internal->mpxs[i]->inputA = node->inputA[i];
        node->internal->mpxs[i]->inputB = node->inputB[i];
        node->internal->mpxs[i]->select = node->select;
        propagateMpx(node->internal->mpxs[i]);
        node->output[i] = node->internal->mpxs[i]->output;
    }
}

void printMpx32to32(Multiplexer32to32* node) {
    printf("Multiplexer32to32(inputA=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputA + (7 - i) * 4, 4));
    }
    printf(", inputB=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputB + (7 - i) * 4, 4));
    }
    printf(", select=%d, output=0x", node->select);
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->output + (7 - i) * 4, 4));
    }
    printf(")\n");
}

void freeInternalMultiplexer32to32(InternalMultiplexer32to32* node) {
    for (bit i = 0; i < 32; i++) {
        freeMpx(node->mpxs[i]);
    }
    free(node->mpxs);
    free(node);
}

void freeMpx32to32(Multiplexer32to32* node) {
    freeInternalMultiplexer32to32(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->output);
    free(node);
}
