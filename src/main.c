#include <cjson/cJSON.h>
#include "mqtt_client.h"
#include "wireless.h"
#include "message.h"
#include "sys_init.h"
#include "socket.h"
#include <stdio.h>
#include <unistd.h>
#include "pi_router_os_version.h"

void msgarrive_event(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    struct _pi_router_os_version ret;

    cJSON *topic_name = NULL;

    cJSON *new_msg_json = cJSON_Parse(message->payload);
    
    topic_name = cJSON_GetObjectItemCaseSensitive(new_msg_json, "type_name");

    /*
    if (topic_name->valuestring != NULL) {
        printf("%s\n", topic_name->valuestring);
        
        if (strcmp(topic_name->valuestring, "PI_ROUTER_OS_VERSION") == 0) {
            printf("YES\n");
    
        
    }
    */
    
    /* printf("%s\n",topicName);
    pi_router_os_version_message_unpack(message->payload, &ret);
    
    for (int idx = 0; idx < 5; idx++) {
        printf("%e\n", ret.test3[idx]);
    }
    */
    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
}

/**
 * @brief Main function
 * @param argv
 * 
 * Output: {"type_name":"type names", "field":value}
 * 
 * @return int
 */
int main(int argc, char **argv)
{
    /*
    sys_init();
    */

    struct _socket new_socket;

    //mqtt_client_subscribe(&new_mqtt_client, "Testx");

    printf("%d\n", socket_init(&new_socket));

    socket_run_forever(&new_socket);

    return 0;
}