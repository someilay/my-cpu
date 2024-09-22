#ifndef ARITHMETIC_UNITS_HALF_ADDER
#define ARITHMETIC_UNITS_HALF_ADDER
#include "typedefs.h"
#include "gates/xor.h"
#include "basic/and.h"

typedef struct {
    Xor* xorNode;
    And* andNode;
} InternalHalfAdder;

typedef struct {
    bit inputA;
    bit inputB;
    bit s;
    bit c;
    InternalHalfAdder* internal;
} HalfAdder;

HalfAdder* newHalfAdder();

void propagateHalfAdder(HalfAdder* node);

void printHalfAdder(HalfAdder* node);

void freeHalfAdder(HalfAdder* node);

#endif
