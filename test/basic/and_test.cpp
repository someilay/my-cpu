#include "gtest/gtest.h"

extern "C"
{
#include "basic/and.h"
}

class AndTest : public testing::Test
{
protected:
    AndTest() {
        andNode = newAnd();
    }
    ~AndTest() {
        freeAnd(andNode);
    }
    And* andNode;
};

TEST_F(AndTest, TestAndPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            andNode->inputA = i;
            andNode->inputB = j;
            propagateAnd(andNode);
            EXPECT_EQ(andNode->output, i & j);
        }
    }
}
