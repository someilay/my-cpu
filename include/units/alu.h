#ifndef UNITS_ALU_H
#define UNITS_ALU_H

#include "typedefs.h"
#include "arithmetic_units/32_bit_adder.h"
#include "basic/not.h"
#include "basic/and.h"
#include "gates/32_and_32.h"
#include "gates/32_or_32.h"
#include "gates/32_not_32.h"
#include "gates/32_mpx_32.h"
#include "gates/32_mpx_4_32.h"
#include "gates/or_32.h"
#include "gates/xor.h"

#define ALU_AND_OP 0
#define ALU_OR_OP 1
#define ALU_ADD_OP 2
#define ALU_SUB_OP 6
#define ALU_SLT_OP 7
#define ALU_NOR_OP 12

typedef struct {
    Not32to32* not32to32A;
    Not32to32* not32to32B;
    Multiplexer32to32* mpx32to32A;
    Multiplexer32to32* mpx32to32B;
    And32to32* and32to32;
    Or32to32* or32to32;
    BitAdder32* adder;
    Xor* xorNodeA;
    Xor* xorNodeB;
    Multiplexer4x32to32* mpx4x32to32Node;
    Or32* or32Node;
    Not* notNode;
    And* andNodeA;
    And* andNodeB;
} InternalAlu;

typedef struct {
    bit* inputA;
    bit* inputB;
    bit* control;
    bit* output;
    bit zero;
    bit overflow;
    bit carry;
    InternalAlu* internal;
} Alu;

Alu* newAlu();

void propagateAlu(Alu* node);

void printAlu(Alu* node);

void freeAlu(Alu* node);

#endif
