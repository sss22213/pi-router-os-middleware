#include "process.h"
#define REQUEST_SYSCALL_TOPIC "REQUEST_SYSCALL_TOPIC"


static inline void _process(char *topicName, char *msg_from_mqtt)
{
    cJSON *new_msg = NULL;

    cJSON *type = NULL;

    cJSON *syscall_number = NULL;

    if (strcmp(topicName, REQUEST_SYSCALL_TOPIC) != 0) {
        return;
    }

    type = cJSON_GetObjectItemCaseSensitive(new_msg, "type");
    if (strcmp(type->valuestring, "PI_ROUTER_OS_REQUEST_SYSCALL")!=0) {
        return;
    }

    syscall_number = cJSON_GetObjectItemCaseSensitive(new_msg, "syscall_number");
    switch (syscall_number->valueint) {
    case SYSCALL_PI_ROUTER_OS_VERSION:
    
        break;
    case SYSCALL_NETWORK_FIND_INTERFACE:

        break; 
    case SYSCALL_NETWORK_FIND_ACTIVE_INTERFACE:

        break;  
    case SYSCALL_NETWORK_FIND_SUPPORT_FREQUENCY:

        break;     
    case SYSCALL_NETWORK_FIND_SUPPORT_BITRATE:

        break;    
    case SYSCALL_NETWORK_FIND_SUPPORT_TXPOWER:

        break;
    case SYSCALL_NETWORK_AVAILABLE_CHANNEL:

        break;
    case SYSCALL_NETWORK_SUPPORT_FREQUENCY:

        break;   
    default:
        break;
    }
}