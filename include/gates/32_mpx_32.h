#ifndef GATES_32_MPX_32_H
#define GATES_32_MPX_32_H
#include "typedefs.h"
#include "gates/mpx.h"

typedef struct {
    Multiplexer** mpxs;
} InternalMultiplexer32to32;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit* output;
    bit select;
    InternalMultiplexer32to32* internal;
} Multiplexer32to32;

Multiplexer32to32* newMpx32to32();

void propagateMpx32to32(Multiplexer32to32* node);

void printMpx32to32(Multiplexer32to32* node);

void freeMpx32to32(Multiplexer32to32* node);

#endif
