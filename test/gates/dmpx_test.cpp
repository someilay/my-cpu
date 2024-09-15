#include "gtest/gtest.h"

extern "C"
{
#include "gates/dmpx.h"
}

class DeMultiplexerTest : public testing::Test
{
protected:
    DeMultiplexerTest() {
        dmpxNode = newDmpx();
    }
    ~DeMultiplexerTest() {
        freeDmpx(dmpxNode);
    }
    DeMultiplexer* dmpxNode;
};

TEST_F(DeMultiplexerTest, TestDmpxPropagate) {
    for (bit i = 0; i < 2; i++) {
        for (bit j = 0; j < 2; j++) {
            dmpxNode->input = i;
            dmpxNode->select = j;
            propagateDmpx(dmpxNode);
            EXPECT_EQ(dmpxNode->outputA, j ? 0 : i);
            EXPECT_EQ(dmpxNode->outputB, j ? i : 0);
        }
    }
}
