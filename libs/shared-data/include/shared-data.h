#pragma once

struct QuadraticEquation
{
	double a;
	double b;
	double c;
};

enum SquareRootResult {NO_ROOT, ONE_ROOT, TWO_ROOT};

struct SquareRootData
{
	enum SquareRootResult result;

	double x1;
	
	double x2;
};

enum ArrayOp {AVG = 1, SUM, MAX, MIN, MAX_MIN};

struct ArrayPacket
{
	enum ArrayOp operation;

	double data[1024];
};

struct ArrayResult
{
	enum ArrayOp operation;

	int result_count;
	
	double data[8];

	char error_message[128];
};
