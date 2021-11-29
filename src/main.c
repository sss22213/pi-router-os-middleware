#include <stdio.h>
#include <pthread.h>
#include "list.h"
#include "queue.h"
#include "tree.h"
#include "map.h"
#include "wireless.h"
#include "console.h"
#include "transfer_socket.h"

/**
 * @brief Main function
 * 
 * usage: ./main [option] -i [interface number]
 * [option]:
 *      avail_channel
 *      avail_freq
 *      cur_channel
 *      cur_freq
 *      cur_bitrate
 *      cur_txpower
 *      
 * @param argc 
 * @param argv
 * @return int
 */

int main(int argc, char **argv)
{
    struct _console console;
    console_excute_array(&console, argc, argv);
    
    /*
    struct _console console;
    uint8_t a[] = "Avail_freq";
    insert_console(&console, a);
    */
    /*
    INIT_MAP(new_map, 20);

    map_insert(&new_map, "avail_channel", 0);
    map_insert(&new_map, "avail_freq", 0);
    */

    //char str[] = "avail_channel -i 2";
    //console_read(str);
    // Initialize socket
    //INIT_TRANSFER_SOCKET(new_socket, 8232);

    //while(1);

    //struct _wireless_iface_iwlist_node *new_wireless_node = _find_support_freq_channel(2);
    /*
    struct _node *ptr_node = NULL;
    QUEUE_FOR_EACH(ptr_node, &new_wireless_node->ptr_support_channel_freq) {
        printf("%d\n", CONTAINER_OF(ptr_node, struct _channel_freq, iface_node)->channel);
        printf("%e\n", CONTAINER_OF(ptr_node, struct _channel_freq, iface_node)->freq);
    }
    */

    return 0;
}