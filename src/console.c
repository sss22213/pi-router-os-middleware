#include "console.h"

/**
 * @brief Read console
 *      
 * @param argc number of argument 
 * @param console_string opcode + interface
 */
static inline void _read(char* console_string)
{
    const char s[2] = "-";
    char *token;
   
    /* get the first token */
    token = strtok(console_string, s);

    printf("%s\n", token);

}

void console_read(char* console_string)
{
    _read(console_string);
}