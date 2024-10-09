#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef _WIN32 || _WIN32_ || __WIN32__

#include "winsock2.h"

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#endif
int init();

void cleanup();

int resolve_address(const char* src, char* dest);

int combine_arg_line(char* dest, char* argv[], int start, int count);

#ifdef _WIN32 || _WIN32_ || __WIN32__
#else
typedef int SOCKET;

int closesocket(SOCKET socket);
#endif

#ifdef _WIN32 || _WIN32_ || __WIN32__
typedef int socklen_t;
#endif