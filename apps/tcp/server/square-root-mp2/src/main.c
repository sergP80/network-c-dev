#include "main.h"

int process_request(P_CLIENT_SESSION_PARAMETER_CONFIG parameter_config)
{
	struct QuadraticEquation* request = (struct QuadraticEquation*) parameter_config->request;
	struct SquareRootData* response = (struct SquareRootData*) parameter_config->response;

	double a = request->a, b = request->b, c = request->c;
	
	char bc = '+';
	if (b < 0)
	{
		bc = '\0';
	}

	char cc = '+';
	if (c < 0)
	{
		cc = '\0';
	}

	printf("Equastion %.5f*x^2%c%.5f*x%c%.5f=0\n", a, bc, b, cc, c);

	double D = b * b - 4 * a * c;

	if (D < 0)
	{
		response->result = NO_ROOT;
		return 0;
	}

	response->x1 = (-b - sqrt(D)) / 2 / a;

	response->x2 = (-b + sqrt(D)) / 2 / a;

	if (fabs(response->x1 - response->x2) < 1e-9)
	{
		response->result = ONE_ROOT;
	}
	else {
		response->result = TWO_ROOT;
	}

	printf("Results: x1=%.3f, x2=%.3f\n", response->x1, response->x2);

	return 0;
}
