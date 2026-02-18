#pragma once

#include "math.h"

typedef double (*array_op_func_t)(double*);

double array_avg(double* data);
double array_sum(double* data);

#define COUNT_OPS 2
extern array_op_func_t array_op_funcs[COUNT_OPS];