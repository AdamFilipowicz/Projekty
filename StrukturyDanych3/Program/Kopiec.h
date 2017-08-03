#ifndef KOPIEC_INCLUDED
#define KOPIEC_INCLUDED

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Kopiec {
public:
	float *kopiec;
	int *wagi;
	int *numery;


	Kopiec(int sizee);

	~Kopiec();

	void addValue(float value, int waga, int numer);

	void deleteFirst();

private:
	int size; //maksymalna wielkosc kopca
	int cnt;
};

#endif