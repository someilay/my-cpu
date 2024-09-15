#include "malloc.h"
#include "gates/or_4.h"

InternalOr4* newInternalOr4() {
    InternalOr4* ret = (InternalOr4*)malloc(sizeof(InternalOr4));
    ret->orA = newOr();
    ret->orB = newOr();
    ret->orC = newOr();
    return ret;
}

Or4* newOr4() {
    Or4* ret = (Or4*)malloc(sizeof(Or4));
    ret->inputs = (bit*)malloc(4 * sizeof(bit));
    ret->output = 0;
    ret->internal = newInternalOr4();
    for (bit i = 0; i < 4; i++) {
        ret->inputs[i] = 0;
    }
    return ret;
}

void propagateOr4(Or4* node) {
    node->internal->orA->inputA = node->inputs[0];
    node->internal->orA->inputB = node->inputs[1];
    node->internal->orB->inputA = node->inputs[2];
    node->internal->orB->inputB = node->inputs[3];

    propagateOr(node->internal->orA);
    propagateOr(node->internal->orB);

    node->internal->orC->inputA = node->internal->orA->output;
    node->internal->orC->inputB = node->internal->orB->output;

    propagateOr(node->internal->orC);

    node->output = node->internal->orC->output;
}

void printOr4(Or4* node) {
    printf(
        "Or4(input_0=%d, input_1=%d, input_2=%d, input_3=%d, output=%d)\n",
        node->inputs[0], node->inputs[1], node->inputs[2], node->inputs[3],
        node->output
    );
}

void freeInternalOr4(InternalOr4* node) {
    freeOr(node->orA);
    freeOr(node->orB);
    freeOr(node->orC);
    free(node);
}

void freeOr4(Or4* node) {
    freeInternalOr4(node->internal);
    free(node->inputs);
    free(node);
}
