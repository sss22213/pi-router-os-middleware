#ifndef __SYSCALL_H__
#define __SYSCALL_H__
#define SYSCALL_MAXIMUM_NUMBER  100
#include "map.h"
#include "list.h"
#include <cjson/cJSON.h>
#include <stdlib.h>

typedef enum {
    SYSCALL_EXCUTE_SUCCESS,
    SYSCALL_EXCUTE_FAILED,
} SYSCALL_EXCUTE;

struct _syscall {
    int syscall_number;
    SYSCALL_EXCUTE (*ptr_syscall_func)(cJSON *arg, cJSON *ret);
};

struct _list_syscall {
    int ptr_cur_syscall;
    struct _syscall ary_syscall[SYSCALL_MAXIMUM_NUMBER];
};

struct _list_syscall *syscall_init(void);
void syscall_deinit(struct _list_syscall*);
void syscall_register(struct _list_syscall*, struct _syscall*);
void syscall_unregister(struct _list_syscall*, struct _syscall);
SYSCALL_EXCUTE syscall_excute(struct _list_syscall*, int, cJSON*, cJSON*);

#endif