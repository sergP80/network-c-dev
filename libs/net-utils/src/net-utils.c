#include "net-utils.h"

#include "string.h"

int init()
{
	#ifdef _WIN32
	WSADATA ws;

	return WSAStartup(MAKEWORD(2, 2), &ws);
	#else
	return 0;
	#endif
}

void cleanup()
{
	#ifdef _WIN32
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

	if (addr_list[0] != 0) {
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

SOCKET create_tcp_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

SOCKET create_udp_socket()
{
    return socket(AF_INET, SOCK_DGRAM, 0);
}


void close_socket(SOCKET s)
{
	#ifdef _WIN32
	closesocket(s);
	#elif __linux__ || __APPLE__
	close(s);
	#endif 
}

struct sockaddr_in create_endpoint(const char *host, short port)
{
	struct sockaddr_in saddr;

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	
	
	if (!host || strlen(host) == 0)
	{
		saddr.sin_addr.s_addr = htonl(INADDR_ANY);;
	} else 
	{
		char target_host[2048] = "";
		
		resolve_address(host, target_host);

		saddr.sin_addr.s_addr = inet_addr(target_host);
	}

    return saddr;
}
