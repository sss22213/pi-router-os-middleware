#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#include <string.h>
#include <stdio.h>
#include "wireless.h"
#include "map.h"

#define MAXIMUM_OPCODE_PREFIX_LENGTH   5
#define MAXIMUM_OPCODE_POSTFIX_LENGTH   5
#define MAXIMUM_OPCODE_PREFIX_STRING_LENGTH   10
#define MAXIMUM_OPCODE_POSTFIX_STRING_LENGTH   10
#define MAXIMUM_FUNC_CONSOLE_LENGTH (MAXIMUM_OPCODE_PREFIX_LENGTH * MAXIMUM_OPCODE_POSTFIX_LENGTH)

/*
static char op_code_prefix[MAXIMUM_OP_CODE_PREFIX_LENGTH][MAXIMUM_OP_CODE_PREFIX_STRING_LENGTH] = \
                            {"avail, cur"};

static char op_code_postfix[MAXIMUM_OP_CODE_POSTFIX_LENGTH][MAXIMUM_OP_CODE_POSTFIX_STRING_LENGTH] = \
                            {"channel", "freq", "bitrate", "txpower"};
*/

struct _func_console {
    void (*func)(void*);
    int number;
};

struct _console {
    char *op_code;
    struct _func_console func_console[MAXIMUM_OPCODE_PREFIX_LENGTH][MAXIMUM_OPCODE_POSTFIX_LENGTH];
};


void init_console(struct _console*);
void insert_console(struct _console*, const char*);
void console_excute_array(struct _console *console, int, char**);

#endif
