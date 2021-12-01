#ifndef __PI_UCI_H__
#define __PI_UCI_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define offsetof(TYPE, MEMBER)  ((size_t)&((TYPE *)0)->MEMBER)
#define MAX_LINE  100
#define MAX_CHAR_NUMBER_ON_LINE 1024

#define INIT_UCI_LIST(STU_LIST_NAME) \
            struct _uci_cmd_list (STU_LIST_NAME) = {0};

#define UCI_LIST_FOR_EACH(POS, STU_LIST_NAME) \
            for ((POS) = 0; (POS) < (STU_LIST_NAME)->total_line; (POS)++)
            

struct _uci_cmd_stu {
    union {
        char _uci_format[MAX_CHAR_NUMBER_ON_LINE * 4];
        struct {
            char config[MAX_CHAR_NUMBER_ON_LINE];
            char section[MAX_CHAR_NUMBER_ON_LINE];
            char option[MAX_CHAR_NUMBER_ON_LINE];
            char type_value[MAX_CHAR_NUMBER_ON_LINE];
        };
    };

};

struct _uci_cmd_list {
    int total_line;
    struct _uci_cmd_stu uci_multi_cmd[MAX_LINE];
};

void _send_uci_command(struct _uci_cmd_list*, const char*);

#endif