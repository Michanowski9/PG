#include <iostream>
#include "LinearGenerator.h"
#include "LSFRGenerator.h"

#define ARRAY_SIZE 10
#define N 100000
#define M pow(2, 31)

void linear() {
	auto linearGenerator = LinearGenerator(15);

	//creating empty array (filled by zeros)
	int result[ARRAY_SIZE] = {};

	//drawing numbers
	for (int i = 0; i < N; i++) {
		int randValue = linearGenerator.Random();
		int index = (long long)10 * randValue / M;
		result[index]++;
	}

	//printing array
	for (int i = 0; i < ARRAY_SIZE; i++) {
		std::cout << result[i] << std::endl;
	}
}

void lsfr() {
	auto lsfrGenerator = LSFRGenerator(90);

	//creating empty array (filled by zeros)
	int result[ARRAY_SIZE] = {};

	//drawing numbers
	for (int i = 0; i < N; i++) {
		int randValue = lsfrGenerator.Random();
		int index = (long long) 10 * randValue / M;
		result[index]++;
	}

	//printing array
	for (int i = 0; i < ARRAY_SIZE; i++) {
		std::cout << result[i] << std::endl;
	}
}

int main() {
	std::cout << "Zadanie 1 - linear:\n";
	linear();
	std::cout << std::endl;
	std::cout << "Zadanie 2 - lsfr:\n";
	lsfr();
}