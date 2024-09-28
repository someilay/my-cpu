#ifndef ARITHMETIC_UNITS_32_BIT_ADDER
#define ARITHMETIC_UNITS_32_BIT_ADDER
#include "typedefs.h"
#include "arithmetic_units/full_adder.h"

typedef struct {
    FullAdder** adders;
} InternalBitAdder32;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit inputC;
    bit* output;
    bit c;
    InternalBitAdder32* internal;
} BitAdder32;

BitAdder32* newBitAdder32();

void propagateBitAdder32(BitAdder32* node);

void printBitAdder32(BitAdder32* node);

void freeBitAdder32(BitAdder32* node);

#endif
