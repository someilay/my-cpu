#include "malloc.h"
#include "gates/mpx.h"

InternalMultiplexer* newInternalMultiplexer() {
    InternalMultiplexer* ret = (InternalMultiplexer*) malloc(sizeof(InternalMultiplexer));
    ret->andA = newAnd();
    ret->andB = newAnd();
    ret->notNode = newNot();
    ret->orNode = newOr();
    return ret;
}

Multiplexer* newMpx() {
    Multiplexer* ret = (Multiplexer*) malloc(sizeof(Multiplexer));
    ret->inputA = 0;
    ret->inputB = 0;
    ret->select = 0;
    ret->output = 0;
    ret->internal = newInternalMultiplexer();
    return ret;
}

void propagateMpx(Multiplexer* node) {
    node->internal->notNode->input = node->select;

    propagateNot(node->internal->notNode);

    node->internal->andA->inputA = node->inputA;
    node->internal->andA->inputB = node->internal->notNode->output;
    node->internal->andB->inputA = node->inputB;
    node->internal->andB->inputB = node->select;

    propagateAnd(node->internal->andA);
    propagateAnd(node->internal->andB);

    node->internal->orNode->inputA = node->internal->andA->output;
    node->internal->orNode->inputB = node->internal->andB->output;

    propagateOr(node->internal->orNode);

    node->output = node->internal->orNode->output;
}

void printMpx(Multiplexer* node) {
    printf(
        "Multiplexer(inputA=%d, inputB=%d, select=%d, output=%d)\n",
        node->inputA, node->inputB, node->select, node->output
    );
}

void freeInternalMultiplexer(InternalMultiplexer* node) {
    freeAnd(node->andA);
    freeAnd(node->andB);
    freeNot(node->notNode);
    freeOr(node->orNode);
    free(node);
}

void freeMpx(Multiplexer* node) {
    freeInternalMultiplexer(node->internal);
    free(node);
}
