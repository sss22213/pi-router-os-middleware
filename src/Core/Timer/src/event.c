#include "event.h"

void get_network_interface_info(void)
{
    char string1[1200] = {0};
    get_all_wireless_action_iface(string1);
    mqtt_client_publish(&new_mqtt_client, "Testx", string1);
    printf("func1\n");
}

void event_func2(void)
{
    printf("func2\n");
}

void event_func3(void)
{
    printf("func3\n");
}

void process_event(TIMER_EVENT timer_event)
{
    switch (timer_event) {
    case EVENT_GET_NETWORK_INTERFACE_INFO:
        get_network_interface_info();
        break;

    case EVENT_TEST1:
        event_func2();
        break;

    case EVENT_TEST2:
        event_func3();
        break;

    default:
        break;
    }
}