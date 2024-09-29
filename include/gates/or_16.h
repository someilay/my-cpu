#ifndef GATES_OR_16_H
#define GATES_OR_16_H
#include "typedefs.h"
#include "gates/or_8.h"
#include "basic/or.h"

typedef struct {
    Or8* orA;
    Or8* orB;
    Or* orC;
} InternalOr16;

typedef struct {
    bit* input;
    bit output;
    InternalOr16* internal;
} Or16;

Or16* newOr16();

void propagateOr16(Or16* node);

void printOr16(Or16* node);

void freeOr16(Or16* node);

#endif
