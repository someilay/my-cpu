#ifndef BASIC_NOT_H
#define BASIC_NOT_H

#include "typedefs.h"

typedef struct
{
    bit input;
    bit output;
} Not;


Not* newNot();

void propagateNot(Not* node);

void printNot(Not* node);

void freeNot(Not* node);

#endif