#ifndef __PI_ROUTER_OS_SUPPORT_ACTION_IFACE_H__
#define __PI_ROUTER_OS_SUPPORT_ACTION_IFACE_H__

#include <cjson/cJSON.h>
#include <string.h>

#define PI_ROUTER_OS_SUPPORT_ACTION_IFACE_OFFSETOF(TYPE,MEMBER)\
        (size_t)&(((TYPE*)0)->MENBER)

#define PI_ROUTER_OS_SUPPORT_ACTION_IFACE_CONTAINER_OF(PTR,TYPE,MEMBER)\
        ({const typeof(((TYPE*)0->MEMBER)) *__mptr = (PTR);\
        (TYPE*)((char*)__mptr - PI_ROUTER_OS_SUPPORT_ACTION_IFACE_OFFSETOF(TYPE,MEMBER)};)

#define PI_ROUTER_OS_SUPPORT_ACTION_IFACE_OFFSET_EVERY_ITEM(TYPE)\
        {PI_ROUTER_OS_SUPPORT_ACTION_IFACE_ITEM}

struct _pi_router_os_support_action_iface{
	int iface;
	char ip_addr[15];
	char broadcast[15];
	char hwaddr[17];
	int mask;
};

void pi_router_os_support_action_iface_message_pack(char*, struct _pi_router_os_support_action_iface, char*);
void pi_router_os_support_action_iface_message_unpack(char*, struct _pi_router_os_support_action_iface*);


#endif