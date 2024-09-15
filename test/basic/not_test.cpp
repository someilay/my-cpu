#include "gtest/gtest.h"

extern "C"
{
#include "basic/not.h"
}


class NotTest : public testing::Test {
protected:
    NotTest() {
        notNode = newNot();
    }
    ~NotTest() {
        freeNot(notNode);
    }
    Not* notNode;
};


TEST_F(NotTest, TestNotPropagate) {
    notNode->input = 1;
    propagateNot(notNode);
    EXPECT_FALSE(notNode->output);

    notNode->input = 0;
    propagateNot(notNode);
    EXPECT_TRUE(notNode->output);
}
