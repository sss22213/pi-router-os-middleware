#include "pi_router_os_request_syscall.h"

void pi_router_os_request_syscall_message_pack(char *topic, struct _pi_router_os_request_syscall type, char *ret_string)
{
    cJSON *new_msg = cJSON_CreateObject();

    cJSON *topic_name = NULL;

    cJSON *type_name = NULL;

	cJSON *syscall_number_json = NULL;
	cJSON *arg1_json = NULL;
	cJSON *arg2_json = NULL;
	cJSON *arg3_json = NULL;
	cJSON *arg4_json = NULL;
	cJSON *arg5_json = NULL;
	cJSON *arg6_json = NULL;




	type_name = cJSON_CreateString("PI_ROUTER_OS_REQUEST_SYSCALL");
	cJSON_AddItemToObject(new_msg, "type_name", type_name);


	syscall_number_json = cJSON_CreateNumber(type.syscall_number);
	cJSON_AddItemToObject(new_msg, "syscall_number", syscall_number_json);
	arg1_json = cJSON_CreateNumber(type.arg1);
	cJSON_AddItemToObject(new_msg, "arg1", arg1_json);
	arg2_json = cJSON_CreateNumber(type.arg2);
	cJSON_AddItemToObject(new_msg, "arg2", arg2_json);
	arg3_json = cJSON_CreateNumber(type.arg3);
	cJSON_AddItemToObject(new_msg, "arg3", arg3_json);
	arg4_json = cJSON_CreateString(type.arg4);
	cJSON_AddItemToObject(new_msg, "arg4", arg4_json);
	arg5_json = cJSON_CreateString(type.arg5);
	cJSON_AddItemToObject(new_msg, "arg5", arg5_json);
	arg6_json = cJSON_CreateString(type.arg6);
	cJSON_AddItemToObject(new_msg, "arg6", arg6_json);


    strcpy(ret_string, cJSON_Print(new_msg));
    cJSON_Delete(new_msg);
}

void pi_router_os_request_syscall_message_unpack(char *source, struct _pi_router_os_request_syscall *ret)
{
    cJSON *new_msg = cJSON_Parse(source);

	cJSON *syscall_number_json = NULL;
	cJSON *arg1_json = NULL;
	cJSON *arg2_json = NULL;
	cJSON *arg3_json = NULL;
	cJSON *arg4_json = NULL;
	cJSON *arg5_json = NULL;
	cJSON *arg6_json = NULL;


	int idx = 0;

	syscall_number_json = cJSON_GetObjectItemCaseSensitive(new_msg, "syscall_number");
	if(!cJSON_IsString(syscall_number_json)) {
		ret->syscall_number = syscall_number_json->valuedouble;
	}
	arg1_json = cJSON_GetObjectItemCaseSensitive(new_msg, "arg1");
	if(!cJSON_IsString(arg1_json)) {
		ret->arg1 = arg1_json->valuedouble;
	}
	arg2_json = cJSON_GetObjectItemCaseSensitive(new_msg, "arg2");
	if(!cJSON_IsString(arg2_json)) {
		ret->arg2 = arg2_json->valuedouble;
	}
	arg3_json = cJSON_GetObjectItemCaseSensitive(new_msg, "arg3");
	if(!cJSON_IsString(arg3_json)) {
		ret->arg3 = arg3_json->valuedouble;
	}
	arg4_json = cJSON_GetObjectItemCaseSensitive(new_msg, "arg4");
	strcpy(ret->arg4, arg4_json->valuestring);
	arg5_json = cJSON_GetObjectItemCaseSensitive(new_msg, "arg5");
	strcpy(ret->arg5, arg5_json->valuestring);
	arg6_json = cJSON_GetObjectItemCaseSensitive(new_msg, "arg6");
	strcpy(ret->arg6, arg6_json->valuestring);

}