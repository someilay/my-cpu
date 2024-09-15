#ifndef LATCHES_SR_LATCH_H
#define LATCHES_SR_LATCH_H
#include "typedefs.h"
#include "gates/nor.h"

typedef struct {
    Nor* norA;
    Nor* norB;
} InternalSrLatch;

typedef struct {
    bit set;
    bit reset;
    bit q;
    bit notQ;
    InternalSrLatch* internal;
} SrLatch;

SrLatch* newSrLatch(bit q);

void propagateSrLatch(SrLatch* node);

void printSrLatch(SrLatch* node);

void freeSrLatch(SrLatch* node);

#endif
