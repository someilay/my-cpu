#include "defines.h"
#include "latches/d_flip_flop.h"

InternalDFlipFlop* newInternalDFlipFlop(bit q) {
    S_MALLOC(ret, InternalDFlipFlop);
    ret->dLatchA = newDLatch(q);
    ret->dLatchB = newDLatch(q);
    ret->notNode = newNot();
    return ret;
}

DFlipFlop* newDFlipFlop(bit q) {
    S_MALLOC(ret, DFlipFlop);
    ret->internal = newInternalDFlipFlop(q);
    ret->d = 0;
    ret->clk = 0;
    ret->q = q;
    ret->notQ = !q;
    propagateDFlipFlop(ret);
    return ret;
}

void propagateDFlipFlop(DFlipFlop* node) {
    node->internal->notNode->input = node->clk;
    propagateNot(node->internal->notNode);

    node->internal->dLatchA->clk = node->internal->notNode->output;
    node->internal->dLatchA->d = node->d;
    propagateDLatch(node->internal->dLatchA);

    node->internal->dLatchB->clk = node->clk;
    node->internal->dLatchB->d = node->internal->dLatchA->q;
    propagateDLatch(node->internal->dLatchB);

    node->q = node->internal->dLatchB->q;
    node->notQ = node->internal->dLatchB->notQ;
}

void printDFlipFlop(DFlipFlop* node) {
    printf("DFlipFlop(clk=%d, d=%d, q=%d, notQ=%d)\n", node->clk, node->d, node->q, node->notQ);
}

void freeInternalDFlipFlop(InternalDFlipFlop* node) {
    freeDLatch(node->dLatchA);
    freeDLatch(node->dLatchB);
    freeNot(node->notNode);
    free(node);
}

void freeDFlipFlop(DFlipFlop* node) {
    freeInternalDFlipFlop(node->internal);
    free(node);
}
