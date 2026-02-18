#include "array-process.h"

double array_avg(double* data)
{
    double s = 0.0;
    int n = 0;

    for (; !isnan(data[n]); ++n)
    {
        s += data[n];
    }

    return s/n;
}

double array_sum(double* data)
{
    double s = 0.0;
    int n = 0;

    for (; !isnan(data[n]); ++n)
    {
        s += data[n];
    }

    return s;
}

array_op_func_t array_op_funcs[COUNT_OPS] = {array_avg, array_sum};