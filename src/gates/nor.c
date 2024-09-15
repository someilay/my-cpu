#include "malloc.h"
#include "gates/nor.h"

InternalNor* newInternalNor() {
    InternalNor* ret = (InternalNor*)malloc(sizeof(InternalNor));
    ret->notNode = newNot();
    ret->orNode = newOr();
    return ret;
}

Nor* newNor() {
    Nor* ret = (Nor*)malloc(sizeof(Nor));
    ret->inputA = 0;
    ret->inputB = 0;
    ret->output = 1;
    ret->internal = newInternalNor();
    return ret;
}

void propagateNor(Nor* node) {
    node->internal->orNode->inputA = node->inputA;
    node->internal->orNode->inputB = node->inputB;
    propagateOr(node->internal->orNode);

    node->internal->notNode->input = node->internal->orNode->output;
    propagateNot(node->internal->notNode);

    node->output = node->internal->notNode->output;
}

void printNor(Nor* node) {
    printf("Nor(inputA=%d, inputB=%d, output=%d)\n", node->inputA, node->inputB, node->output);
}

void freeInternalNor(InternalNor* node) {
    freeOr(node->orNode);
    freeNot(node->notNode);
    free(node);
}

void freeNor(Nor* node) {
    freeInternalNor(node->internal);
    free(node);
}
