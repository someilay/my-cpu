#include "gtest/gtest.h"

extern "C"
{
#include "gates/mpx_4.h"
}

class Multiplexer4Test : public testing::Test
{
protected:
    Multiplexer4Test() {
        mpx4node = newMpx4();
    }
    ~Multiplexer4Test() {
        freeMpx4(mpx4node);
    }
    Multiplexer4* mpx4node;
};

TEST_F(Multiplexer4Test, TestMpx4Propagate) {
    for (bit i = 0; i < 16; i++) {
        for (bit j = 0; j < 4; j++) {
            mpx4node->inputs[j] = (i >> j) & 1;
        }
        for (bit j = 0; j < 4; j++) {
            mpx4node->selectA = j & 1;
            mpx4node->selectB = (j >> 1) & 1;
            propagateMpx4(mpx4node);
            EXPECT_EQ(mpx4node->output, mpx4node->inputs[j]);
        }
    }
}
