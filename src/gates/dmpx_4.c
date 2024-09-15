#include "malloc.h"
#include "gates/dmpx_4.h"

InternalDeMultiplexer4* newInternalDeMultiplexer4() {
    InternalDeMultiplexer4* ret = (InternalDeMultiplexer4*)malloc(sizeof(InternalDeMultiplexer4));
    ret->dmpxA = newDmpx();
    ret->dmpxB = newDmpx();
    ret->dmpxC = newDmpx();
    return ret;
}

DeMultiplexer4* newDmpx4() {
    DeMultiplexer4* ret = (DeMultiplexer4*)malloc(sizeof(DeMultiplexer4));
    ret->internal = newInternalDeMultiplexer4();
    ret->outputs = (bit*)malloc(sizeof(bit) * 4);
    ret->input = 0;
    ret->selectA = 0;
    ret->selectB = 0;
    for (bit i = 0; i < 4; i++) {
        ret->outputs[i] = 0;
    }
    return ret;
}

void propagateDmpx4(DeMultiplexer4* node) {
    node->internal->dmpxA->input = node->input;
    node->internal->dmpxA->select = node->selectB;
    propagateDmpx(node->internal->dmpxA);

    node->internal->dmpxB->input = node->internal->dmpxA->outputA;
    node->internal->dmpxB->select = node->selectA;
    node->internal->dmpxC->input = node->internal->dmpxA->outputB;
    node->internal->dmpxC->select = node->selectA;
    propagateDmpx(node->internal->dmpxB);
    propagateDmpx(node->internal->dmpxC);

    node->outputs[0] = node->internal->dmpxB->outputA;
    node->outputs[1] = node->internal->dmpxB->outputB;
    node->outputs[2] = node->internal->dmpxC->outputA;
    node->outputs[3] = node->internal->dmpxC->outputB;
}

void printDmpx4(DeMultiplexer4* node) {
    printf(
        "DeMultiplexer4(input=%d, selectA=%d, selectB=%d, ",
        node->input, node->selectA, node->selectB
    );
    for (bit i = 0; i < 3; i++) {
        printf("output_%d = %d, ", i, node->outputs[i]);
    }
    printf("output_3 = %d)\n", node->outputs[3]);
}

void freeInternalDeMultiplexer4(InternalDeMultiplexer4* node) {
    freeDmpx(node->dmpxA);
    freeDmpx(node->dmpxB);
    freeDmpx(node->dmpxC);
    free(node);
}

void freeDmpx4(DeMultiplexer4* node) {
    freeInternalDeMultiplexer4(node->internal);
    free(node->outputs);
    free(node);
}
