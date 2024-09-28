#ifndef GATES_32_OR_32_H
#define GATES_32_OR_32_H
#include "typedefs.h"
#include "basic/or.h"

typedef struct {
    Or** ors;
} InternalOr32to32;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit* output;
    InternalOr32to32* internal;
} Or32to32;

Or32to32* newOr32to32();

void propagateOr32to32(Or32to32* node);

void printOr32to32(Or32to32* node);

void freeOr32to32(Or32to32* node);

#endif
