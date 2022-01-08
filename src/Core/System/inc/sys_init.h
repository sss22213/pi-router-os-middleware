#ifndef __SYS_INIT_H__
#define __SYS_INIT_H__
#include "timer.h"
#include "event.h"
#include "mqtt_client.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

#define MQTT_SERVER_IP_PORT "tcp://127.0.0.1:1883"
#define MQTT_CLIENT_NAME "system"

struct _timer ptr_timer;
struct _mqtt_client new_mqtt_client;

void sys_init(void);

#endif