#ifndef __PI_ROUTER_OS_REQUEST_SYSCALL_H__
#define __PI_ROUTER_OS_REQUEST_SYSCALL_H__

#include <cjson/cJSON.h>
#include <string.h>

#define PI_ROUTER_OS_REQUEST_SYSCALL_OFFSETOF(TYPE,MEMBER)\
        (size_t)&(((TYPE*)0)->MENBER)

#define PI_ROUTER_OS_REQUEST_SYSCALL_CONTAINER_OF(PTR,TYPE,MEMBER)\
        ({const typeof(((TYPE*)0->MEMBER)) *__mptr = (PTR);\
        (TYPE*)((char*)__mptr - PI_ROUTER_OS_REQUEST_SYSCALL_OFFSETOF(TYPE,MEMBER)};)

#define PI_ROUTER_OS_REQUEST_SYSCALL_OFFSET_EVERY_ITEM(TYPE)\
        {PI_ROUTER_OS_REQUEST_SYSCALL_ITEM}

struct _pi_router_os_request_syscall{
	int syscall_number;
	double arg1;
	double arg2;
	double arg3;
	char arg4[50];
	char arg5[50];
	char arg6[50];
};

void pi_router_os_request_syscall_message_pack(char*, struct _pi_router_os_request_syscall, char*);
void pi_router_os_request_syscall_message_unpack(char*, struct _pi_router_os_request_syscall*);


#endif