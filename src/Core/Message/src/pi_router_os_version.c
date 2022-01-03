#include "pi_router_os_version.h"

void pi_router_os_version_message_pack(char *topic, struct _pi_router_os_version type, char *ret_string)
{
    cJSON *new_msg = cJSON_CreateObject();

    cJSON *topic_name = NULL;

    cJSON *type_name = NULL;

	cJSON *test1_json = NULL;
	cJSON *test2_json = NULL;
	cJSON *test3_json = NULL;
	cJSON *test4_json = NULL;
	cJSON *test_json = NULL;




	type_name = cJSON_CreateString("PI_ROUTER_OS_VERSION");
	cJSON_AddItemToObject(new_msg, "type_name", type_name);


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

	cJSON *test1_json = NULL;
	cJSON *test2_json = NULL;
	cJSON *test3_json = NULL;
	cJSON *test4_json = NULL;
	cJSON *test_json = NULL;


	int idx = 0;

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