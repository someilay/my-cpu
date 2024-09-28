#ifndef GATES_32_MPX_4_32_H
#define GATES_32_MPX_4_32_H
#include "typedefs.h"
#include "gates/mpx_4.h"

typedef struct {
    Multiplexer4** mpxs;
} InternalMultiplexer4x32to32;

typedef struct {
    bit** input;
    bit* output;
    bit selectA;
    bit selectB;
    InternalMultiplexer4x32to32* internal;
} Multiplexer4x32to32;

Multiplexer4x32to32* newMpx4x32to32();

void propagateMpx4x32to32(Multiplexer4x32to32* node);

void printMpx4x32to32(Multiplexer4x32to32* node);

void freeMpx4x32to32(Multiplexer4x32to32* node);

#endif
