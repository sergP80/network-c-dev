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

double array_min(double* data)
{
    int n = 0;
    
    double min = NAN;
    
    for (; !isnan(data[n]); ++n)
    {
        if (isnan(min)) 
        {
            min = data[n];
        } else
        {
            if (data[n] < min)
            {
                min = data[n];
            }
        }
    }

    return min;
}

double array_max(double* data)
{
    int n = 0;
    
    double max = NAN;
    
    for (; !isnan(data[n]); ++n)
    {
        if (isnan(max)) 
        {
            max = data[n];
        } else
        {
            if (data[n] > max)
            {
                max = data[n];
            }
        }
    }

    return max;
}

void print_packet(struct ArrayPacket* packet)
{
    if (!packet)
    {
        return;
    }

    printf("Requested operation: %d\n", packet->operation);
    
    int n = 0;
    for(;isnan(packet->data[n]); ++n)
    {
        printf("%d\t", packet->data[n]);
    }
    printf("\n");
}

array_op_func_t array_op_funcs[COUNT_OPS] = {array_avg, array_sum, array_min, array_max};