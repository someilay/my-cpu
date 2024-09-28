#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/32_or_32.h"
#include "utility.h"
}

class BitOr32to32Test : public testing::Test
{
protected:
    BitOr32to32Test() {
        or32to32Node = newOr32to32();
    }
    ~BitOr32to32Test() {
        freeOr32to32(or32to32Node);
    }
    Or32to32* or32to32Node;
};

TEST_F(BitOr32to32Test, TestOr32to32Propagate) {
    srand(403);
    for (int i = 0; i < 1000; i++) {
        uint64_t inputA = (uint64_t)(rand() % UINT32_MAX);
        uint64_t inputB = (uint64_t)(rand() % UINT32_MAX);

        num2bits(inputA, or32to32Node->inputA, 32);
        num2bits(inputB, or32to32Node->inputB, 32);
        propagateOr32to32(or32to32Node);

        EXPECT_EQ(bits2num(or32to32Node->output, 32), inputA | inputB);
    }
}
