#include "net-utils.h"

int init()
{
#ifdef __WIN32__
	WSADATA ws;

	return WSAStartup(MAKEWORD(2, 2), &ws);
#else
    return 0;
#endif
}

void cleanup()
{
#ifdef __WIN32__
    if (WSACleanup())
    {
        printf("Error cleanup WinSock2\n");
    }
#endif
}

int resolve_address(const char* name, char* dest)
{
    struct hostent* he = gethostbyname(name);

    if (he == NULL)
    {
        return -5;
    }

    struct in_addr** addr_list = (struct in_addr**)he->h_addr_list;

    if (addr_list[0] != 0)
    {
        strcpy(dest, inet_ntoa(*addr_list[0]));
        return 0;
    }

    return -6;
}

int combine_arg_line(char* dest, char* argv[], int start, int count)
{
    for (int i = start; i < count; ++i)
    {
        strcat(dest, argv[i]);

        if (i < count - 1)
        {
            strcat(dest, " ");
        }
    }

    return 0;
}

#ifndef __WIN32__
int closesocket(SOCKET socket)
{
    return close(socket);
}
#endif
