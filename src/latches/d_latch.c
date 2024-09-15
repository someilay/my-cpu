#include "defines.h"
#include "latches/d_latch.h"

InternalDLatch* newInternalDLatch(bit q) {
    S_MALLOC(ret, InternalDLatch);
    ret->andA = newAnd();
    ret->andB = newAnd();
    ret->notNode = newNot();
    ret->latch = newSrLatch(q);
    return ret;
}

DLatch* newDLatch(bit q) {
    S_MALLOC(ret, DLatch);
    ret->internal = newInternalDLatch(q);
    ret->clk = 0;
    ret->d = 0;
    ret->q = q;
    ret->notQ = !q;
    return ret;
}

void propagateDLatch(DLatch* node) {
    node->internal->notNode->input = node->d;
    propagateNot(node->internal->notNode);

    node->internal->andA->inputA = node->clk;
    node->internal->andA->inputB = node->internal->notNode->output;
    node->internal->andB->inputA = node->clk;
    node->internal->andB->inputB = node->d;
    propagateAnd(node->internal->andA);
    propagateAnd(node->internal->andB);

    node->internal->latch->reset = node->internal->andA->output;
    node->internal->latch->set = node->internal->andB->output;
    propagateSrLatch(node->internal->latch);

    node->q = node->internal->latch->q;
    node->notQ = node->internal->latch->notQ;
}

void printDLatch(DLatch* node) {
    printf("DLatch(clk=%d, d=%d, q=%d, notQ=%d)\n", node->clk, node->d, node->q, node->notQ);
}

void freeInternalDLatch(InternalDLatch* node) {
    freeAnd(node->andA);
    freeAnd(node->andB);
    freeNot(node->notNode);
    freeSrLatch(node->latch);
    free(node);
}

void freeDLatch(DLatch* node) {
    freeInternalDLatch(node->internal);
    free(node);
}
