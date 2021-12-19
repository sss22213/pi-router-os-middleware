#include "mqtt_client.h"
#include <unistd.h>

void msgarrive_event(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("   Real message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
}

/**
 * @brief Main function
 * @param argv
 * 
 * Output: {"TOPIC_NAME:topic_name", "VALUE":{}}
 * 
 * @return int
 */

int main(int argc, char **argv)
{
    INIT_MQTT_CLIENT(new_mqtt_client, "tcp://127.0.0.1:1883", "system");
   
    mqtt_client_subscribe(&new_mqtt_client, "Testx");

    while(1) {
        mqtt_client_publish(&new_mqtt_client, "Testx", "BODT");
        sleep(1);
    }

    return 0;
}