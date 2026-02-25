#pragma once

#include "stdio.h"
#include "string.h"
#include "math.h"
#include "thread_pool.h"
#include "net-utils.h"
#include "shared-data.h"
#include "array-process.h"

#define DEFAULT_PORT 7701
#define DEFAULT_QUEUE 20

extern SOCKET server_socket;

extern threadpool* p_thrd_pool;

void free_pool();

void free_socket();

int start(int argc, char* argv[]);

void usage(const char* exe_name);

threadpool* init_thread_pool(int size);

int init_server(short port, int queue_size);

int process_connections();

void process_connection(void*);

int process_request(struct ArrayPacket* request, struct ArrayResult* response);