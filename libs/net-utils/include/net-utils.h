#pragma once

#include "stdio.h"
#include "string.h"

#ifdef _WIN32

#include <tchar.h>
#include <winsock2.h>
#include <windows.h>

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

int combine_arg_line(char* dest, const char* argv[], int start, int count);

SOCKET create_tcp_socket();

SOCKET create_udp_socket();

void close_socket(SOCKET);