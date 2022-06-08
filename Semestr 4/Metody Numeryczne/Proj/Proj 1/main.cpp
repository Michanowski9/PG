#include <iostream>

#include "functions.h"


int main() {
	float money{};

	std::cout << "Podaj poczatkowy kapital w PLN: ";
	std::cin >> money;

	dataContainer result = getData("inputData/wig20_d.csv", "outputData/wig20_dCalc.csv", money);

	money = result.wallet;
	std::cout << std::endl << "Koncowy Kapital: " << money << std::endl;

}