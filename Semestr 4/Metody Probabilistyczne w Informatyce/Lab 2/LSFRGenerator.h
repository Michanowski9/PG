#pragma once
class LSFRGenerator {
public:
	LSFRGenerator(int x0);
	int Random();

private:
	int xn;
	int p = 7;
	int q = 3;
};

