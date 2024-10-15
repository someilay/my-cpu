#ifndef GATES_DMPX_16_H
#define GATES_DMPX_16_H
#include "typedefs.h"
#include "gates/dmpx_4.h"

typedef struct {
    DeMultiplexer4* dmpxM;
    DeMultiplexer4** dmpxS;
} InternalDeMultiplexer16;

typedef struct {
    bit input;
    bit* select;
    bit* output;
    InternalDeMultiplexer16* internal;
} DeMultiplexer16;

DeMultiplexer16* newDmpx16();

void propagateDmpx16(DeMultiplexer16* node);

void printDmpx16(DeMultiplexer16* node);

void freeDmpx16(DeMultiplexer16* node);

#endif
