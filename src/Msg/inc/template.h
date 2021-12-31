#ifndef __TEMPLETE_H__
#define __TEMPLETE_H__

#include <cjson/cJSON.h>
#include <string.h>

#define TEMPLETE_OFFSETOF(TYPE,MEMBER)\
        (size_t)&(((TYPE*)0)->MENBER)

#define TEMPLETE_CONTAINER_OF(PTR,TYPE,MEMBER)\
        ({const typeof(((TYPE*)0->MEMBER)) *__mptr = (PTR);\
        (TYPE*)((char*)__mptr - TEMPLETE_OFFSETOF(TYPE,MEMBER)};)

#define TEMPLETE_OFFSET_EVERY_ITEM(TYPE)\
        {TEMPLETE_ITEM}

struct _templete;

#endif