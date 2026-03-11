#include "app.h"

void exit_handler();

SOCKET receiver_socket;

int main(int argc, char *argv[]) {	
    atexit(cleanup);
	atexit(exit_handler);

    short port = DEFAULT_PORT;
    char host[128] = "";

	int ret_opts = get_connection_cli(argc, argv, host, &port);

	if (ret_opts < 2)
	{
		printf("Enter end-point in format -h <host> -p <port>:");

		if (scanf("-h %s -p %d", host, &port) < 2)
		{
			printf("Error input\n");
			return -1;
		}

		getc(stdin);
	}

    init();

    receiver_socket = create_udp_socket();

	if (receiver_socket <= 0) {
        printf("Can't create socket");
        return -1;
    }

    struct sockaddr_in receiver_addr = create_endpoint(host, port);

	//Bind socket to the address on the server
	if (bind(receiver_socket, (struct sockaddr *)&receiver_addr, sizeof(struct sockaddr))) {
		printf("Can't bind socket to the port %d", port);
		return -1;
	}

    printf("Receiver available on the port %d\n", port);

    while (process_receiv_data(receiver_socket)) {}

    return 0;
}

void exit_handler() {
    close_socket(receiver_socket);
}