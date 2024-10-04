#pragma once

#include <math.h>
#include <tcp-server-mp.h>
#include <shared-data.h>

#define DEFAULT_PORT 7701
#define DEFAULT_QUEUE 20
#define DEFAULT_POOL_SIZE 10

int process_request(P_CLIENT_SESSION_PARAMETER_CONFIG parameter_config);