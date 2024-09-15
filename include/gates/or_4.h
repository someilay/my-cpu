#ifndef GATES_OR_4_H
#define GATES_OR_4_H
#include "typedefs.h"
#include "basic/or.h"

typedef struct {
    Or* orA;
    Or* orB;
    Or* orC;
} InternalOr4;

typedef struct {
    bit* inputs;
    bit output;
    InternalOr4* internal;
} Or4;

Or4* newOr4();

void propagateOr4(Or4* node);

void printOr4(Or4* node);

void freeOr4(Or4* node);

#endif
