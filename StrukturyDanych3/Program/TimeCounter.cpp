#include "stdafx.h"
#include "TimeCounter.h"

void TimeCounter::StartCounter() {
	LARGE_INTEGER li;	//64bitowa unia(jedno miejsce w pamiêci dla paru obiektów ró¿nego typu)
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart);	//QuadPart to znakowany 64bitowy int z LARGE_INTEGER

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double TimeCounter::GetCounter() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}