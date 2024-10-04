#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "net-utils.h"


int start(int argc, char* argv[]);

int resolve_dns(const char* name);