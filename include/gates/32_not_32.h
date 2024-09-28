#ifndef GATES_32_NOT_32_H
#define GATES_32_NOT_32_H
#include "typedefs.h"
#include "basic/not.h"

typedef struct {
    Not** nots;
} InternalNot32to32;

typedef struct {
    bit* input;
    bit* output;
    InternalNot32to32* internal;
} Not32to32;

Not32to32* newNot32to32();

void propagateNot32to32(Not32to32* node);

void printNot32to32(Not32to32* node);

void freeNot32to32(Not32to32* node);

#endif
