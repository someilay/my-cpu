#ifndef BASIC_OR_H
#define BASIC_OR_H
#include "typedefs.h"

typedef struct
{
    bit inputA;
    bit inputB;
    bit output;
} Or;


Or* newOr();

void propagateOr(Or* node);

void printOr(Or* node);

void freeOr(Or* node);

#endif
