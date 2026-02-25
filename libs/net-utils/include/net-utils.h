#pragma once

#include "stdio.h"
#include "string.h"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <tchar.h>

#elif __linux__ || __APPLE__

#include<netinet/ip.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

typedef int SOCKET;

#endif

int init();

void cleanup();

int resolve_address(const char* src, char* dest);

int combine_arg_line(char* dest, char* argv[], int start, int count);

SOCKET create_tcp_socket();

SOCKET create_udp_socket();

void close_socket(SOCKET);

/**
 * Create sock addr structure with the host and port converted into BE order
*/
struct sockaddr_in create_endpoint(const char* host, short port);