#ifndef MY_DEFINES
#define MY_DEFINES
#include "malloc.h"

#define S_MALLOC(varName, structName) structName* varName = (structName*) malloc(sizeof(structName))

#endif
