#include "pi_router_os_support_action_iface.h"

void pi_router_os_support_action_iface_message_pack(char *topic, struct _pi_router_os_support_action_iface type, char *ret_string)
{
    cJSON *new_msg = cJSON_CreateObject();

    cJSON *topic_name = NULL;

    cJSON *type_name = NULL;

	cJSON *iface_json = NULL;
	cJSON *ip_addr_json = NULL;
	cJSON *broadcast_json = NULL;
	cJSON *hwaddr_json = NULL;
	cJSON *mask_json = NULL;




	type_name = cJSON_CreateString("PI_ROUTER_OS_SUPPORT_ACTION_IFACE");
	cJSON_AddItemToObject(new_msg, "type_name", type_name);


	iface_json = cJSON_CreateNumber(type.iface);
	cJSON_AddItemToObject(new_msg, "iface", iface_json);
	ip_addr_json = cJSON_CreateString(type.ip_addr);
	cJSON_AddItemToObject(new_msg, "ip_addr", ip_addr_json);
	broadcast_json = cJSON_CreateString(type.broadcast);
	cJSON_AddItemToObject(new_msg, "broadcast", broadcast_json);
	hwaddr_json = cJSON_CreateString(type.hwaddr);
	cJSON_AddItemToObject(new_msg, "hwaddr", hwaddr_json);
	mask_json = cJSON_CreateNumber(type.mask);
	cJSON_AddItemToObject(new_msg, "mask", mask_json);


    strcpy(ret_string, cJSON_Print(new_msg));
    cJSON_Delete(new_msg);
}

void pi_router_os_support_action_iface_message_unpack(char *source, struct _pi_router_os_support_action_iface *ret)
{
    cJSON *new_msg = cJSON_Parse(source);

	cJSON *iface_json = NULL;
	cJSON *ip_addr_json = NULL;
	cJSON *broadcast_json = NULL;
	cJSON *hwaddr_json = NULL;
	cJSON *mask_json = NULL;


	int idx = 0;

	iface_json = cJSON_GetObjectItemCaseSensitive(new_msg, "iface");
	if(!cJSON_IsString(iface_json)) {
		ret->iface = iface_json->valuedouble;
	}
	ip_addr_json = cJSON_GetObjectItemCaseSensitive(new_msg, "ip_addr");
	strcpy(ret->ip_addr, ip_addr_json->valuestring);
	broadcast_json = cJSON_GetObjectItemCaseSensitive(new_msg, "broadcast");
	strcpy(ret->broadcast, broadcast_json->valuestring);
	hwaddr_json = cJSON_GetObjectItemCaseSensitive(new_msg, "hwaddr");
	strcpy(ret->hwaddr, hwaddr_json->valuestring);
	mask_json = cJSON_GetObjectItemCaseSensitive(new_msg, "mask");
	if(!cJSON_IsString(mask_json)) {
		ret->mask = mask_json->valuedouble;
	}

}