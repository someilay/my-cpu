#include "gtest/gtest.h"

extern "C"
{
#include "latches/sr_latch.h"
}

class SrLatchTest : public testing::Test
{
protected:
    SrLatchTest() {
        srLatchNodes = (SrLatch**)malloc(sizeof(SrLatch*) * 2);
        for (bit i = 0; i < 2; i++) {
            srLatchNodes[i] = newSrLatch(i);
        }
    }
    ~SrLatchTest() {
        for (bit i = 0; i < 2; i++) {
            freeSrLatch(srLatchNodes[i]);
        }
        free(srLatchNodes);
    }
    SrLatch** srLatchNodes;
};

TEST_F(SrLatchTest, TestSrLatchPropagate) {
    for (bit i = 0; i < 2; i++) {
        srLatchNodes[i]->set = 1;
        propagateSrLatch(srLatchNodes[i]);
        EXPECT_NE(srLatchNodes[i]->q, srLatchNodes[i]->notQ);
        EXPECT_EQ(srLatchNodes[i]->q, 1);

        srLatchNodes[i]->set = 0;
        propagateSrLatch(srLatchNodes[i]);
        EXPECT_NE(srLatchNodes[i]->q, srLatchNodes[i]->notQ);
        EXPECT_EQ(srLatchNodes[i]->q, 1);

        srLatchNodes[i]->reset = 1;
        propagateSrLatch(srLatchNodes[i]);
        EXPECT_NE(srLatchNodes[i]->q, srLatchNodes[i]->notQ);
        EXPECT_EQ(srLatchNodes[i]->q, 0);

        srLatchNodes[i]->reset = 0;
        propagateSrLatch(srLatchNodes[i]);
        EXPECT_NE(srLatchNodes[i]->q, srLatchNodes[i]->notQ);
        EXPECT_EQ(srLatchNodes[i]->q, 0);
    }
}
