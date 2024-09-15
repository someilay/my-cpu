#include "malloc.h"
#include "gates/and_4.h"

InternalAnd4* newInternalAnd4() {
    InternalAnd4* ret = (InternalAnd4*)malloc(sizeof(InternalAnd4));
    ret->andA = newAnd();
    ret->andB = newAnd();
    ret->andC = newAnd();
    return ret;
}

And4* newAnd4() {
    And4* ret = (And4*)malloc(sizeof(And4));
    ret->inputs = (bit*)malloc(4 * sizeof(bit));
    ret->output = 0;
    ret->internal = newInternalAnd4();
    for (bit i = 0; i < 4; i++) {
        ret->inputs[i] = 0;
    }
    return ret;
}

void propagateAnd4(And4* node) {
    node->internal->andA->inputA = node->inputs[0];
    node->internal->andA->inputB = node->inputs[1];
    node->internal->andB->inputA = node->inputs[2];
    node->internal->andB->inputB = node->inputs[3];

    propagateAnd(node->internal->andA);
    propagateAnd(node->internal->andB);

    node->internal->andC->inputA = node->internal->andA->output;
    node->internal->andC->inputB = node->internal->andB->output;

    propagateAnd(node->internal->andC);

    node->output = node->internal->andC->output;
}

void printAnd4(And4* node) {
    printf(
        "And4(input_0=%d, input_1=%d, input_2=%d, input_3=%d, output=%d)\n",
        node->inputs[0], node->inputs[1], node->inputs[2], node->inputs[3],
        node->output
    );
}

void freeInternalAnd4(InternalAnd4* node) {
    freeAnd(node->andA);
    freeAnd(node->andB);
    freeAnd(node->andC);
    free(node);
}

void freeAnd4(And4* node) {
    freeInternalAnd4(node->internal);
    free(node->inputs);
    free(node);
}
