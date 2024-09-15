#include "defines.h"
#include "latches/sr_latch.h"

InternalSrLatch* newInternalSrLatch() {
    S_MALLOC(ret, InternalSrLatch);
    ret->norA = newNor();
    ret->norB = newNor();
    ret->norB->inputA = 1;
    ret->norB->output = 0;
    return ret;
}

void subPropagateSrLatch(SrLatch* node) {
    node->internal->norA->inputA = node->reset;
    node->internal->norA->inputB = node->internal->norB->output;
    node->internal->norB->inputA = node->internal->norA->output;
    node->internal->norB->inputB = node->set;
    propagateNor(node->internal->norA);
    propagateNor(node->internal->norB);
}

SrLatch* newSrLatch(bit q) {
    S_MALLOC(ret, SrLatch);
    ret->internal = newInternalSrLatch();
    ret->reset = 0;
    ret->set = 0;
    ret->q = q;
    ret->notQ = !q;
    ret->internal->norA->output = q;
    ret->internal->norB->output = !q;
    subPropagateSrLatch(ret);
    return ret;
}

void propagateSrLatch(SrLatch* node) {
    subPropagateSrLatch(node);
    subPropagateSrLatch(node);
    node->q = node->internal->norA->output;
    node->notQ = node->internal->norB->output;
}

void printSrLatch(SrLatch* node) {
    printf("SrLatch(reset=%d, set=%d, q=%d, notQ=%d)\n", node->reset, node->set, node->q, node->notQ);
}

void freeInternalSrLatch(InternalSrLatch* node) {
    freeNor(node->norA);
    freeNor(node->norB);
    free(node);
}

void freeSrLatch(SrLatch* node) {
    freeInternalSrLatch(node->internal);
    free(node);
}
