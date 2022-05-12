#pragma once
#include <math.h>

class LinearGenerator {
public:
	LinearGenerator(int x0);
	int Random();

private:
	int xn;
	int a = 69069;
	int c = 1;
	int M = pow(2, 31);
};