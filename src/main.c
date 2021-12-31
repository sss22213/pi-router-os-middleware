#include <cjson/cJSON.h>
#include "mqtt_client.h"
#include "wireless.h"
#include "message.h"
#include <unistd.h>
#include "pi_router_os_version.h"

void msgarrive_event(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    struct _pi_router_os_version ret;

    cJSON *topic_name = NULL;

    cJSON *new_msg_json = cJSON_Parse(message->payload);

    topic_name = cJSON_GetObjectItemCaseSensitive(new_msg_json, "type_name");

    if (topic_name->valuestring != NULL) {
        if (strcmp(topic_name->valuestring, "PI_ROUTER_OS_VERSION") == 0) {
            printf("YES\n");
        }
    }
    




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
    char string[12000];
    struct _pi_router_os_version pi_router_os_version; 
    pi_router_os_version.test1=1;
    pi_router_os_version.test2=3;
    pi_router_os_version.test3[0] = 4;
    pi_router_os_version.test4[0] = 5;
    strcpy(pi_router_os_version.test, "You");
    pi_router_os_version_message_pack("test", pi_router_os_version, string);

   
    /*
    char *string = NULL;
    cJSON *monitor = cJSON_CreateObject();
    cJSON *name = cJSON_CreateString("Awesome 4K");
    cJSON_AddItemToObject(monitor, "name", name);
    string = cJSON_Print(monitor);
    cJSON_Delete(monitor);
    */

    INIT_MQTT_CLIENT(new_mqtt_client, "tcp://127.0.0.1:1883", "system");
    mqtt_client_subscribe(&new_mqtt_client, "Testx");

    while(1) {
        mqtt_client_publish(&new_mqtt_client, "Testx", string);
        sleep(1);
    }

    return 0;
}