#include "gtest/gtest.h"

extern "C"
{
#include "arithmetic_units/full_adder.h"
}

class FullAdderTest : public testing::Test
{
protected:
    FullAdderTest() {
        fullAdderNode = newFullAdder();
    }
    ~FullAdderTest() {
        freeFullAdder(fullAdderNode);
    }
    FullAdder* fullAdderNode;
};

TEST_F(FullAdderTest, TestFullAdderPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            for (bit k = 0; k < 2; k++)
            {
                fullAdderNode->inputA = i;
                fullAdderNode->inputB = j;
                fullAdderNode->inputC = k;
                propagateFullAdder(fullAdderNode);
                EXPECT_EQ(fullAdderNode->s, (i + j + k) & 1);
                EXPECT_EQ(fullAdderNode->c, (i + j + k) >> 1);
            }
        }
    }
}
