#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "arithmetic_units/32_bit_adder.h"
#include "utility.h"
}

class BitAdder32Test : public testing::Test
{
protected:
    BitAdder32Test() {
        bitAdder32Node = newBitAdder32();
    }
    ~BitAdder32Test() {
        freeBitAdder32(bitAdder32Node);
    }
    BitAdder32* bitAdder32Node;
};

TEST_F(BitAdder32Test, TestBitAdder32Propagate) {
    srand(403);
    for (int i = 0; i < 1000; i++) {
        uint64_t inputA = (uint64_t)(rand() % UINT32_MAX);
        uint64_t inputB = (uint64_t)(rand() % UINT32_MAX);
        uint64_t inputC = (uint64_t)(rand() & 1);

        num2bits(inputA, bitAdder32Node->inputA, 32);
        num2bits(inputB, bitAdder32Node->inputB, 32);
        bitAdder32Node->inputC = (bit)inputC;
        propagateBitAdder32(bitAdder32Node);

        EXPECT_EQ(bits2num(bitAdder32Node->output, 32), (inputA + inputB + inputC) % UINT32_MAX);
        EXPECT_EQ(bitAdder32Node->c, ((inputA + inputB + inputC) >> 32) & 1);
    }
}
