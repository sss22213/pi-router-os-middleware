#include "sys_init.h"

static struct itimerval value;

static inline void systick(int sig)
{
    ptr_timer.ptr_process_event_timer(&ptr_timer);
}

static inline void init_sys_timer_func()
{
    // Linux signal
    signal(SIGALRM, systick);
}

static inline void start_sys_timer_func()
{
    // For Linux settimout, 1ms
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 1000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 1000;
    setitimer(ITIMER_REAL, &value, NULL);
}

static inline void stop_sys_timer_func()
{
    // For Linux settimout
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, NULL);
}

static inline void _init_timer()
{
    NEW_TIMER(timer1, init_sys_timer_func, start_sys_timer_func, stop_sys_timer_func, process_event);
    timer_init(&timer1);

    memcpy(&ptr_timer, &timer1, sizeof(struct _timer));

    /*
        printf("Before delay 5 tick \n");
        timer_delay(&ptr_timer, 5000);
        printf("After delay 5 tick \n");
    */

    NEW_EVENT_TIMER(timer_event_1, EVENT_GET_NETWORK_INTERFACE_INFO, 1000);
    NEW_EVENT_TIMER(timer_event_2, EVENT_TEST1, 2000);
    NEW_EVENT_TIMER(timer_event_3, EVENT_TEST2, 2000);

    timer_settimeevent(&ptr_timer, &timer_event_1);
    timer_settimeevent(&ptr_timer, &timer_event_2);
    timer_settimeevent(&ptr_timer, &timer_event_3);
}

static inline void _init_mqtt()
{
    INIT_MQTT_CLIENT_PTR(&new_mqtt_client, MQTT_SERVER_IP_PORT, MQTT_CLIENT_NAME);
}

void sys_init()
{
    _init_mqtt();
    _init_timer();
}