#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/32_not_32.h"
#include "utility.h"
}

class BitNot32to32Test : public testing::Test
{
protected:
    BitNot32to32Test() {
        not32to32Node = newNot32to32();
    }
    ~BitNot32to32Test() {
        freeNot32to32(not32to32Node);
    }
    Not32to32* not32to32Node;
};

TEST_F(BitNot32to32Test, TestNot32to32Propagate) {
    srand(403);
    for (int i = 0; i < 1000; i++) {
        uint32_t input = (uint32_t)(rand() % UINT32_MAX);
        num2bits((uint64_t) input, not32to32Node->input, 32);
        propagateNot32to32(not32to32Node);
        EXPECT_EQ(bits2num(not32to32Node->output, 32), ~input);
    }
}
