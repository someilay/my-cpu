#include "gtest/gtest.h"

extern "C"
{
#include "arithmetic_units/half_adder.h"
}

class HalfAdderTest : public testing::Test
{
protected:
    HalfAdderTest() {
        halfAdderNode = newHalfAdder();
    }
    ~HalfAdderTest() {
        freeHalfAdder(halfAdderNode);
    }
    HalfAdder* halfAdderNode;
};

TEST_F(HalfAdderTest, TestHalfAdderPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            halfAdderNode->inputA = i;
            halfAdderNode->inputB = j;
            propagateHalfAdder(halfAdderNode);
            EXPECT_EQ(halfAdderNode->s, (i + j) & 1);
            EXPECT_EQ(halfAdderNode->c, (i + j) >> 1);
        }
    }
}
