#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#include <string.h>
#include <stdio.h>

static char op_code_prefix[][10] = {"avail, cur"};

static char op_code_postfix[][10] = {"channel", "freq", "bitrate", "txpower"};

struct _console {
    char *op_code;
    int iface;
};

void console_read(char*);

#endif
