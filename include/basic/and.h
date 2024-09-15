#ifndef BASIC_AND_H
#define BASIC_AND_H

#include "typedefs.h"

typedef struct
{
    bit inputA;
    bit inputB;
    bit output;
} And;

And* newAnd();

void propagateAnd(And* node);

void printAnd(And* node);

void freeAnd(And* node);

#endif
