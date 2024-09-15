#ifndef LATCHES_D_FLIP_FLOP_H
#define LATCHES_D_FLIP_FLOP_H
#include "typedefs.h"
#include "latches/d_latch.h"
#include "basic/not.h"

typedef struct {
    DLatch* dLatchA;
    DLatch* dLatchB;
    Not* notNode;
} InternalDFlipFlop;

typedef struct {
    bit clk;
    bit d;
    bit q;
    bit notQ;
    InternalDFlipFlop* internal;
} DFlipFlop;

DFlipFlop* newDFlipFlop(bit q);

void propagateDFlipFlop(DFlipFlop* node);

void printDFlipFlop(DFlipFlop* node);

void freeDFlipFlop(DFlipFlop* node);

#endif
