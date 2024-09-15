#include "gtest/gtest.h"

extern "C"
{
#include "gates/xor.h"
}

class XorTest : public testing::Test
{
protected:
    XorTest() {
        xorNode = newXor();
    }
    ~XorTest() {
        freeXor(xorNode);
    }
    Xor* xorNode;
};

TEST_F(XorTest, TestXorPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            xorNode->inputA = i;
            xorNode->inputB = j;
            propagateXor(xorNode);
            EXPECT_EQ(xorNode->output, i ^ j);
        }
    }
}
