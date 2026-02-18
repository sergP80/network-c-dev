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

enum ArrayOp {AVG, SUM, MAX, MIN, MAX_MIN};

struct ArrayPacket
{
	enum ArrayOp operation;

	double data[1024];
};

struct ArrayResult
{
	enum ArrayOp operation;

	double data[8];
};
