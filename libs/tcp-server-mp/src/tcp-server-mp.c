#include "tcp-server-mp.h"

SOCKET server_socket = -1;

threadpool th_pool = NULL;

void free_resources()
{
	if (th_pool)
	{
		thpool_wait(th_pool);
		thpool_destroy(th_pool);
	}

	if (server_socket > 0)
	{
		closesocket(server_socket);
	}
}

void usage(const char* exe_name)
{
	printf("Usage:\n");
	printf("\t%s -p <port> -q <que_size> --pool-size", exe_name);
}

int start(int argc, char* argv[], P_SERVER_CONFIG config)
{
	if (argc >= 3)
	{
		char arg_line[128];
		
		memset(arg_line, 0, sizeof(arg_line));

		combine_arg_line(arg_line, argv, 1, argc);

		int ret = sscanf(arg_line, "-p %d -q %d --pool-size %d", &config->port, &config->queue_size, &config->pool_size);

		if (ret < 1) {
			usage(argv[0]);
			return -1;
		}
	}

	return run_server(config);
}

int run_server(P_SERVER_CONFIG config)
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (server_socket <= 0)
	{
		printf("Cannot create socket\n");
		return -1;
	}

	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = htons(config->port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(server_socket, (struct sockaddr*)&address, sizeof(address))) {
		printf("Cannot bind socket to port %d\n", config->port);
		return -2;
	}
	
	if (listen(server_socket, config->queue_size))
	{
		printf("Cannot listen socket on port %d\n", config->port);
		return -3;
	}

	printf("Sever run on port %d\n", config->port);

	return handle_clients(config);
}

int handle_clients(P_SERVER_CONFIG config)
{
	threadpool th_pool = thpool_init(config->pool_size);

	//main loop
	while (1)
	{
		struct sockaddr_in client_addr;

		socklen_t len = sizeof(client_addr);

		SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len);

		if (client_socket <= 0)
		{
			printf("Cannot accept client connection\n");
			continue;
		}

		CLIENT_SESSION_CONFIG session_config = to_session_config(client_socket, config);

		thpool_add_work(th_pool, handle_client, &session_config);
	}

	return 0;
}

void handle_client(void* arg)
{
	P_CLIENT_SESSION_CONFIG client_session_config = (P_CLIENT_SESSION_CONFIG)arg;

	SOCKET client_socket = client_session_config->socket;

	if (client_socket <= 0)
	{
		printf("Error incomming connection\n");
		return;
	}

	server_session_handler_t session_handler = client_session_config->session_handler;

	if (!session_handler)
	{
		printf("Cannot handle client connections\n");
		return;
	}

	stop_session_handler_t stop_session_handler = client_session_config->stop_session_handler;

	struct sockaddr_in client_addr;

	socklen_t len = sizeof(client_addr);

	getsockname(client_socket, (struct sockaddr*)&client_addr, &len);

	printf("Establish connection from: %s\n", inet_ntoa(client_addr.sin_addr));

	CLIENT_SESSION_PARAMETER_CONFIG parameter_config = client_session_config->parameter_config;

	// client loop
	while (!stop_session_handler || !stop_session_handler())
	{
		int ret = recv(client_socket, parameter_config.request, parameter_config.request_size, 0);

		if (ret <= 0)
		{
			printf("Close connection\n");
			break;
		}

		printf("<==== Received: [%d bytes]\n", ret);


		session_handler(&parameter_config);

		ret = send(client_socket, parameter_config.response, parameter_config.response_size, 0);

		if (ret <= 0)
		{
			printf("Close connection\n");
			break;
		}

		printf("====> Sent: [%d bytes]\n", ret);
	}

	closesocket(client_socket);
}

struct ClientSessionConfig to_session_config(SOCKET socket, P_SERVER_CONFIG config)
{
	CLIENT_SESSION_CONFIG client_session_config;

	client_session_config.socket = socket;
	client_session_config.session_handler = config->session_handler;
	client_session_config.stop_session_handler = config->stop_session_handler;
	client_session_config.parameter_config = config->parameter_config;

	return client_session_config;
}