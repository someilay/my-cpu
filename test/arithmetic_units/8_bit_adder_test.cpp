#include "gtest/gtest.h"

extern "C"
{
#include "arithmetic_units/8_bit_adder.h"
#include "utility.h"
}

class BitAdder8Test : public testing::Test
{
protected:
    BitAdder8Test() {
        bitAdder8Node = newBitAdder8();
    }
    ~BitAdder8Test() {
        freeBitAdder8(bitAdder8Node);
    }
    BitAdder8* bitAdder8Node;
};

TEST_F(BitAdder8Test, TestBitAdder8Propagate) {
    srand(403);
    for (int i = 0; i < 1000; i++) {
        uint64_t inputA = (uint64_t)(rand() % 256);
        uint64_t inputB = (uint64_t)(rand() % 256);
        uint64_t inputC = (uint64_t)(rand() & 1);

        num2bits(inputA, bitAdder8Node->inputA, 8);
        num2bits(inputB, bitAdder8Node->inputB, 8);
        bitAdder8Node->inputC = (bit)inputC;
        propagateBitAdder8(bitAdder8Node);

        EXPECT_EQ(bits2num(bitAdder8Node->output, 8), (inputA + inputB + inputC) % 256);
        EXPECT_EQ(bitAdder8Node->c, ((inputA + inputB + inputC) >> 8) & 1);
    }
}
