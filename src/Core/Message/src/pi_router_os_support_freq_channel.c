#include "pi_router_os_support_freq_channel.h"

void pi_router_os_support_freq_channel_message_pack(char *topic, struct _pi_router_os_support_freq_channel type, char *ret_string)
{
    cJSON *new_msg = cJSON_CreateObject();

    cJSON *topic_name = NULL;

    cJSON *type_name = NULL;

	cJSON *freq_json = NULL;
	cJSON *channel_json = NULL;




	type_name = cJSON_CreateString("PI_ROUTER_OS_SUPPORT_FREQ_CHANNEL");
	cJSON_AddItemToObject(new_msg, "type_name", type_name);



	cJSON *freq_ary = cJSON_CreateArray();
	cJSON_AddItemToObject(new_msg, "freq", freq_ary);
	for (int idx = 0; idx < 50; idx++) {
		freq_json = cJSON_CreateNumber(type.freq[idx]);
		cJSON_AddItemToArray(freq_ary, freq_json);
	}

	cJSON *channel_ary = cJSON_CreateArray();
	cJSON_AddItemToObject(new_msg, "channel", channel_ary);
	for (int idx = 0; idx < 50; idx++) {
		channel_json = cJSON_CreateNumber(type.channel[idx]);
		cJSON_AddItemToArray(channel_ary, channel_json);
	}


    strcpy(ret_string, cJSON_Print(new_msg));
    cJSON_Delete(new_msg);
}

void pi_router_os_support_freq_channel_message_unpack(char *source, struct _pi_router_os_support_freq_channel *ret)
{
    cJSON *new_msg = cJSON_Parse(source);

	cJSON *freq_json = NULL;
	cJSON *channel_json = NULL;


	int idx = 0;

	cJSON *freq_json_ary = cJSON_GetObjectItemCaseSensitive(new_msg, "freq");
	idx = 0;
	cJSON_ArrayForEach(freq_json, freq_json_ary) {
		ret->freq[idx] = freq_json->valuedouble;
		idx++;
	}

	cJSON *channel_json_ary = cJSON_GetObjectItemCaseSensitive(new_msg, "channel");
	idx = 0;
	cJSON_ArrayForEach(channel_json, channel_json_ary) {
		ret->channel[idx] = channel_json->valuedouble;
		idx++;
	}


}