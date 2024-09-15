#include "gtest/gtest.h"

extern "C"
{
#include "gates/or_4.h"
}

class Or4Test : public testing::Test
{
protected:
    Or4Test() {
        or4node = newOr4();
    }
    ~Or4Test() {
        freeOr4(or4node);
    }
    Or4* or4node;
};

TEST_F(Or4Test, TestOr4Propagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            for (bit k = 0; k < 2; k++) {
                for (bit l = 0; l < 2; l++) {
                    or4node->inputs[0] = i;
                    or4node->inputs[1] = j;
                    or4node->inputs[2] = k;
                    or4node->inputs[3] = l;
                    propagateOr4(or4node);
                    EXPECT_EQ(or4node->output, i | j | k | l);
                }
            }
        }
    }
}
