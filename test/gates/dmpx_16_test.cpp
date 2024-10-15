#include "gtest/gtest.h"

extern "C"
{
#include "gates/dmpx_16.h"
#include "utility.h"
}

class DeMultiplexer16Test : public testing::Test
{
protected:
    DeMultiplexer16Test() {
        dmpx16node = newDmpx16();
    }
    ~DeMultiplexer16Test() {
        freeDmpx16(dmpx16node);
    }
    DeMultiplexer16* dmpx16node;
};

TEST_F(DeMultiplexer16Test, TestDmpx16Propagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 16; j++) {
            dmpx16node->input = i;
            num2bits((uint64_t) j, dmpx16node->select, 4);
            propagateDmpx16(dmpx16node);
            for (bit k = 0; k < 16; k++) {
                EXPECT_EQ(dmpx16node->output[k], j == k ? i : 0);
            }
        }
    }
}
