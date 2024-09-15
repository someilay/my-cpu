#include "malloc.h"
#include "basic/or.h"

Or* newOr() {
    Or* ret = (Or*) malloc(sizeof(Or));
    ret->inputA = 0;
    ret->inputB = 0;
    ret->output = 0;
    return ret;
}

void propagateOr(Or* node) {
    node->output = node->inputA | node->inputB;
}

void printOr(Or* node) {
    printf("Or(inputA=%d, inputB=%d, output=%d)\n", node->inputA, node->inputB, node->output);
}

void freeOr(Or* node) {
    free(node);
}
