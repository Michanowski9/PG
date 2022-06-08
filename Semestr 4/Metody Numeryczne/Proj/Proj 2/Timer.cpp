#include "Timer.h"

void Timer::Start()
{
	start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
	end = std::chrono::high_resolution_clock::now();
}

Time Timer::GetTime()
{
	Time result;
	result.temp = (end - start).count();

	result.min = result.temp * pow(10, -9) / 60;

	result.sec = result.temp * pow(10, -9) - result.min * 60;

	double temp = (result.temp * pow(10, -5));
	temp = temp / 10;
	temp = round(temp);

	result.ms = temp;
	result.ms %= 1000;

	return result;
}
