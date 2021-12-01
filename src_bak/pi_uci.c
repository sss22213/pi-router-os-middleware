#include "pi_uci.h"

static void analysis_string(struct _uci_cmd_stu *uci_cmd_stu, char *str)
{
    char *ptr_back = NULL;
    
    /* Get type or value */
    char *token = strtok_r(str, "=", &ptr_back);
    strcpy(uci_cmd_stu->_uci_format + MAX_CHAR_NUMBER_ON_LINE * 3, ptr_back);
    
    /* Get config, section, option */
    token = strtok_r(str, ".", &ptr_back);
    int idx = 0;
    while (token != NULL) {
        strcpy(uci_cmd_stu->_uci_format + idx * MAX_CHAR_NUMBER_ON_LINE, token);
        idx++;
        token = strtok_r(NULL, ".", &ptr_back);
    }

}

void _send_uci_command(struct _uci_cmd_list *uci_cmd_list, const char *command)
{
    FILE *ptr_cmd = NULL;
    
    ptr_cmd = popen(command, "r");

    char buf[MAX_CHAR_NUMBER_ON_LINE] = {0};

    /**
     * Maximum text number is limited by 100 character on every line.
     * Read data until file tail 
     */
    for (int line = 0; fgets(buf, MAX_CHAR_NUMBER_ON_LINE, ptr_cmd)!=NULL; line++) {
        uci_cmd_list->total_line++;
        analysis_string(uci_cmd_list->uci_multi_cmd + line, buf);
    }
    
    pclose(ptr_cmd);
}