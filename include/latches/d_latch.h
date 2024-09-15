#ifndef LATCHES_D_LATCH_H
#define LATCHES_D_LATCH_H
#include "typedefs.h"
#include "latches/sr_latch.h"
#include "basic/not.h"
#include "basic/and.h"

typedef struct {
    Not* notNode;
    And* andA;
    And* andB;
    SrLatch* latch;
} InternalDLatch;

typedef struct {
    bit clk;
    bit d;
    bit q;
    bit notQ;
    InternalDLatch* internal;
} DLatch;

DLatch* newDLatch(bit q);

void propagateDLatch(DLatch* node);

void printDLatch(DLatch* node);

void freeDLatch(DLatch* node);

#endif
