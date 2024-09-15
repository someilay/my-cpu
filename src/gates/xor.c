#include "malloc.h"
#include "gates/xor.h"

InternalXor* newInternalXor() {
    InternalXor* ret = (InternalXor*) malloc(sizeof(InternalXor));
    ret->andA = newAnd();
    ret->andB = newAnd();
    ret->notA = newNot();
    ret->notB = newNot();
    ret->orNode = newOr();
    return ret;
}

Xor* newXor() {
    Xor* ret = (Xor*) malloc(sizeof(Xor));
    ret->inputA = 0;
    ret->inputB = 0;
    ret->output = 0;
    ret->internal = newInternalXor();
    return ret;
}

void propagateXor(Xor* node) {
    node->internal->notA->input = node->inputA;
    node->internal->notB->input = node->inputB;

    propagateNot(node->internal->notA);
    propagateNot(node->internal->notB);

    node->internal->andA->inputA = node->inputA;
    node->internal->andA->inputB = node->internal->notB->output;
    node->internal->andB->inputA = node->internal->notA->output;
    node->internal->andB->inputB = node->inputB;

    propagateAnd(node->internal->andA);
    propagateAnd(node->internal->andB);

    node->internal->orNode->inputA = node->internal->andA->output;
    node->internal->orNode->inputB = node->internal->andB->output;

    propagateOr(node->internal->orNode);

    node->output = node->internal->orNode->output;
}

void printXor(Xor* node) {
    printf("Xor(inputA=%d, inputB=%d, output=%d)\n", node->inputA, node->inputB, node->output);
}


void freeInternalXor(InternalXor* node) {
    freeAnd(node->andA);
    freeAnd(node->andB);
    freeNot(node->notA);
    freeNot(node->notB);
    freeOr(node->orNode);
    free(node);
}


void freeXor(Xor* node) {
    freeInternalXor(node->internal);
    free(node);
}
