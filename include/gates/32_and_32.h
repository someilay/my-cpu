#ifndef GATES_32_AND_32_H
#define GATES_32_AND_32_H
#include "typedefs.h"
#include "basic/and.h"

typedef struct {
    And** ands;
} InternalAnd32to32;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit* output;
    InternalAnd32to32* internal;
} And32to32;

And32to32* newAnd32to32();

void propagateAnd32to32(And32to32* node);

void printAnd32to32(And32to32* node);

void freeAnd32to32(And32to32* node);

#endif
