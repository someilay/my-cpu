#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/32_mpx_4_32.h"
#include "utility.h"
#include "defines.h"
}

class BitMultiplexer4x32to32Test : public testing::Test
{
protected:
    BitMultiplexer4x32to32Test() {
        mpx4x32to32Node = newMpx4x32to32();
    }
    ~BitMultiplexer4x32to32Test() {
        freeMpx4x32to32(mpx4x32to32Node);
    }
    Multiplexer4x32to32* mpx4x32to32Node;
};

TEST_F(BitMultiplexer4x32to32Test, TestMultiplexer4x32to32Propagate) {
    srand(403);
    A_MALLOC(input, uint64_t, 4);
    for (int i = 0; i < 1000; i++) {
        for (bit j = 0; j < 4; j++) {
            input[j] = (uint64_t)(rand() % UINT32_MAX);
        }
        uint64_t select = (uint64_t)(rand() % 4);

        mpx4x32to32Node->selectA = (bit) select & 1;
        mpx4x32to32Node->selectB = (bit) (select >> 1) & 1;
        for (bit j = 0; j < 4; j++) {
            num2bits(input[j], mpx4x32to32Node->input[j], 32);
        }
        propagateMpx4x32to32(mpx4x32to32Node);

        EXPECT_EQ(bits2num(mpx4x32to32Node->output, 32), input[select]);
    }
    free(input);
}
