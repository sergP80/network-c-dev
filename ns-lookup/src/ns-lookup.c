#include "ns-lookup.h"

int init()
{
	WSADATA ws;

	return WSAStartup(MAKEWORD(2, 2), &ws);
}

void cleanup()
{
	if (WSACleanup())
	{
		printf("Error cleanup WinSock2\n");
		return -2;
	}
}

int start(int argc, char** argv)
{
	char name[256];

	memset(name, 0, sizeof(name));

	if (argc >= 2)
	{
		strcpy(name, argv[1]);
	}
	else
	{
		printf("Enter dns name:");
		int ret = scanf("%s", name);
		if (ret < 1)
		{
			return -3;
		}
	}

	return resolve_dns(name);
}

int resolve_dns(const char* name)
{
	struct hostent* he = gethostbyname(name);

	if (he == NULL)
	{
		return -5;
	}

	printf("Resolved: %s\n", he->h_name);

	printf("IPv4 addres list\n");

	for (char** pa = he->h_addr_list; pa != NULL; ++pa)
	{
		char ip[64] = "";

		resolve_ip(*pa, ip, he->h_length);

		printf("\t%s\n", ip);		
	}

	return 0;

}

char* resolve_ip(const char* src, char* dst, const int len)
{
	struct in_addr addr;

	memcpy(&addr, src, len);

	strcpy(dst, inet_ntoa(addr));

	return dst;
}