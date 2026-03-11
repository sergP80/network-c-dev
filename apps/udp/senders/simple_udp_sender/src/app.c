#include "app.h"

void exit_handler();

SOCKET client_socket;

int main(int argc, char* argv[])
{
    atexit(cleanup);
    atexit(exit_handler);

    short port;
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

    client_socket = create_udp_socket();

    if (client_socket <= 0)
    {
        printf("Can't create socket");
        return -1;
    }

    struct sockaddr_in receiver_addr = create_endpoint(host, port);

    char msg[256] = "";
    printf("%s", "Enter msg:");
    scanf("%[^\n]s", msg);
    int sc = sendto(client_socket, msg, sizeof(msg), 0, (struct sockaddr*)&receiver_addr, sizeof(receiver_addr));
    if (sc <= 0)
    {
        printf("Can't send data to the %s:%d", host, port);
        return -1;
    }

    return 0;
}

void exit_handler()
{
    close_socket(client_socket);
}
