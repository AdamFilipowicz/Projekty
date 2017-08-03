#ifndef TIMECOUNTER_INCLUDED
#define TIMECOUNTER_INCLUDED

#include <windows.h>
#include <iostream>

using namespace std;

class TimeCounter {
	double PCFreq = 0.0;
	__int64 CounterStart = 0;	//64bitowy int

public:

	void StartCounter();

	double GetCounter();
};

#endif