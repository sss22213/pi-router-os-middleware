#ifndef __SYSCALL_H__
#define __SYSCALL_H__
#define SYSCALL_MAXIMUM_NUMBER  100
#include "map.h"
#include "list.h"
#include <stdlib.h>

typedef enum {
    SYSCALL_EXCUTE_SUCCESS,
    SYSCALL_EXCUTE_FAILED,
} SYSCALL_EXCUTE;

struct _syscall {
    int syscall_number;
    SYSCALL_EXCUTE (*ptr_syscall_func)(void *arg, void *ret);
    struct _node syscall_node;
};

struct _list_syscall {
    int ptr_cur_syscall;
    struct _syscall ary_syscall[SYSCALL_MAXIMUM_NUMBER];
};

#endif