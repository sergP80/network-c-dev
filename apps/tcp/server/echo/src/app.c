﻿#include "echo.h"

int main(int argc, char* argv[])
{
	atexit(free_resources);

	atexit(cleanup);
	
	if (init())
	{
		printf("Error init networking\n");
		return -1;
	}

	if (start(argc, argv))
	{
		printf("Cannot start server\n");
		return -2;
	}

	return 0;
}
