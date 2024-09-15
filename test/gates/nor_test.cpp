#include "gtest/gtest.h"

extern "C"
{
#include "gates/nor.h"
}

class NorTest : public testing::Test
{
protected:
    NorTest() {
        norNode = newNor();
    }
    ~NorTest() {
        freeNor(norNode);
    }
    Nor* norNode;
};

TEST_F(NorTest, TestNorPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            norNode->inputA = i;
            norNode->inputB = j;
            propagateNor(norNode);
            EXPECT_EQ(norNode->output, !(i | j));
        }
    }
}
