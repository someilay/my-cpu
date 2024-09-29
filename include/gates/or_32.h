#ifndef GATES_OR_32_H
#define GATES_OR_32_H
#include "typedefs.h"
#include "gates/or_16.h"
#include "basic/or.h"

typedef struct {
    Or16* orA;
    Or16* orB;
    Or* orC;
} InternalOr32;

typedef struct {
    bit* input;
    bit output;
    InternalOr32* internal;
} Or32;

Or32* newOr32();

void propagateOr32(Or32* node);

void printOr32(Or32* node);

void freeOr32(Or32* node);

#endif
