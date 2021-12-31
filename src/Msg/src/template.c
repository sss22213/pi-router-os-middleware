#include "templete.h"

void _message_pack(char *topic, struct _templete type, char *ret_string)
{
    cJSON *new_msg = cJSON_CreateObject();

    cJSON *topic_name = NULL;

    cJSON *type_name = NULL;

DECLARE_SCECTION

CREATE_TOPIC_NAME_FILED_SCECTION

CREATE_TYPE_SCECTION

ADD_TOPIC_NAME_SECTION

    strcpy(ret_string, cJSON_Print(new_msg));
    cJSON_Delete(new_msg);
}

void _message_unpack(char *source, struct _templete *ret)
{
    cJSON *new_msg = cJSON_Parse(source);

DECLARE_SCECTION

UNPACK_PACKAGE
}