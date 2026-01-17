#pragma once
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer
{
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::milli>;
	std::chrono::time_point<Clock> m_beg { Clock::now() };
public:
	void reset() {m_beg = Clock::now();}

	double elapsed() const { return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();}
};