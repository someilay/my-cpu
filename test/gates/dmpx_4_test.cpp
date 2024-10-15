#include "gtest/gtest.h"

extern "C"
{
#include "gates/dmpx_4.h"
}

class DeMultiplexer4Test : public testing::Test
{
protected:
    DeMultiplexer4Test() {
        dmpx4node = newDmpx4();
    }
    ~DeMultiplexer4Test() {
        freeDmpx4(dmpx4node);
    }
    DeMultiplexer4* dmpx4node;
};

TEST_F(DeMultiplexer4Test, TestDmpx4Propagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 4; j++) {
            dmpx4node->input = i;
            dmpx4node->selectA = j & 1;
            dmpx4node->selectB = (j >> 1) & 1;
            propagateDmpx4(dmpx4node);
            for (bit k = 0; k < 4; k++) {
                EXPECT_EQ(dmpx4node->outputs[k], j == k ? i : 0);
            }
        }
    }
}
