#include "gtest/gtest.h"

extern "C"
{
#include "latches/d_flip_flop.h"
}

class DFlipFlopTest : public testing::Test
{
protected:
    DFlipFlopTest() {
        dFlipFlopNode = newDFlipFlop(0);
    }
    ~DFlipFlopTest() {
        freeDFlipFlop(dFlipFlopNode);
    }
    DFlipFlop* dFlipFlopNode;
};

TEST_F(DFlipFlopTest, TestDFlipFlopPropagate) {
    for (bit i = 0; i < 4; i++) {
        dFlipFlopNode->d = i & 1;
        propagateDFlipFlop(dFlipFlopNode);
        EXPECT_NE(dFlipFlopNode->q, dFlipFlopNode->notQ);
        EXPECT_EQ(dFlipFlopNode->q, 0);
    }

    dFlipFlopNode->clk = 1;
    for (bit i = 0; i < 4; i++) {
        dFlipFlopNode->d = i & 1;
        propagateDFlipFlop(dFlipFlopNode);
        EXPECT_NE(dFlipFlopNode->q, dFlipFlopNode->notQ);
        EXPECT_EQ(dFlipFlopNode->q, 1);
    }

    dFlipFlopNode->clk = 0;
    dFlipFlopNode->d = 0;
    propagateDFlipFlop(dFlipFlopNode);
    EXPECT_NE(dFlipFlopNode->q, dFlipFlopNode->notQ);
    EXPECT_EQ(dFlipFlopNode->q, 1);

    dFlipFlopNode->clk = 1;
    dFlipFlopNode->d = 1;
    propagateDFlipFlop(dFlipFlopNode);
    EXPECT_NE(dFlipFlopNode->q, dFlipFlopNode->notQ);
    EXPECT_EQ(dFlipFlopNode->q, 0);

    dFlipFlopNode->clk = 0;
    propagateDFlipFlop(dFlipFlopNode);
    EXPECT_NE(dFlipFlopNode->q, dFlipFlopNode->notQ);
    EXPECT_EQ(dFlipFlopNode->q, 0);

    dFlipFlopNode->clk = 1;
    propagateDFlipFlop(dFlipFlopNode);
    EXPECT_NE(dFlipFlopNode->q, dFlipFlopNode->notQ);
    EXPECT_EQ(dFlipFlopNode->q, 1);
}
