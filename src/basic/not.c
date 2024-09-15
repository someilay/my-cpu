#include "malloc.h"
#include "basic/not.h"

Not *newNot()
{
    Not* ret = (Not *)malloc(sizeof(Not));
    ret->input = 0;
    ret->output = 1;
    return ret;
}

void propagateNot(Not* node) {
    node->output = !node->input;
}


void printNot(Not* node) {
    printf("Node(input=%d, output=%d)\n", node->input, node->output);
}


void freeNot(Not* node) {
    free(node);
}
