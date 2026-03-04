#include "main.h"

void usage(const char* exe_name)
{
	printf("Usage:\n");
	printf("\t%s -h <host> -p <port>\n", exe_name);
}

int start(int argc, char* argv[])
{
	char host[2048] = "";

	int port;

	if (argc >= 3)
	{
		char arg_line[4 * 1024] = "";
		
		combine_arg_line(arg_line, argv, 1, argc);

		int ret = sscanf(arg_line, "-h %s -p %d", host, &port);
		
		if (ret < 2) {
			usage(argv[0]);
			return -1;
		}
	}
	else {
		printf("Enter server address (-h <host> -p <port>): ");

		int ret = scanf("-h %s -p %d", host, &port);

		if (ret < 2)
		{
			usage(argv[0]);

			return -2;
		}
	}

	return init_client(host, port);
}

int init_client(const char* host, short port)
{
	SOCKET client_socket = create_tcp_socket();
	
	if (client_socket <= 0)
	{
		printf("Cannot create client socket\n");
		return -1;
	}

	printf("Socket created\n");

	struct sockaddr_in server_address = create_endpoint(host, port);
	
	if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) {
		printf("Cannot connect to port %s:%d\n", host, port);
		return -2;
	}

	printf("Success connection to server: %s:%d\n", host, port);

	return process_connection(client_socket);
}

int process_connection(SOCKET client_socket)
{
	struct ArrayPacket request = {};

	enum ArrayOp operation = select_operation();

	request.operation = operation;

	int size = 0;

	user_receive_array(request.data, &size);

	printf("You've wanted to send %d items to server with op %d\n", size, operation);

	int ret = send(client_socket, (char*)&request, sizeof(request), 0);

	if (ret <= 0)
	{
		printf("Sending data error\n");
		return -11;
	}

	printf("====> Sent: [%d bytes]\n", ret);
	
	struct ArrayResult response;

	ret = recv(client_socket, (char*)&response, sizeof(response), 0);

	printf("<==== Received echo: [%d bytes]\n", ret);

	process_request(&request, &response);

	close_socket(client_socket);
	return 0; 
}

int process_request(struct ArrayPacket* request, struct ArrayResult* response)
{
	if (strlen(response->error_message))
	{
		printf("Error: %s\n", response->error_message);
	}
	else
	{
		printf("Result of %d=%.3f\n", response->operation, response->data[0]);
	}
	return 0;
}


enum ArrayOp select_operation()
{
	
	printf("1 - AVG\n");
	printf("2 - SUM\n");
	printf("3 - MAX\n");
	printf("4 - MIN\n");
	printf("5 - MAX_MIN\n");
	printf("Select operation: ");

	enum ArrayOp op;
	
	int ret = scanf("%d", &op);

	if (ret < 1)
	{
		printf("Error operation\n");
	}

	printf("You selected %d\n", op);

	return op;
}

void user_receive_array(double* dest, int* size)
{
	*size = 0;
	for(;;)
	{
		
		printf("Type array item:");

		double item;

		int ret = scanf("%lf", &item);

		if (ret < 1)
		{
			break;
		}

		dest[(*size)++] = item;
	}

	if (*size > 0)
	{
		dest[*size] = NAN;
	}
}
