#include "mqtt_client.h"

#define QOS 1

static inline _Bool _init(struct _mqtt_client *mqtt_client, char *address, char *client_id)
{
    memcpy(&mqtt_client->conn_opts, \
                    &(MQTTClient_connectOptions)MQTTClient_connectOptions_initializer, \
                    sizeof(MQTTClient_connectOptions));

    mqtt_client->conn_opts.keepAliveInterval = 20;
    mqtt_client->conn_opts.cleansession = 1;

    strcpy(mqtt_client->addr, address);
    strcpy(mqtt_client->client_id, client_id);

    MQTTClient_create(&mqtt_client->client, mqtt_client->addr, \
                                mqtt_client->client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    MQTTClient_setCallbacks(mqtt_client->client, NULL, mqtt_client->ptr_connlost_event, \
                                mqtt_client->ptr_msgarrive_event, mqtt_client->ptr_delivered_event);

    return MQTTClient_connect(mqtt_client->client, &mqtt_client->conn_opts);
}

static inline _Bool _publish(struct _mqtt_client *mqtt_client, char *topic_name, char *payload)
{
    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    MQTTClient_deliveryToken token;

    pubmsg.payload = payload;

    pubmsg.payloadlen = (int)strlen(payload);

    pubmsg.qos = QOS;

    pubmsg.retained = 0;

    MQTTClient_publishMessage(mqtt_client->client, topic_name, &pubmsg, &token);

    return MQTTClient_waitForCompletion(mqtt_client->client, token, 1000);
}

static inline _Bool _subscribe(struct _mqtt_client *mqtt_client, char *topic_name)
{
    return MQTTClient_subscribe(mqtt_client->client, topic_name, QOS);
}

_Bool mqtt_client_init(struct _mqtt_client *mqtt_client, char *address, char *client_id)
{
    return _init(mqtt_client, address, client_id);
}

void delivered_event(void *context, MQTTClient_deliveryToken dt)
{
    1 == 1;
}

__attribute__((weak)) void msgarrive_event(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
}

void connlost_event(void *context, char *cause)
{
     1 == 1;
}

_Bool mqtt_client_publish(struct _mqtt_client *mqtt_client, char *topic_name, char *payload)
{
    return _publish(mqtt_client, topic_name, payload);
}

_Bool mqtt_client_subscribe(struct _mqtt_client *mqtt_client, char *topic_name)
{
    return _subscribe(mqtt_client, topic_name);
}