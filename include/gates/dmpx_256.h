#ifndef GATES_DMPX_256_H
#define GATES_DMPX_256_H
#include "typedefs.h"
#include "gates/dmpx_16.h"

typedef struct {
    DeMultiplexer16* dmpxM;
    DeMultiplexer16** dmpxS;
} InternalDeMultiplexer256;

typedef struct {
    bit input;
    bit* select;
    bit* output;
    InternalDeMultiplexer256* internal;
} DeMultiplexer256;

DeMultiplexer256* newDmpx256();

void propagateDmpx256(DeMultiplexer256* node);

void printDmpx256(DeMultiplexer256* node);

void freeDmpx256(DeMultiplexer256* node);

#endif
