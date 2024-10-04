#include "main.h"

int main(int argc, char* argv[])
{
	SERVER_CONFIG server_config;

	CLIENT_SESSION_PARAMETER_CONFIG parameter_config;
	parameter_config.request = NULL;
	parameter_config.request_size = sizeof(struct QuadraticEquation);
	parameter_config.response = NULL;
	parameter_config.response_size = sizeof(struct SquareRootData);

	server_config.port = DEFAULT_PORT;
	server_config.queue_size = DEFAULT_QUEUE;
	server_config.pool_size = DEFAULT_POOL_SIZE;
	server_config.session_handler = process_request;
	server_config.parameter_config = parameter_config;

	return start(argc, argv, &server_config);
}
