#ifndef GATES_MPX_4_H
#define GATES_MPX_4_H
#include "typedefs.h"
#include "gates/mpx.h"

typedef struct {
    Multiplexer* mpxA;
    Multiplexer* mpxB;
    Multiplexer* mpxC;
} InternalMultiplexer4;

typedef struct {
    bit* inputs;
    bit selectA;
    bit selectB;
    bit output;
    InternalMultiplexer4* internal;
} Multiplexer4;

Multiplexer4* newMpx4();

void propagateMpx4(Multiplexer4* node);

void printMpx4(Multiplexer4* node);

void freeMpx4(Multiplexer4* node);

#endif
