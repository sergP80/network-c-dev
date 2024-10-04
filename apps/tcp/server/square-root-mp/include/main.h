#pragma once

#include <math.h>
#include <thread-utils.h>
#include <net-utils.h>
#include <shared-data.h>

#define DEFAULT_PORT 7701
#define DEFAULT_QUEUE 20
#define DEFAULT_POOL_SIZE 10

extern SOCKET server_socket;

extern threadpool th_pool;

void free_resources();

int start(int argc, char* argv[]);

void usage(const char* exe_name);

int init_server(short port, int queue_size, int pool_size);

int process_connections(int pool_size);

void process_connection(void*);

int process_request(struct QuadraticEquation* request, struct SquareRootData* response);