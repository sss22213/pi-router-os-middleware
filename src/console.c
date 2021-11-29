#include "console.h"

static char cmd_prefix[] = {'i'};

static char opcode_prefix[MAXIMUM_OPCODE_PREFIX_LENGTH][MAXIMUM_OPCODE_PREFIX_STRING_LENGTH] = {"cur", "avail"};

static char opcode_postfix[MAXIMUM_OPCODE_POSTFIX_LENGTH][MAXIMUM_OPCODE_POSTFIX_STRING_LENGTH] = {"channel", "freq", "bitrate", "txpower"};

static void (*ptr_excute_func[MAXIMUM_OPCODE_PREFIX_LENGTH*MAXIMUM_OPCODE_POSTFIX_LENGTH])(void*, void *) = \
                        {find_support_channel, find_support_freq, find_support_bitrate, find_support_txpower,\
                            find_available_channel, find_available_freq};

static inline void _insert(struct _console *console, char *opcode) 
{
    const char s[2] = "_";
    char *token;

    /* get the first token */
    token = strtok(opcode, s);

    printf("%s\n", token+1);
}


static inline void _excute(struct _console *console, const char** opcode, int interface)
{

}

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

void init_console(struct _console *console)
{

}

void insert_console(struct _console *console, const char *opcode)
{
    _insert(console, (char*)opcode);
}

void console_excute_array(struct _console *console, int argc, char** opcode)
{
    int opcode_number = -1;
    int interface_number = opcode[1][2];

    // Compare cmd_prefix with opcode
    for (int cmd_prefix_idx = 0; cmd_prefix_idx < sizeof(cmd_prefix)/sizeof(cmd_prefix[0]); cmd_prefix_idx++) {
        if (opcode_number == cmd_prefix[cmd_prefix_idx]) {
            opcode_number = cmd_prefix_idx;
        }
    }
    


    //_excute_array(console, opcode, interface);
}
