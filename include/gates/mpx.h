#ifndef GATES_MPX_H
#define GATES_MPX_H
#include "typedefs.h"
#include "basic/and.h"
#include "basic/or.h"
#include "basic/not.h"

typedef struct {
    And* andA;
    And* andB;
    Not* notNode;
    Or* orNode;
} InternalMultiplexer;

typedef struct {
    bit inputA;
    bit inputB;
    bit select;
    bit output;
    InternalMultiplexer* internal;
} Multiplexer;

Multiplexer* newMpx();

void propagateMpx(Multiplexer* node);

void printMpx(Multiplexer* node);

void freeMpx(Multiplexer* node);

#endif
