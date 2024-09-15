#ifndef LATCHES_RESETTABLE_D_FLIP_FLOP_H
#define LATCHES_RESETTABLE_D_FLIP_FLOP_H
#include "typedefs.h"
#include "latches/d_flip_flop.h"
#include "basic/not.h"
#include "basic/and.h"

typedef struct {
    DFlipFlop* dFlipFlopNode;
    Not* notNode;
    And* andNode;
} InternalResettableDFlipFlop;

typedef struct {
    bit clk;
    bit d;
    bit reset;
    bit q;
    bit notQ;
    InternalResettableDFlipFlop* internal;
} ResettableDFlipFlop;

ResettableDFlipFlop* newResettableDFlipFlop(bit q);

void propagateResettableDFlipFlop(ResettableDFlipFlop* node);

void printResettableDFlipFlop(ResettableDFlipFlop* node);

void freeResettableDFlipFlop(ResettableDFlipFlop* node);

#endif