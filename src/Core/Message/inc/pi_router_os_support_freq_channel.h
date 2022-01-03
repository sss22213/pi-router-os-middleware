#ifndef __PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_H__
#define __PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_H__

#include <cjson/cJSON.h>
#include <string.h>

#define PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_OFFSETOF(TYPE,MEMBER)\
        (size_t)&(((TYPE*)0)->MENBER)

#define PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_CONTAINER_OF(PTR,TYPE,MEMBER)\
        ({const typeof(((TYPE*)0->MEMBER)) *__mptr = (PTR);\
        (TYPE*)((char*)__mptr - PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_OFFSETOF(TYPE,MEMBER)};)

#define PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_OFFSET_EVERY_ITEM(TYPE)\
        {PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL_ITEM}

struct _pi_router_os_support_freq_channel{
	float freq[50];
	int channel[50];
};

void pi_router_os_support_freq_channel_message_pack(char*, struct _pi_router_os_support_freq_channel, char*);
void pi_router_os_support_freq_channel_message_unpack(char*, struct _pi_router_os_support_freq_channel*);


#endif