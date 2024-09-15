#ifndef GATES_AND_4_H
#define GATES_AND_4_H
#include "typedefs.h"
#include "basic/and.h"

typedef struct {
    And* andA;
    And* andB;
    And* andC;
} InternalAnd4;

typedef struct {
    bit* inputs;
    bit output;
    InternalAnd4* internal;
} And4;

And4* newAnd4();

void propagateAnd4(And4* node);

void printAnd4(And4* node);

void freeAnd4(And4* node);

#endif
