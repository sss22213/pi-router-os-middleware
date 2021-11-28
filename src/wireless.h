#ifndef __WIRELESS_H__
#define __WIRELESS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define INIT_WIRELESS_IFACE(WIRELESS_IFACE_NAME) \
          struct _wireless_iface (WIRELESS_IFACE_NAME) = {0, {0}, {0}, {0}, 0, wireless_stop, NULL}

#define INIT_WIRELESS_HEAD(WIRELESS_IFACE_LIST_NAME) \
          struct _wireless_list (WIRELESS_IFACE_LIST_NAME) = {NULL}

#define INTERFACE_NAME_LENGTH 10
#define IFACE_NUMBER 100
#define IFACE_INFO  200
#define IFACE_FREQ_INFO 5
#define IFACE_CHANNEL_INFO 3


struct _channel_freq {
    /* GHZ */
    float freq;
    char channel;
    struct _node iface_node;
};

struct _wireless_iface_iwlist_node {
    struct _channel_freq current_channel_freq;
    struct _queue ptr_support_channel_freq;
    /* MB/s */
    float bitrate;
    /* dbm */
    int txpower;
};

struct _wireless_iface_node {
    int iface;
    struct _node iface_node;
};

struct _wireless_iface_active_node {
    int iface;
    char ip_addr[15];
    char broadcast[15];
    char hwaddr[17];
    int mask;
    struct _wireless_iface_iwlist_node wireless_iface_iwlist_node;
    struct _node iface_node;
};

struct _wireless_list {
    struct _wireless_iface *wireless_list_head;
};

void find_all_wireless_iface(struct _queue*);
void find_all_wireless_action_iface(struct _queue*);
struct _wireless_iface_iwlist_node *_find_support_freq_channel(int);

#endif