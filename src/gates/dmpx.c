#include "malloc.h"
#include "gates/dmpx.h"

InternalDeMultiplexer* newInternalDeMultiplexer() {
    InternalDeMultiplexer* ret = (InternalDeMultiplexer*)malloc(sizeof(InternalDeMultiplexer));
    ret->andA = newAnd();
    ret->andB = newAnd();
    ret->notNode = newNot();
    return ret;
}

DeMultiplexer* newDmpx() {
    DeMultiplexer* ret = (DeMultiplexer*)malloc(sizeof(DeMultiplexer));
    ret->input = 0;
    ret->select = 0;
    ret->outputA = 0;
    ret->outputB = 0;
    ret->internal = newInternalDeMultiplexer();
    return ret;
}

void propagateDmpx(DeMultiplexer* node) {
    node->internal->notNode->input = node->select;
    propagateNot(node->internal->notNode);

    node->internal->andA->inputA = node->input;
    node->internal->andA->inputB = node->internal->notNode->output;
    node->internal->andB->inputA = node->input;
    node->internal->andB->inputB = node->select;
    propagateAnd(node->internal->andA);
    propagateAnd(node->internal->andB);

    node->outputA = node->internal->andA->output;
    node->outputB = node->internal->andB->output;
}

void printDmpx(DeMultiplexer* node) {
    printf(
        "DeMultiplexer(input=%d, select=%d, outputA=%d, outputB=%d)\n",
        node->input, node->select, node->outputA, node->outputB
    );
}

void freeInternalDeMultiplexer(InternalDeMultiplexer* node) {
    freeAnd(node->andA);
    freeAnd(node->andB);
    freeAnd(node->notNode);
    free(node);
}

void freeDmpx(DeMultiplexer* node) {
    freeInternalDeMultiplexer(node->internal);
    free(node);
}
