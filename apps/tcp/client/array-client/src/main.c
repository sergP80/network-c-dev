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
	struct ArrayPacket request = {SUM, {1.2, 3.5, 7.4, -1.4, NAN}};

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
	printf("Result of %d=%.3f\n", response->operation, response->data[0]);
	return 0;
}
