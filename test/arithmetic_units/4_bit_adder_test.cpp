#include "gtest/gtest.h"

extern "C"
{
#include "arithmetic_units/4_bit_adder.h"
#include "utility.h"
}

class BitAdder4Test : public testing::Test
{
protected:
    BitAdder4Test() {
        bitAdder4Node = newBitAdder4();
    }
    ~BitAdder4Test() {
        freeBitAdder4(bitAdder4Node);
    }
    BitAdder4* bitAdder4Node;
};

TEST_F(BitAdder4Test, TestBitAdder4Propagate) {
    for (bit i = 0; i < 16; i++) {
        for (bit j = 0; j < 16; j++) {
            for (bit k = 0; k < 2; k++) {
                bitAdder4Node->inputC = k;
                num2bits((uint64_t) i, bitAdder4Node->inputA, 4);
                num2bits((uint64_t) j, bitAdder4Node->inputB, 4);
                propagateBitAdder4(bitAdder4Node);
                EXPECT_EQ(bits2num(bitAdder4Node->output, 4), (i + j + k) & 15);
                EXPECT_EQ(bitAdder4Node->c, ((i + j + k) & 16) >> 4);
            }
        }
    }
}
