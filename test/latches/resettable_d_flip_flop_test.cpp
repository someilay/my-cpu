#include "gtest/gtest.h"

extern "C"
{
#include "latches/resettable_d_flip_flop.h"
}

class ResettableDFlipFlopTest : public testing::Test
{
protected:
    ResettableDFlipFlopTest() {
        rdFlipFlopNode = newResettableDFlipFlop(0);
    }
    ~ResettableDFlipFlopTest() {
        freeResettableDFlipFlop(rdFlipFlopNode);
    }
    ResettableDFlipFlop* rdFlipFlopNode;
};

TEST_F(ResettableDFlipFlopTest, TestDFlipFlopPropagate) {
    for (bit i = 0; i < 4; i++) {
        rdFlipFlopNode->d = i & 1;
        propagateResettableDFlipFlop(rdFlipFlopNode);
        EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
        EXPECT_EQ(rdFlipFlopNode->q, 0);
    }

    rdFlipFlopNode->clk = 1;
    for (bit i = 0; i < 4; i++) {
        rdFlipFlopNode->d = i & 1;
        propagateResettableDFlipFlop(rdFlipFlopNode);
        EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
        EXPECT_EQ(rdFlipFlopNode->q, 1);
    }

    rdFlipFlopNode->clk = 0;
    rdFlipFlopNode->d = 0;
    propagateResettableDFlipFlop(rdFlipFlopNode);
    EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
    EXPECT_EQ(rdFlipFlopNode->q, 1);

    rdFlipFlopNode->clk = 1;
    rdFlipFlopNode->d = 1;
    propagateResettableDFlipFlop(rdFlipFlopNode);
    EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
    EXPECT_EQ(rdFlipFlopNode->q, 0);

    rdFlipFlopNode->clk = 0;
    propagateResettableDFlipFlop(rdFlipFlopNode);
    EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
    EXPECT_EQ(rdFlipFlopNode->q, 0);

    rdFlipFlopNode->clk = 1;
    propagateResettableDFlipFlop(rdFlipFlopNode);
    EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
    EXPECT_EQ(rdFlipFlopNode->q, 1);

    rdFlipFlopNode->clk = 0;
    rdFlipFlopNode->reset = 1;
    propagateResettableDFlipFlop(rdFlipFlopNode);
    rdFlipFlopNode->clk = 1;
    propagateResettableDFlipFlop(rdFlipFlopNode);
    EXPECT_NE(rdFlipFlopNode->q, rdFlipFlopNode->notQ);
    EXPECT_EQ(rdFlipFlopNode->q, 0);
}
