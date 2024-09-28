#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/32_mpx_32.h"
#include "utility.h"
}

class BitMultiplexer32to32Test : public testing::Test
{
protected:
    BitMultiplexer32to32Test() {
        mpx32to32Node = newMpx32to32();
    }
    ~BitMultiplexer32to32Test() {
        freeMpx32to32(mpx32to32Node);
    }
    Multiplexer32to32* mpx32to32Node;
};

TEST_F(BitMultiplexer32to32Test, TestMultiplexer32to32Propagate) {
    srand(403);
    for (int i = 0; i < 1000; i++) {
        uint64_t inputA = (uint64_t)(rand() % UINT32_MAX);
        uint64_t inputB = (uint64_t)(rand() % UINT32_MAX);
        uint64_t select = (uint64_t)(rand() % 2);

        mpx32to32Node->select = (bit) select;
        num2bits(inputA, mpx32to32Node->inputA, 32);
        num2bits(inputB, mpx32to32Node->inputB, 32);
        propagateMpx32to32(mpx32to32Node);

        EXPECT_EQ(bits2num(mpx32to32Node->output, 32), select ? inputB : inputA);
    }
}
