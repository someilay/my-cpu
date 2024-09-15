#include "gtest/gtest.h"

extern "C"
{
#include "basic/or.h"
}

class OrTest : public testing::Test
{
protected:
    OrTest() {
        orNode = newOr();
    }
    ~OrTest() {
        freeOr(orNode);
    }
    Or* orNode;
};

TEST_F(OrTest, TestOrPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            orNode->inputA = i;
            orNode->inputB = j;
            propagateOr(orNode);
            EXPECT_EQ(orNode->output, i | j);
        }
    }
}
