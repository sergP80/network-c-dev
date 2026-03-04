#pragma once

#include <stdio.h>
#include <math.h>
#include "shared-data.h"
typedef double (*array_op_func_t)(double*);

double array_avg(double* data);
double array_sum(double* data);
double array_min(double* data);
double array_max(double* data);

void print_packet(struct ArrayPacket* packet);

#define COUNT_OPS 4
extern array_op_func_t array_op_funcs[COUNT_OPS];