#include "LinearGenerator.h"

LinearGenerator::LinearGenerator(int x0) : xn(x0) {

}

int LinearGenerator::Random() {
	xn = ((long long)a * xn + c) % M;
	return xn;
}