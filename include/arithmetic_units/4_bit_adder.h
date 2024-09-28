#ifndef ARITHMETIC_UNITS_4_BIT_ADDER
#define ARITHMETIC_UNITS_4_BIT_ADDER
#include "typedefs.h"
#include "arithmetic_units/full_adder.h"

typedef struct {
    FullAdder** adders;
} InternalBitAdder4;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit inputC;
    bit* output;
    bit c;
    InternalBitAdder4* internal;
} BitAdder4;

BitAdder4* newBitAdder4();

void propagateBitAdder4(BitAdder4* node);

void printBitAdder4(BitAdder4* node);

void freeBitAdder4(BitAdder4* node);

#endif
