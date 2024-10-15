#include "gtest/gtest.h"

extern "C"
{
#include "gates/dmpx_256.h"
#include "utility.h"
}

class DeMultiplexer256Test : public testing::Test
{
protected:
    DeMultiplexer256Test() {
        dmpx256node = newDmpx256();
    }
    ~DeMultiplexer256Test() {
        freeDmpx256(dmpx256node);
    }
    DeMultiplexer256* dmpx256node;
};

TEST_F(DeMultiplexer256Test, TestDmpx256Propagate) {
    for (int32_t i = 0; i < 2; i++) {
        for (int32_t j = 0; j < 256; j++) {
            dmpx256node->input = i;
            num2bits((uint64_t) j, dmpx256node->select, 8);
            propagateDmpx256(dmpx256node);
            for (int32_t k = 0; k < 256; k++) {
                EXPECT_EQ(dmpx256node->output[k], j == k ? i : 0);
            }
        }
    }
}
