#ifndef __MAP_H__
#define __MAP_H__
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define INIT_MAP(MAP_NAME, LENGTH) \
            struct _map MAP_NAME = {.length=(LENGTH)};\
            init_map(&MAP_NAME, (LENGTH));

typedef enum {
    ITEM_NOT_COLLISION,
    ITEM_COLLISION
} COLLISION_ITEM_MAP;

typedef enum {
    ITEM_NOT_EXIST,
    ITEM_EXIST
} EXIST_ITEM_MAP;

struct _map_item {
    const char *key;
    int value;
    EXIST_ITEM_MAP exist_item_flag;
};

struct _map {
    int length;
    struct _map_item *_map_item_list;
};

void init_map(struct _map*, int);
COLLISION_ITEM_MAP map_insert(struct _map*, const char*, int);

#endif