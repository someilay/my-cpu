#include "gtest/gtest.h"

extern "C"
{
#include "latches/d_latch.h"
}

class DLatchTest : public testing::Test
{
protected:
    DLatchTest() {
        dLatchNode = newDLatch(0);
    }
    ~DLatchTest() {
        freeDLatch(dLatchNode);
    }
    DLatch* dLatchNode;
};

TEST_F(DLatchTest, TestDLatchPropagate) {
    for (bit i = 0; i < 4; i++) {
        dLatchNode->d = i & 1;
        propagateDLatch(dLatchNode);
        EXPECT_NE(dLatchNode->q, dLatchNode->notQ);
        EXPECT_EQ(dLatchNode->q, 0);
    }

    dLatchNode->d = 1;
    dLatchNode->clk = 1;
    propagateDLatch(dLatchNode);
    EXPECT_NE(dLatchNode->q, dLatchNode->notQ);
    EXPECT_EQ(dLatchNode->q, 1);

    for (bit i = 0; i < 4; i++) {
        dLatchNode->d = i & 1;
        propagateDLatch(dLatchNode);
        EXPECT_NE(dLatchNode->q, dLatchNode->notQ);
        EXPECT_EQ(dLatchNode->q, i & 1);
    }

    dLatchNode->clk = 0;
    dLatchNode->d = 0;
    propagateDLatch(dLatchNode);
    EXPECT_NE(dLatchNode->q, dLatchNode->notQ);
    EXPECT_EQ(dLatchNode->q, 1);

    dLatchNode->clk = 1;
    dLatchNode->d = 0;
    propagateDLatch(dLatchNode);
    EXPECT_NE(dLatchNode->q, dLatchNode->notQ);
    EXPECT_EQ(dLatchNode->q, 0);
}
