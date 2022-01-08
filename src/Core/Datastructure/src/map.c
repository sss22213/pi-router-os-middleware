#include "map.h"
#define A_HASH_CONST    0.61

// Multiplication hash method
static inline uint32_t _to_hash_function(struct _map *map, const char *key)
{
    float alphabet_number = 0;
    float f = 0;
    uint32_t hash = 0;

    for (const char *ptr_key = key; (*ptr_key)!='\0'; ptr_key++) {
        alphabet_number += (float)(uint8_t)*ptr_key;
    }

    f = alphabet_number*A_HASH_CONST - ((int)(alphabet_number*A_HASH_CONST));

    hash = map->length * f;

    return hash;
}

static inline COLLISION_ITEM_MAP _insert(struct _map *map, const char *key, int value)
{
    uint32_t hash_key = _to_hash_function(map, key);
    if (map->_map_item_list[hash_key].exist_item_flag == ITEM_EXIST) {
        return ITEM_COLLISION;
    }

    map->_map_item_list[hash_key].value = value;
    map->_map_item_list[hash_key].key = key;
    map->_map_item_list[hash_key].exist_item_flag = ITEM_EXIST;

    return ITEM_NOT_COLLISION;

}

static inline void _remove(struct _map *map, const char *key)
{
    uint32_t hash_key = _to_hash_function(map, key);
    map->_map_item_list[hash_key].value = 0;
    map->_map_item_list[hash_key].key = 0;
    map->_map_item_list[hash_key].exist_item_flag = ITEM_NOT_EXIST;
}

COLLISION_ITEM_MAP insert_map(struct _map *map, const char *key, int value)
{
    return _insert(map, key, value);
}

void init_map(struct _map *map, int length)
{
    map->_map_item_list = (struct _map_item*)calloc(length, sizeof(struct _map_item));

    // Put empty flag into all of item container.
    for (int map_item_idx = 0; map_item_idx < length; map_item_idx++) {
        map->_map_item_list[map_item_idx].exist_item_flag = ITEM_NOT_EXIST;
    }
}

void Deinit_map(struct _map *map)
{
    free(map->_map_item_list);
}

struct _map_item find_item_map(struct _map *map, int key)
{
    uint32_t hash_key = _to_hash_function(map, key);
    return map->_map_item_list[hash_key];
}