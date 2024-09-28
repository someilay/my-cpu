#ifndef MY_UTILITY
#define MY_UTILITY
#include "typedefs.h"
#include "stdint.h"

void num2bits(uint64_t num, bit* bits, uint64_t size);

uint64_t bits2num(bit* bits, uint64_t size);

#endif
