#ifndef GATES_DMPX_H
#define GATES_DMPX_H
#include "typedefs.h"
#include "basic/and.h"
#include "basic/not.h"

typedef struct {
    And* andA;
    And* andB;
    Not* notNode;
} InternalDeMultiplexer;

typedef struct {
    bit input;
    bit select;
    bit outputA;
    bit outputB;
    InternalDeMultiplexer* internal;
} DeMultiplexer;

DeMultiplexer* newDmpx();

void propagateDmpx(DeMultiplexer* node);

void printDmpx(DeMultiplexer* node);

void freeDmpx(DeMultiplexer* node);

#endif
