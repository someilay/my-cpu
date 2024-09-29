#include "gtest/gtest.h"

extern "C"
{
#include "gates/or_8.h"
#include "utility.h"
}

class Or8Test : public testing::Test
{
protected:
    Or8Test() {
        or8node = newOr8();
    }
    ~Or8Test() {
        freeOr8(or8node);
    }
    Or8* or8node;
};

TEST_F(Or8Test, TestOr8Propagate) {
    for (uint64_t i = 0; i < 256; i++) {
        num2bits(i, or8node->input, 8);
        propagateOr8(or8node);
        EXPECT_EQ(or8node->output, i > 0);
    }
}
