#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

//#define CONSOLE

#ifdef CONSOLE
	#include <iostream>
#endif // CONSOLE

#include <vector>
#include <deque>
#include <string>
#include <fstream>

struct dataContainer {
	float fund = 0;
	float wallet = 0;
	std::deque<float> value;
	std::deque<std::string> date;
	std::deque<float> macd;
	std::deque<float> signal;
};

std::vector<std::string> splitString(std::string input, char terminator);

float calcExpAverage(std::deque<float> input);

std::deque<float> getLastElements(std::deque<float> container, int number);

float calcExpMovingAverage(std::deque<float> container, int number);

void removeUnusedData(dataContainer* temp);

dataContainer getData(std::string inputFileName, std::string outputFileName, float fund, int numberOfRecords = -1);

#endif // _FUNCTIONS_H_