#ifndef __MQTT_H__
#define __MQTT_H__
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include "MQTTClient.h"

#define ADDRESS_LENGTH  100
#define CLIENT_ID_LENGTH  20

#define INIT_MQTT_CLIENT(MQTT_CLIENT_NAME, ADDRESS, CLIENT_ID) \
                            struct _mqtt_client (MQTT_CLIENT_NAME) = { \
                                .ptr_delivered_event = delivered_event, \
                                .ptr_msgarrive_event = msgarrive_event, \
                                .ptr_connlost_event = connlost_event, \
                            };\
                            mqtt_client_init(&MQTT_CLIENT_NAME, ADDRESS, CLIENT_ID);

#define INIT_MQTT_CLIENT_PTR(PTR_MQTT_CLIENT, ADDRESS, CLIENT_ID) \
                            (PTR_MQTT_CLIENT)->ptr_delivered_event = delivered_event;\
                            (PTR_MQTT_CLIENT)->ptr_msgarrive_event = msgarrive_event;\
                            (PTR_MQTT_CLIENT)->ptr_connlost_event = connlost_event;\
                            mqtt_client_init((PTR_MQTT_CLIENT), ADDRESS, CLIENT_ID);

struct _mqtt_client {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts;

    char addr[ADDRESS_LENGTH];
    char client_id[CLIENT_ID_LENGTH];

    void (*ptr_delivered_event)(void*, MQTTClient_deliveryToken);
    void (*ptr_msgarrive_event)(void*, char *,int, MQTTClient_message*);
    void (*ptr_connlost_event)(void*, char*);
};

_Bool mqtt_client_init(struct _mqtt_client*, char*, char*);
_Bool mqtt_client_publish(struct _mqtt_client*, char*, char*);
_Bool mqtt_client_subscribe(struct _mqtt_client*, char*);
void delivered_event(void*, MQTTClient_deliveryToken);
__attribute__((weak)) void msgarrive_event(void*, char*,int, MQTTClient_message*);
void connlost_event(void*, char*);

#endif