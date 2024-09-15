#ifndef GATES_XOR_H
#define GATES_XOR_H

#include "typedefs.h"
#include "basic/and.h"
#include "basic/or.h"
#include "basic/not.h"

typedef struct {
    And* andA;
    And* andB;
    Not* notA;
    Not* notB;
    Or* orNode;
} InternalXor;

typedef struct
{
    bit inputA;
    bit inputB;
    bit output;
    InternalXor* internal;
} Xor;

Xor* newXor();

void propagateXor(Xor* node);

void printXor(Xor* node);

void freeXor(Xor* node);

#endif
