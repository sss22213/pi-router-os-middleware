#include "pi_router_os_version.h"

void pi_router_os_version_message_pack(char *topic, struct _pi_router_os_version type, char *ret_string)
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
	cJSON *test1_json = NULL;
	cJSON *test2_json = NULL;
	cJSON *test3_json = NULL;
	cJSON *test4_json = NULL;
	cJSON *test_json = NULL;




	type_name = cJSON_CreateString("PI_ROUTER_OS_VERSION");
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
	test1_json = cJSON_CreateNumber(type.test1);
	cJSON_AddItemToObject(new_msg, "test1", test1_json);
	test2_json = cJSON_CreateNumber(type.test2);
	cJSON_AddItemToObject(new_msg, "test2", test2_json);

	cJSON *test3_ary = cJSON_CreateArray();
	cJSON_AddItemToObject(new_msg, "test3", test3_ary);
	for (int idx = 0; idx < 5; idx++) {
		test3_json = cJSON_CreateNumber(type.test3[idx]);
		cJSON_AddItemToArray(test3_ary, test3_json);
	}

	cJSON *test4_ary = cJSON_CreateArray();
	cJSON_AddItemToObject(new_msg, "test4", test4_ary);
	for (int idx = 0; idx < 5; idx++) {
		test4_json = cJSON_CreateNumber(type.test4[idx]);
		cJSON_AddItemToArray(test4_ary, test4_json);
	}
	test_json = cJSON_CreateString(type.test);
	cJSON_AddItemToObject(new_msg, "test", test_json);


    strcpy(ret_string, cJSON_Print(new_msg));
    cJSON_Delete(new_msg);
}

void pi_router_os_version_message_unpack(char *source, struct _pi_router_os_version *ret)
{
    cJSON *new_msg = cJSON_Parse(source);

	cJSON *syscall_number_json = NULL;
	cJSON *arg1_json = NULL;
	cJSON *arg2_json = NULL;
	cJSON *arg3_json = NULL;
	cJSON *arg4_json = NULL;
	cJSON *arg5_json = NULL;
	cJSON *arg6_json = NULL;
	cJSON *test1_json = NULL;
	cJSON *test2_json = NULL;
	cJSON *test3_json = NULL;
	cJSON *test4_json = NULL;
	cJSON *test_json = NULL;


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
	test1_json = cJSON_GetObjectItemCaseSensitive(new_msg, "test1");
	if(!cJSON_IsString(test1_json)) {
		ret->test1 = test1_json->valuedouble;
	}
	test2_json = cJSON_GetObjectItemCaseSensitive(new_msg, "test2");
	if(!cJSON_IsString(test2_json)) {
		ret->test2 = test2_json->valuedouble;
	}
	cJSON *test3_json_ary = cJSON_GetObjectItemCaseSensitive(new_msg, "test3");
	idx = 0;
	cJSON_ArrayForEach(test3_json, test3_json_ary) {
		ret->test3[idx] = test3_json->valuedouble;
		idx++;
	}

	cJSON *test4_json_ary = cJSON_GetObjectItemCaseSensitive(new_msg, "test4");
	idx = 0;
	cJSON_ArrayForEach(test4_json, test4_json_ary) {
		ret->test4[idx] = test4_json->valuedouble;
		idx++;
	}

	test_json = cJSON_GetObjectItemCaseSensitive(new_msg, "test");
	strcpy(ret->test, test_json->valuestring);

}