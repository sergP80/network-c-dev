#pragma once

#include <thread-utils.h>
#include <net-utils.h>

extern SOCKET server_socket;

extern threadpool th_pool;

typedef struct ClientSessionParameterConfig {

  char* request;

  int request_size;

  char* response;

  int response_size;

} CLIENT_SESSION_PARAMETER_CONFIG, *P_CLIENT_SESSION_PARAMETER_CONFIG;

typedef int (*server_session_handler_t)(P_CLIENT_SESSION_PARAMETER_CONFIG);

typedef int (*stop_session_handler_t)();

typedef struct ServerConfig {
  short port;

  int queue_size;

  int pool_size;

  server_session_handler_t session_handler;

  stop_session_handler_t stop_session_handler;

  struct ClientSessionParameterConfig parameter_config;

} SERVER_CONFIG, *P_SERVER_CONFIG;

typedef struct ClientSessionConfig {
  SOCKET socket;

  server_session_handler_t session_handler;

  stop_session_handler_t stop_session_handler;

  struct ClientSessionParameterConfig parameter_config;

} CLIENT_SESSION_CONFIG, *P_CLIENT_SESSION_CONFIG;


void free_resources();

int start(int argc, char* argv[], P_SERVER_CONFIG config);

void usage(const char* exe_name);

int run_server(P_SERVER_CONFIG config);

int handle_clients(P_SERVER_CONFIG config);

void handle_client(void*);

struct ClientSessionConfig to_session_config(SOCKET socket, P_SERVER_CONFIG config);