#include "defines.h"
#include "arithmetic_units/full_adder.h"

InternalFullAdder* newInternalFullAdder() {
    S_MALLOC(ret, InternalFullAdder);
    ret->orNode = newOr();
    ret->halfAdderNodeA = newHalfAdder();
    ret->halfAdderNodeB = newHalfAdder();
    return ret;
}

FullAdder* newFullAdder() {
    S_MALLOC(ret, FullAdder);
    ret->internal = newInternalFullAdder();
    ret->inputA = 0;
    ret->inputB = 0;
    ret->inputC = 0;
    ret->s = 0;
    ret->c = 0;
    return ret;
}

void propagateFullAdder(FullAdder* node) {
    node->internal->halfAdderNodeA->inputA = node->inputA;
    node->internal->halfAdderNodeA->inputB = node->inputB;
    propagateHalfAdder(node->internal->halfAdderNodeA);

    node->internal->halfAdderNodeB->inputA = node->internal->halfAdderNodeA->s;
    node->internal->halfAdderNodeB->inputB = node->inputC;
    propagateHalfAdder(node->internal->halfAdderNodeB);

    node->internal->orNode->inputA = node->internal->halfAdderNodeA->c;
    node->internal->orNode->inputB = node->internal->halfAdderNodeB->c;
    propagateOr(node->internal->orNode);

    node->s = node->internal->halfAdderNodeB->s;
    node->c = node->internal->orNode->output;
}

void printFullAdder(FullAdder* node) {
    printf(
        "FullAdder(inputA=%d, inputB=%d, inputC=%d, s=%d, c=%d)\n",
        node->inputA, node->inputB, node->inputC, node->s, node->c
    );
}

void freeInternalFullAdder(InternalFullAdder* node) {
    freeOr(node->orNode);
    freeHalfAdder(node->halfAdderNodeA);
    freeHalfAdder(node->halfAdderNodeB);
    free(node);
}

void freeFullAdder(FullAdder* node) {
    freeInternalFullAdder(node->internal);
    free(node);
}
