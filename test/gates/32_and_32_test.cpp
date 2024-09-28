#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/32_and_32.h"
#include "utility.h"
}

class BitAnd32to32Test : public testing::Test
{
protected:
    BitAnd32to32Test() {
        and32to32Node = newAnd32to32();
    }
    ~BitAnd32to32Test() {
        freeAnd32to32(and32to32Node);
    }
    And32to32* and32to32Node;
};

TEST_F(BitAnd32to32Test, TestAnd32to32Propagate) {
    srand(403);
    for (int i = 0; i < 1000; i++) {
        uint64_t inputA = (uint64_t)(rand() % UINT32_MAX);
        uint64_t inputB = (uint64_t)(rand() % UINT32_MAX);

        num2bits(inputA, and32to32Node->inputA, 32);
        num2bits(inputB, and32to32Node->inputB, 32);
        propagateAnd32to32(and32to32Node);

        EXPECT_EQ(bits2num(and32to32Node->output, 32), inputA & inputB);
    }
}
