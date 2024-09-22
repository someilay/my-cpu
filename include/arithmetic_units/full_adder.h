#ifndef ARITHMETIC_UNITS_FULL_ADDER
#define ARITHMETIC_UNITS_FULL_ADDER
#include "typedefs.h"
#include "basic/or.h"
#include "arithmetic_units/half_adder.h"

typedef struct {
    Or* orNode;
    HalfAdder* halfAdderNodeA;
    HalfAdder* halfAdderNodeB;
} InternalFullAdder;

typedef struct {
    bit inputA;
    bit inputB;
    bit inputC;
    bit s;
    bit c;
    InternalFullAdder* internal;
} FullAdder;

FullAdder* newFullAdder();

void propagateFullAdder(FullAdder* node);

void printFullAdder(FullAdder* node);

void freeFullAdder(FullAdder* node);

#endif
