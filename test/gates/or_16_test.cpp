#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/or_16.h"
#include "utility.h"
}

class Or16Test : public testing::Test
{
protected:
    Or16Test() {
        or16node = newOr16();
    }
    ~Or16Test() {
        freeOr16(or16node);
    }
    Or16* or16node;
};

TEST_F(Or16Test, TestOr16Propagate) {
    srand(407);
    for (int i = 0; i < 1000; i++) {
        uint64_t input = (uint64_t)rand() % UINT16_MAX;
        num2bits(input, or16node->input, 16);
        propagateOr16(or16node);
        EXPECT_EQ(or16node->output, input != 0);
    }

    num2bits(0, or16node->input, 16);
    propagateOr16(or16node);
    EXPECT_EQ(or16node->output, 0);
}
