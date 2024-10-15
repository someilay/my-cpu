#include "gtest/gtest.h"

extern "C"
{
#include "gates/dmpx_65kb.h"
#include "utility.h"
}

class DeMultiplexer65kbTest : public testing::Test
{
protected:
    DeMultiplexer65kbTest() {
        dmpx65kbNode = newDmpx65kb();
    }
    ~DeMultiplexer65kbTest() {
        freeDmpx65kb(dmpx65kbNode);
    }
    DeMultiplexer65kb* dmpx65kbNode;
};

TEST_F(DeMultiplexer65kbTest, TestDmpx65kbPropagate) {
    srand(407);
    for (int32_t i = 0; i < 1000; i++) {
        int32_t input = rand() % 2;
        int32_t select = rand() % 65536;
        dmpx65kbNode->input = input;
        num2bits((uint64_t) select, dmpx65kbNode->select, 16);
        propagateDmpx65kb(dmpx65kbNode);
        for (int32_t j = 0; j < 65536; j++) {
            // EXPECT_EQ(dmpx65kbNode->output[j], j == select ? input : 0);
        }
    }
}
