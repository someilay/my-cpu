#include "malloc.h"
#include "basic/and.h"

And* newAnd() {
    And* ret = (And*)malloc(sizeof(And));
    ret->inputA = 0;
    ret->inputB = 0;
    ret->output = 0;
    return ret;
}

void propagateAnd(And* node) {
    node->output = node->inputA & node->inputB;
}

void freeAnd(And* node) {
    free(node);
}

void printAnd(And* node) {
    printf("And(inputA=%d, inputB=%d, output=%d)\n", node->inputA, node->inputB, node->output);
}
