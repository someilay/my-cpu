#ifndef GATES_DMPX_4_H
#define GATES_DMPX_4_H
#include "typedefs.h"
#include "gates/dmpx.h"

typedef struct {
    DeMultiplexer* dmpxA;
    DeMultiplexer* dmpxB;
    DeMultiplexer* dmpxC;
} InternalDeMultiplexer4;

typedef struct {
    bit input;
    bit selectA;
    bit selectB;
    bit* outputs;
    InternalDeMultiplexer4* internal;
} DeMultiplexer4;

DeMultiplexer4* newDmpx4();

void propagateDmpx4(DeMultiplexer4* node);

void printDmpx4(DeMultiplexer4* node);

void freeDmpx4(DeMultiplexer4* node);

#endif
