#include "defines.h"
#include "utility.h"
#include "units/alu.h"

InternalAlu* newInternalAlu() {
    S_MALLOC(ret, InternalAlu);
    ret->not32to32A = newNot32to32();
    ret->not32to32B = newNot32to32();
    ret->mpx32to32A = newMpx32to32();
    ret->mpx32to32B = newMpx32to32();
    ret->and32to32 = newAnd32to32();
    ret->or32to32 = newOr32to32();
    ret->adder = newBitAdder32();
    ret->xorNodeA = newXor();
    ret->xorNodeB = newXor();
    ret->mpx4x32to32Node = newMpx4x32to32();
    ret->or32Node = newOr32();
    ret->notNode = newNot();
    ret->andNodeA = newAnd();
    ret->andNodeB = newAnd();
    return ret;
}

Alu* newAlu() {
    S_MALLOC(ret, Alu);
    AIF_MALLOC(ret->inputA, bit, 32, 0);
    AIF_MALLOC(ret->inputB, bit, 32, 0);
    AIF_MALLOC(ret->output, bit, 32, 0);
    AIF_MALLOC(ret->control, bit, 4, 0);
    ret->internal = newInternalAlu();
    ret->zero = 1;
    ret->carry = 0;
    ret->overflow = 0;
    return ret;
}

void propagateAlu(Alu* node) {
    InternalAlu* il = node->internal;

    // Invert A and B
    memcpy(il->not32to32A->input, node->inputA, B32);
    memcpy(il->not32to32B->input, node->inputB, B32);
    propagateNot32to32(il->not32to32A);
    propagateNot32to32(il->not32to32B);

    // Set A and B to invert value if needed
    il->mpx32to32A->select = node->control[3];
    il->mpx32to32B->select = node->control[2];
    memcpy(il->mpx32to32A->inputA, node->inputA, B32);
    memcpy(il->mpx32to32A->inputB, il->not32to32A->output, B32);
    memcpy(il->mpx32to32B->inputA, node->inputB, B32);
    memcpy(il->mpx32to32B->inputB, il->not32to32B->output, B32);
    propagateMpx32to32(il->mpx32to32A);
    propagateMpx32to32(il->mpx32to32B);

    // Pass signals through several logical blocks
    bit* inputSA = il->mpx32to32A->output;
    bit* inputSB = il->mpx32to32B->output;
    il->adder->inputC = node->control[2];
    memcpy(il->and32to32->inputA, inputSA, B32);
    memcpy(il->and32to32->inputB, inputSB, B32);
    memcpy(il->or32to32->inputA, inputSA, B32);
    memcpy(il->or32to32->inputB, inputSB, B32);
    memcpy(il->adder->inputA, inputSA, B32);
    memcpy(il->adder->inputB, inputSB, B32);
    propagateAnd32to32(il->and32to32);
    propagateOr32to32(il->or32to32);
    propagateBitAdder32(il->adder);

    // Overflow detection
    il->xorNodeA->inputA = il->adder->internal->adders[31]->inputC;
    il->xorNodeA->inputB = il->adder->c;
    propagateXor(il->xorNodeA);

    // A < B detection
    il->xorNodeB->inputA = il->xorNodeA->output;
    il->xorNodeB->inputB = il->adder->output[31];
    propagateXor(il->xorNodeB);

    // Chose output
    il->mpx4x32to32Node->selectA = node->control[0];
    il->mpx4x32to32Node->selectB = node->control[1];
    memcpy(il->mpx4x32to32Node->input[0], il->and32to32->output, B32);
    memcpy(il->mpx4x32to32Node->input[1], il->or32to32->output, B32);
    memcpy(il->mpx4x32to32Node->input[2], il->adder->output, B32);
    memset(il->mpx4x32to32Node->input[3], 0, B32);
    il->mpx4x32to32Node->input[3][0] = il->xorNodeB->output;
    propagateMpx4x32to32(il->mpx4x32to32Node);

    // Detect zero output
    memcpy(il->or32Node->input, il->mpx4x32to32Node->output, B32);
    propagateOr32(il->or32Node);

    il->notNode->input = il->or32Node->output;
    propagateNot(il->notNode);

    // Pass overflow and carry if it is not logical operation
    il->andNodeA->inputA = node->control[1];
    il->andNodeA->inputB = il->adder->c;
    il->andNodeB->inputA = node->control[1];
    il->andNodeB->inputB = il->xorNodeA->output;
    propagateAnd(il->andNodeA);
    propagateAnd(il->andNodeB);

    // Setting output
    memcpy(node->output, il->mpx4x32to32Node->output, B32);
    node->carry = il->andNodeA->output;
    node->overflow = il->andNodeB->output;
    node->zero = il->notNode->output;
}

void printAlu(Alu* node) {
    printf("Alu(inputA=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputA + (7 - i) * 4, 4));
    }
    printf(", inputB=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->inputB + (7 - i) * 4, 4));
    }
    printf(", control=0b");
    for (bit i = 0; i < 4; i++) {
        printf("%d", node->control[3 - i]);
    }
    printf(", output=0x");
    for (bit i = 0; i < 8; i++) {
        printf("%lx", bits2num(node->output + (7 - i) * 4, 4));
    }
    printf(", zero=%d, overflow=%d, carry=%d)\n", node->zero, node->overflow, node->carry);
}

void freeInternalAlu(InternalAlu* node) {
    freeNot32to32(node->not32to32A);
    freeNot32to32(node->not32to32B);
    freeMpx32to32(node->mpx32to32A);
    freeMpx32to32(node->mpx32to32B);
    freeAnd32to32(node->and32to32);
    freeOr32to32(node->or32to32);
    freeBitAdder32(node->adder);
    freeXor(node->xorNodeA);
    freeXor(node->xorNodeB);
    freeMpx4x32to32(node->mpx4x32to32Node);
    freeOr32(node->or32Node);
    freeNot(node->notNode);
    freeAnd(node->andNodeA);
    freeAnd(node->andNodeB);
    free(node);
}

void freeAlu(Alu* node) {
    freeInternalAlu(node->internal);
    free(node->inputA);
    free(node->inputB);
    free(node->control);
    free(node->output);
    free(node);
}
