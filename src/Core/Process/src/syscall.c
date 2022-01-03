#include "syscall.h"

/**
 * @brief Initialize structure of _list_syscall
 * 
 * @return struct _list_syscall*
 */
static inline struct _list_syscall *init(void)
{
    struct _list_syscall *list_syscall = (struct _list_syscall*)calloc(1, sizeof(struct _list_syscall));
    
    list_syscall->ptr_cur_syscall = 0;

    return list_syscall;
}

/**
 * @brief Deinitialize structure of _list_syscall
 * 
 * @param list_syscall 
 * @return void* 
 */
static inline void *deinit(struct _list_syscall *list_syscall) 
{
    free(list_syscall);
}

/**
 * @brief Register syscall into structure of _list_syscall 
 * 
 * @param list_syscall 
 * @param syscall 
 */
static inline void _register(struct _list_syscall *list_syscall, struct _syscall *syscall)
{
    list_syscall->ary_syscall[list_syscall->ptr_cur_syscall] = *syscall;

    list_syscall->ptr_cur_syscall++;
}

/**
 * @brief Unregister syscall into structure of _list_syscall 
 * 
 * @param list_syscall 
 * @param syscall 
 */
static inline void _unregister(struct _list_syscall *list_syscall, struct _syscall syscall)
{
    // Swapping specific syscall.
    struct _syscall ptr_tmp_syscall = list_syscall->ary_syscall[list_syscall->ptr_cur_syscall];
    list_syscall->ary_syscall[list_syscall->ptr_cur_syscall] = syscall;
    syscall = ptr_tmp_syscall;

    list_syscall->ptr_cur_syscall--;
}

/**
 * @brief Excute syscall
 * 
 * @param list_syscall 
 * @param syscall_number 
 * @param arg 
 * @return SYSCALL_EXCUTE 
 */
static inline SYSCALL_EXCUTE _excute(struct _list_syscall *list_syscall, int syscall_number, void *arg)
{
    //list_syscall->ary_syscall[syscall_number].ptr_syscall_func(arg);
}

