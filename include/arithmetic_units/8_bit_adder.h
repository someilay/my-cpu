#ifndef ARITHMETIC_UNITS_8_BIT_ADDER
#define ARITHMETIC_UNITS_8_BIT_ADDER
#include "typedefs.h"
#include "arithmetic_units/4_bit_adder.h"

typedef struct {
    BitAdder4* bitAdderA;
    BitAdder4* bitAdderB;
} InternalBitAdder8;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit inputC;
    bit* output;
    bit c;
    InternalBitAdder8* internal;
} BitAdder8;

BitAdder8* newBitAdder8();

void propagateBitAdder8(BitAdder8* node);

void printBitAdder8(BitAdder8* node);

void freeBitAdder8(BitAdder8* node);

#endif
