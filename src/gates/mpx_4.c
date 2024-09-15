#include "malloc.h"
#include "gates/mpx_4.h"

InternalMultiplexer4* newInternalMultiplexer4() {
    InternalMultiplexer4* ret = (InternalMultiplexer4*)malloc(sizeof(InternalMultiplexer4));
    ret->mpxA = newMpx();
    ret->mpxB = newMpx();
    ret->mpxC = newMpx();
    return ret;
}

Multiplexer4* newMpx4() {
    Multiplexer4* ret = (Multiplexer4*)malloc(sizeof(Multiplexer4));
    ret->internal = newInternalMultiplexer4();
    ret->inputs = (bit*)malloc(sizeof(bit) * 4);
    ret->selectA = 0;
    ret->selectB = 0;
    ret->output = 0;
    for (bit i = 0; i < 4; i++) {
        ret->inputs[i] = 0;
    }
    return ret;
}

void propagateMpx4(Multiplexer4* node) {
    node->internal->mpxA->inputA = node->inputs[0];
    node->internal->mpxA->inputB = node->inputs[1];
    node->internal->mpxA->select = node->selectA;
    propagateMpx(node->internal->mpxA);

    node->internal->mpxB->inputA = node->inputs[2];
    node->internal->mpxB->inputB = node->inputs[3];
    node->internal->mpxB->select = node->selectA;
    propagateMpx(node->internal->mpxB);

    node->internal->mpxC->inputA = node->internal->mpxA->output;
    node->internal->mpxC->inputB = node->internal->mpxB->output;
    node->internal->mpxC->select = node->selectB;
    propagateMpx(node->internal->mpxC);

    node->output = node->internal->mpxC->output;
}

void printMpx4(Multiplexer4* node) {
    printf("Multiplexer4(");
    for (bit i = 0; i < 4; i++)
    {
        printf("input_%d = %d, ", i, node->inputs[i]);
    }
    printf("selectA = %d, selectB = %d, output = %d)\n", node->selectA, node->selectB, node->output);
}

void freeInternalMultiplexer4(InternalMultiplexer4* node) {
    freeMpx(node->mpxA);
    freeMpx(node->mpxB);
    freeMpx(node->mpxC);
    free(node);
}

void freeMpx4(Multiplexer4* node) {
    freeInternalMultiplexer4(node->internal);
    free(node->inputs);
    free(node);
}
