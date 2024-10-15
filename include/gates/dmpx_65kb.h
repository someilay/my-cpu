#ifndef GATES_DMPX_65KB_H
#define GATES_DMPX_65KB_H
#include "typedefs.h"
#include "gates/dmpx_256.h"

typedef struct {
    DeMultiplexer256* dmpxM;
    DeMultiplexer256** dmpxS;
} InternalDeMultiplexer65kb;

typedef struct {
    bit input;
    bit* select;
    bit* output;
    InternalDeMultiplexer65kb* internal;
} DeMultiplexer65kb;

DeMultiplexer65kb* newDmpx65kb();

void propagateDmpx65kb(DeMultiplexer65kb* node);

void printDmpx65kb(DeMultiplexer65kb* node);

void freeDmpx65kb(DeMultiplexer65kb* node);

#endif
