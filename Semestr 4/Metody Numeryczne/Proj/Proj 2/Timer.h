#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

struct Time {
	long long temp = 0;
	int min = 0;
	int sec = 0;
	int ms = 0;
};

class Timer {
public:
	Timer() = default;
	void Start();
	void Stop();
	Time GetTime();

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
};

#endif // !_TIMER_H_