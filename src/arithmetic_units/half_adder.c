#include "defines.h"
#include "arithmetic_units/half_adder.h"

InternalHalfAdder* newInternalHalfAdder() {
    S_MALLOC(ret, InternalHalfAdder);
    ret->xorNode = newXor();
    ret->andNode = newAnd();
    return ret;
}

HalfAdder* newHalfAdder() {
    S_MALLOC(ret, HalfAdder);
    ret->internal = newInternalHalfAdder();
    ret->inputA = 0;
    ret->inputB = 0;
    ret->s = 0;
    ret->c = 0;
    return ret;
}

void propagateHalfAdder(HalfAdder* node) {
    node->internal->andNode->inputA = node->inputA;
    node->internal->andNode->inputB = node->inputB;
    node->internal->xorNode->inputA = node->inputA;
    node->internal->xorNode->inputB = node->inputB;
    propagateXor(node->internal->xorNode);
    propagateAnd(node->internal->andNode);
    node->s = node->internal->xorNode->output;
    node->c = node->internal->andNode->output;
}

void printHalfAdder(HalfAdder* node) {
    printf(
        "HalfAdder(inputA=%d, inputB=%d, s=%d, c=%d)\n",
        node->inputA, node->inputB, node->s, node->c
    );
}

void freeInternalHalfAdder(InternalHalfAdder* node) {
    freeXor(node->xorNode);
    freeAnd(node->andNode);
    free(node);
}

void freeHalfAdder(HalfAdder* node) {
    freeInternalHalfAdder(node->internal);
    free(node);
}
