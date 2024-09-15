#ifndef GATES_NOR_H
#define GATES_NOR_H

#include "typedefs.h"
#include "basic/or.h"
#include "basic/not.h"

typedef struct {
    Not* notNode;
    Or* orNode;
} InternalNor;

typedef struct
{
    bit inputA;
    bit inputB;
    bit output;
    InternalNor* internal;
} Nor;

Nor* newNor();

void propagateNor(Nor* node);

void printNor(Nor* node);

void freeNor(Nor* node);

#endif
