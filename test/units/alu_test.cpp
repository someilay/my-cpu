#include "gtest/gtest.h"
#include "limits.h"
#include <random>
#include <stdexcept>
#include <cstdlib>

extern "C"
{
#include "units/alu.h"
#include "utility.h"
}

class AluTest : public testing::Test
{
protected:
    AluTest() {
        aluNode = newAlu();
    }
    ~AluTest() {
        freeAlu(aluNode);
    }
    void setOverflow(bool isPlus) {
        int64_t inputAS = (int32_t)inputA;
        int64_t inputBS = (int32_t)inputB;
        if (isPlus) {
            overflow = (inputAS + inputBS > INT32_MAX || inputAS + inputBS < INT32_MIN) ? 1 : 0;
        }
        else {
            overflow = (inputAS - inputBS > INT32_MAX || inputAS - inputBS < INT32_MIN) ? 1 : 0;
        }
    }
    void setCarry(bool isPlus) {
        uint64_t inputBS = isPlus ? inputB : ((~inputB & UINT32_MAX) + 1);
        carry = ((inputA + inputBS) >> 32) & 1;
    }
    void setRightAnswer() {
        overflow = 0;
        carry = 0;
        switch (control) {
        case ALU_AND_OP:
            output = inputA & inputB;
            break;
        case ALU_OR_OP:
            output = inputA | inputB;
            break;
        case ALU_ADD_OP:
            output = (uint64_t)(uint32_t)((int32_t)inputA + (int32_t)inputB);
            setOverflow(true);
            setCarry(true);
            break;
        case ALU_SUB_OP:
            output = (uint64_t)(uint32_t)((int32_t)inputA - (int32_t)inputB);
            setOverflow(false);
            setCarry(false);
            break;
        case ALU_SLT_OP:
            output = ((int32_t)inputA < (int32_t)inputB);
            setOverflow(false);
            setCarry(false);
            break;
        case ALU_NOR_OP:
            output = (uint64_t)(uint32_t)(~(inputA | inputB));
            break;
        default:
            throw std::range_error("Invalid control signal!");
        }
        zero = output == 0;
    }
    void propagate() {
        num2bits(inputA, aluNode->inputA, 32);
        num2bits(inputB, aluNode->inputB, 32);
        num2bits(control, aluNode->control, 4);
        propagateAlu(aluNode);
    }
    Alu* aluNode;
    uint64_t inputA;
    uint64_t inputB;
    uint64_t control;
    uint64_t output;
    bit zero;
    bit overflow;
    bit carry;
};

TEST_F(AluTest, TestAluPropagate) {
    std::random_device rd;
    std::mt19937 gen(407);
    std::uniform_int_distribution<uint64_t> dis(0, UINT32_MAX);
    uint64_t controls[] = { ALU_AND_OP, ALU_OR_OP, ALU_ADD_OP, ALU_SUB_OP, ALU_SLT_OP, ALU_NOR_OP };

    for (int i = 0; i < 1000; i++) {
        inputA = dis(gen);
        inputB = dis(gen);
        control = controls[dis(gen) % 6];

        propagate();
        setRightAnswer();

        EXPECT_EQ(bits2num(aluNode->output, 32), output);
        EXPECT_EQ(aluNode->zero, zero);
        EXPECT_EQ(aluNode->carry, carry);
        EXPECT_EQ(aluNode->overflow, overflow);
    }

    // Edge cases
    inputA = INT32_MAX - 1;
    inputB = 1;
    control = ALU_ADD_OP;
    propagate();
    setRightAnswer();
    EXPECT_EQ(bits2num(aluNode->output, 32), output);
    EXPECT_EQ(aluNode->zero, zero);
    EXPECT_EQ(aluNode->carry, carry);
    EXPECT_EQ(aluNode->overflow, overflow);

    inputA = (uint64_t)INT32_MAX + 1;
    inputB = 1;
    control = ALU_ADD_OP;
    propagate();
    setRightAnswer();
    EXPECT_EQ(bits2num(aluNode->output, 32), output);
    EXPECT_EQ(aluNode->zero, zero);
    EXPECT_EQ(aluNode->carry, carry);
    EXPECT_EQ(aluNode->overflow, overflow);

    inputA = INT32_MAX - 1;
    inputB = (uint64_t)(uint32_t)-1;
    control = ALU_SUB_OP;
    propagate();
    setRightAnswer();
    EXPECT_EQ(bits2num(aluNode->output, 32), output);
    EXPECT_EQ(aluNode->zero, zero);
    EXPECT_EQ(aluNode->carry, carry);
    EXPECT_EQ(aluNode->overflow, overflow);

    inputA = (uint64_t)INT32_MAX + 2;
    inputB = 1;
    control = ALU_SUB_OP;
    propagate();
    setRightAnswer();
    EXPECT_EQ(bits2num(aluNode->output, 32), output);
    EXPECT_EQ(aluNode->zero, zero);
    EXPECT_EQ(aluNode->carry, carry);
    EXPECT_EQ(aluNode->overflow, overflow);
}
