#pragma once

#ifdef _WIN32

#include <windows.h>

typedef DWORD ERROR_CODE_TYPE;

#define ERROR_TIMEOUT WSAETIMEDOUT

#elif __linux__ || __APPLE__

#include <errno.h>
#include <time.h>
#include <unistd.h>

typedef int ERROR_CODE_TYPE;

#define ERROR_TIMEOUT ETIMEDOUT

#else
#error "Unsupported platform"
#endif

unsigned long get_tick_count();

ERROR_CODE_TYPE get_last_error();

int current_thread_sleep(unsigned int millis);

#define CHECK_IO(io, err_code, ...) \
if (!(io)) \
{ \
printf(__VA_ARGS__); \
return err_code; \
}

#define CHECK_SET_OPT(opt_ret, err_msg)\
{\
if ((opt_ret) < 0)\
{\
printf("setsockopt(%s) failed with: %d\n",\
err_msg, get_last_error());\
return -1;\
}\
}