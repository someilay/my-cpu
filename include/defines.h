#ifndef MY_DEFINES
#define MY_DEFINES
#include "malloc.h"
#include "memory.h"

#define S_MALLOC(varName, structName) structName* varName = (structName*) malloc(sizeof(structName))
#define SI_MALLOC(varName, structName) varName = (structName*) malloc(sizeof(structName))
#define A_MALLOC(varName, typeName, size) typeName* varName = (typeName*) malloc(sizeof(typeName) * size)
#define AI_MALLOC(varName, typeName, size) varName = (typeName*) malloc(sizeof(typeName) * size)
#define AF_MALLOC(varName, typeName, size, value) A_MALLOC(varName, typeName, size); memset(varName, value, sizeof(typeName) * size)
#define AIF_MALLOC(varName, typeName, size, value) AI_MALLOC(varName, typeName, size); memset(varName, value, sizeof(typeName) * size)

#endif
