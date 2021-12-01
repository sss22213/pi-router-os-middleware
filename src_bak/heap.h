#ifndef __HEAP_H__
#define __HEAP_H__
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tree.h"

#define INIT_HEAP(HEAP_NAME, HEAP_MEMORY, SIZE) \
        struct _heap (HEAP_NAME) = {HEAP_MEMORY, SIZE};

struct _heap {
    int *ptr_heap_memory;
    int size;
};

#endif