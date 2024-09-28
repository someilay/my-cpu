#include "utility.h"
#include "defines.h"
#include "gates/32_mpx_4_32.h"

InternalMultiplexer4x32to32* newInternalMultiplexer4x32to32() {
    S_MALLOC(ret, InternalMultiplexer4x32to32);
    AI_MALLOC(ret->mpxs, Multiplexer4*, 32);
    for (bit i = 0; i < 32; i++) {
        ret->mpxs[i] = newMpx4();
    }
    return ret;
}

Multiplexer4x32to32* newMpx4x32to32() {
    S_MALLOC(ret, Multiplexer4x32to32);
    AI_MALLOC(ret->input, bit*, 4);
    AIF_MALLOC(ret->output, bit, 32, 0);
    ret->selectA = 0;
    ret->selectB = 0;
    ret->internal = newInternalMultiplexer4x32to32();
    for (bit i = 0; i < 4; i++) {
        AIF_MALLOC(ret->input[i], bit, 32, 0);
    }
    return ret;
}

void propagateMpx4x32to32(Multiplexer4x32to32* node) {
    for (bit i = 0; i < 32; i++) {
        for (bit j = 0; j < 4; j++) {
            node->internal->mpxs[i]->inputs[j] = node->input[j][i];
        }
        node->internal->mpxs[i]->selectA = node->selectA;
        node->internal->mpxs[i]->selectB = node->selectB;
        propagateMpx4(node->internal->mpxs[i]);
        node->output[i] = node->internal->mpxs[i]->output;
    }
}

void printMpx4x32to32(Multiplexer4x32to32* node) {
    printf("Multiplexer4x32to32(");
    for (bit j = 0; j < 4; j++) {
        if (j > 0) {
            printf(", ");
        }
        printf("input_%d=0x", j);
        for (bit i = 0; i < 8; i++) {
            printf("%lx", bits2num(node->input[j] + (7 - i) * 4, 4));
        }
    }
    printf(", selectA=%d, selectB=%d, output=0x", node->selectA, node->selectB);
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->output + (7 - i) * 4, 4));
    }
    printf(")\n");
}

void freeInternalMultiplexer4x32to32(InternalMultiplexer4x32to32* node) {
    for (bit i = 0; i < 32; i++) {
        freeMpx4(node->mpxs[i]);
    }
    free(node->mpxs);
    free(node);
}

void freeMpx4x32to32(Multiplexer4x32to32* node) {
    freeInternalMultiplexer4x32to32(node->internal);
    for (bit i = 0; i < 4; i++) {
        free(node->input[i]);
    }
    free(node->input);
    free(node->output);
    free(node);
}
