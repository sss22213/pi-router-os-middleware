#include "console.h"

static char cmd_prefix[] = {'i'};

// N * MAXIMUM_OPCODE_PREFIX_LENGTH + M
static char opcode_prefix[MAXIMUM_OPCODE_PREFIX_LENGTH][MAXIMUM_OPCODE_PREFIX_STRING_LENGTH] = {"cur", "avail"};

static char opcode_postfix[MAXIMUM_OPCODE_POSTFIX_LENGTH][MAXIMUM_OPCODE_POSTFIX_STRING_LENGTH] = {"channel", "freq", "bitrate", "txpower"};

static void (*ptr_excute_func[MAXIMUM_OPCODE_PREFIX_LENGTH*MAXIMUM_OPCODE_POSTFIX_LENGTH])(void*, struct _queue*) = {\
                        find_support_channel, find_support_freq,\
                        find_support_bitrate, find_support_txpower,\
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
    char *token = NULL;

    int idx = 0;

    INIT_QUEUE(q1, l1);

    // Interface
    int interface_number = atoi(opcode[3]);

    // Opcode
    char ptr_opcode[MAXIMUM_OPCODE_PREFIX_STRING_LENGTH+MAXIMUM_OPCODE_POSTFIX_STRING_LENGTH] = {0};
   
    // Prefix opcode
    char prefix_opcode[MAXIMUM_OPCODE_PREFIX_STRING_LENGTH] = {0};

    // Postfix opcode
    char postfix_opcode[MAXIMUM_OPCODE_POSTFIX_STRING_LENGTH] = {0};

    int prefix_opcode_idx = -1;

    int postfix_opcode_idx = -1;

    strcpy(ptr_opcode, opcode[1]);
   
    token = strtok(ptr_opcode, "_");
    strcpy(prefix_opcode, token);

    token = strtok(NULL, "_");
    strcpy(postfix_opcode, token);

    for (idx = 0; idx < MAXIMUM_OPCODE_PREFIX_LENGTH; idx++) {
        if (!strcmp(prefix_opcode, opcode_prefix[idx])) {
            prefix_opcode_idx = idx;
        }
    }

    for (idx = 0; idx < MAXIMUM_OPCODE_POSTFIX_LENGTH; idx++) {
        if (!strcmp(postfix_opcode, opcode_postfix[idx])) {
            postfix_opcode_idx = idx;
        }
    }

    ptr_excute_func[prefix_opcode_idx*2+postfix_opcode_idx](&interface_number, &q1);
}
