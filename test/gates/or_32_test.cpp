#include "gtest/gtest.h"
#include "limits.h"

extern "C"
{
#include "gates/or_32.h"
#include "utility.h"
}

class Or32Test : public testing::Test
{
protected:
    Or32Test() {
        or32node = newOr32();
    }
    ~Or32Test() {
        freeOr32(or32node);
    }
    Or32* or32node;
};

TEST_F(Or32Test, TestOr32Propagate) {
    srand(407);
    for (int i = 0; i < 1000; i++) {
        uint64_t input = (uint64_t)rand() % UINT32_MAX;
        num2bits(input, or32node->input, 32);
        propagateOr32(or32node);
        EXPECT_EQ(or32node->output, input != 0);
    }

    num2bits(0, or32node->input, 32);
    propagateOr32(or32node);
    EXPECT_EQ(or32node->output, 0);
}
