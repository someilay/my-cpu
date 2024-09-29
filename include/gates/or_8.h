#ifndef GATES_OR_8_H
#define GATES_OR_8_H
#include "typedefs.h"
#include "gates/or_4.h"
#include "basic/or.h"

typedef struct {
    Or4* orA;
    Or4* orB;
    Or* orC;
} InternalOr8;

typedef struct {
    bit* input;
    bit output;
    InternalOr8* internal;
} Or8;

Or8* newOr8();

void propagateOr8(Or8* node);

void printOr8(Or8* node);

void freeOr8(Or8* node);

#endif
