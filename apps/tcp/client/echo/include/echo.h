﻿#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "net-utils.h"

int start(int argc, char* argv[]);

void usage(const char* exe_name);

int init_client(const char* host, short port);

int process_connection(SOCKET client_socket);