#pragma once

#include <stdlib.h>
#include "common-utils.h"
#include "net-utils.h"
#ifdef _WIN32
#include "ws2tcpip.h"
#endif

#define MCASTADDR "234.5.6.7"
#define MCASTPORT 25
#define BUFSIZE 255
#define DEFAULT_COUNT 50

typedef struct tagGroupOptions{
    long ip_interface;
    long group_ip_interface;
    short group_port;
    long repeat_count;
    int is_sender;
    int is_receiver;
    int is_loop_back;
} MULTICAST_GROUP_OPTION, *PMULTICAST_GROUP_OPTION;


void parse_cmd_line(int argc, char **argv, PMULTICAST_GROUP_OPTION opts);