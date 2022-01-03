#ifndef __PI_ROUTER_OS_VERSION_H__
#define __PI_ROUTER_OS_VERSION_H__

#include <cjson/cJSON.h>
#include <string.h>

#define PI_ROUTER_OS_VERSION_OFFSETOF(TYPE,MEMBER)\
        (size_t)&(((TYPE*)0)->MENBER)

#define PI_ROUTER_OS_VERSION_CONTAINER_OF(PTR,TYPE,MEMBER)\
        ({const typeof(((TYPE*)0->MEMBER)) *__mptr = (PTR);\
        (TYPE*)((char*)__mptr - PI_ROUTER_OS_VERSION_OFFSETOF(TYPE,MEMBER)};)

#define PI_ROUTER_OS_VERSION_OFFSET_EVERY_ITEM(TYPE)\
        {PI_ROUTER_OS_VERSION_ITEM}

struct _pi_router_os_version{
	char test1;
	int test2;
	float test3[5];
	int test4[5];
	char test[5];
};

void pi_router_os_version_message_pack(char*, struct _pi_router_os_version, char*);
void pi_router_os_version_message_unpack(char*, struct _pi_router_os_version*);


#endif