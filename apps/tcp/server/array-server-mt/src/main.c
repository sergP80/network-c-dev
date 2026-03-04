#include "main.h"

SOCKET server_socket = -1;

threadpool* p_thrd_pool = NULL;

void free_pool()
{
	if (p_thrd_pool)
	{
		threadpool_destroy(p_thrd_pool);
	}
}

void free_socket()
{
	if (server_socket > 0)
	{
		close_socket(server_socket);
	}
}
void usage(const char* exe_name)
{
	printf("Usage:\n");
	printf("\t%s -p <port> -q <que_size>", exe_name);
}

int start(int argc, char* argv[])
{
	int port = DEFAULT_PORT;

	int queue_size = DEFAULT_QUEUE;

	if (argc >= 3)
	{
		char arg_line[128];
		
		memset(arg_line, 0, sizeof(arg_line));

		combine_arg_line(arg_line, argv, 1, argc);

		int ret = sscanf(arg_line, "-p %d -q %d", &port, &queue_size);

		if (ret < 1) {
			usage(argv[0]);
			return -1;
		}
	}

	return init_server(port, queue_size);
}

int init_server(short port, int queue_size)
{
	server_socket = create_tcp_socket();
	
	if (server_socket <= 0)
	{
		printf("Cannot create socket\n");
		return -1;
	}

	struct sockaddr_in address = create_endpoint(NULL, port);

	if (bind(server_socket, (struct sockaddr*)&address, sizeof(address))) {
		printf("Cannot bind socket to port %d\n", port);
		return -2;
	}
	
	if (listen(server_socket, queue_size))
	{
		printf("Cannot listen socket on port %d\n", port);
		return -3;
	}

	printf("Sever run on port %d\n", port);

	return process_connections();
}

threadpool* init_thread_pool(int size)
{
	p_thrd_pool = threadpool_create(size);
    return p_thrd_pool;
}

int process_connections()
{
	SOCKET client_socket = -1;

	//main loop
	while (1)
	{
		struct sockaddr_in client_addr;

		int len = sizeof(client_addr);

		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len);

		threadpool_add_task(p_thrd_pool, process_connection, (SOCKET*)client_socket);
	}

	return 0;
}

void process_connection(void* arg)
{
	SOCKET client_socket = (SOCKET)arg;

	if (client_socket <= 0)
	{
		printf("Error incomming connection\n");
		return;
	}

	struct sockaddr_in client_addr;

	int len = sizeof(client_addr);

	getsockname(client_socket, (struct sockaddr*)&client_addr, &len);

	printf("Establish connection from: %s\n", inet_ntoa(client_addr.sin_addr));

	// client loop
	while (1)
	{
		struct ArrayPacket request;

		int ret = recv(client_socket, (char*)&request, sizeof(request), 0);

		if (ret <= 0)
		{
			printf("Close connection\n");
			return;
		}

		printf("<==== Received: [%d bytes]\n", ret);

		printf("Requested data===\n");
		print_packet(&request);
		printf("=================\n");
		struct ArrayResult response;

		process_request(&request, &response);

		ret = send(client_socket, (char*)&response, sizeof(response), 0);

		if (ret <= 0)
		{
			printf("Close connection\n");
			return;
		}

		printf("====> Sent: [%d bytes]\n", ret);
	}

	if (client_socket > 0)
	{
		close_socket(client_socket);
	}
}

int process_request(struct ArrayPacket* request, struct ArrayResult* response)
{
	enum ArrayOp op = request->operation;

	int id = op - 1;
	
	if (id < 0 || id >= COUNT_OPS)
	{
		printf("Unsupported operation %d\n", id);
		strcpy(response->error_message, "Unsupported operation");
	} else {
		memset(response->error_message, 0, sizeof(response->error_message));
	}

	array_op_func_t f = array_op_funcs[op - 1];
	
	double result = f(request->data);

	response->operation = op;

	response->data[0] = result;
	
	response->result_count = 1;

	return 0;
}
