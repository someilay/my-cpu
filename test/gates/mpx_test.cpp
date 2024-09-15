#include "gtest/gtest.h"

extern "C"
{
#include "gates/mpx.h"
}

class MultiplexerTest : public testing::Test
{
protected:
    MultiplexerTest() {
        mpxNode = newMpx();
    }
    ~MultiplexerTest() {
        freeMpx(mpxNode);
    }
    Multiplexer* mpxNode;
};

TEST_F(MultiplexerTest, TestMpxPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            for (bit k = 0; k < 2; k++) {
                mpxNode->inputA = i;
                mpxNode->inputB = j;
                mpxNode->select = k;
                propagateMpx(mpxNode);
                EXPECT_EQ(mpxNode->output, k ? j : i);
            }
        }
    }
}
