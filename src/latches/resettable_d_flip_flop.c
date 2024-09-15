#include "defines.h"
#include "latches/resettable_d_flip_flop.h"

InternalResettableDFlipFlop* newInternalResettableDFlipFlop(bit q) {
    S_MALLOC(ret, InternalResettableDFlipFlop);
    ret->dFlipFlopNode = newDFlipFlop(q);
    ret->andNode = newAnd();
    ret->notNode = newNot();
    return ret;
}

ResettableDFlipFlop* newResettableDFlipFlop(bit q) {
    S_MALLOC(ret, ResettableDFlipFlop);
    ret->internal = newInternalResettableDFlipFlop(q);
    ret->clk = 0;
    ret->d = 0;
    ret->reset = 0;
    ret->q = q;
    ret->notQ = !q;
    return ret;
}

void propagateResettableDFlipFlop(ResettableDFlipFlop* node) {
    node->internal->notNode->input = node->reset;
    propagateNot(node->internal->notNode);

    node->internal->andNode->inputA = node->d;
    node->internal->andNode->inputB = node->internal->notNode->output;
    propagateAnd(node->internal->andNode);

    node->internal->dFlipFlopNode->d = node->internal->andNode->output;
    node->internal->dFlipFlopNode->clk = node->clk;
    propagateDFlipFlop(node->internal->dFlipFlopNode);

    node->q = node->internal->dFlipFlopNode->q;
    node->notQ = node->internal->dFlipFlopNode->notQ;
}

void printResettableDFlipFlop(ResettableDFlipFlop* node) {
    printf(
        "ResettableDFlipFlop(clk=%d, d=%d, reset=%d, q=%d, notQ=%d)\n",
        node->clk, node->d, node->reset, node->q, node->notQ
    );
}

void freeInternalResettableDFlipFlop(InternalResettableDFlipFlop* node) {
    freeDFlipFlop(node->dFlipFlopNode);
    freeAnd(node->andNode);
    freeNot(node->notNode);
    free(node);
}

void freeResettableDFlipFlop(ResettableDFlipFlop* node) {
    freeInternalResettableDFlipFlop(node->internal);
    free(node);
}
