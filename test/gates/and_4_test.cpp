#include "gtest/gtest.h"

extern "C"
{
#include "gates/and_4.h"
}

class And4Test : public testing::Test
{
protected:
    And4Test() {
        and4node = newAnd4();
    }
    ~And4Test() {
        freeAnd4(and4node);
    }
    And4* and4node;
};

TEST_F(And4Test, TestAnd4Propagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            for (bit k = 0; k < 2; k++) {
                for (bit l = 0; l < 2; l++) {
                    and4node->inputs[0] = i;
                    and4node->inputs[1] = j;
                    and4node->inputs[2] = k;
                    and4node->inputs[3] = l;
                    propagateAnd4(and4node);
                    EXPECT_EQ(and4node->output, i & j & k & l);
                }
            }
        }
    }
}
