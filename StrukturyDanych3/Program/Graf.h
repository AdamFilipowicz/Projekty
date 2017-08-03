#ifndef GRAF_INCLUDED
#define GRAF_INCLUDED

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Graf {
public:
	int **macierz;

	Graf() {};

	Graf(int n);

	~Graf();

	void algorytmZupelny();

	void algorytmZachlanny(int poczatkowy);

	void algorytmLokalny();

	void display();

	void displayRozwiazanie();

	int loadFromFile(string FileName);

	void generateGraf(int lwierzch);

private:
	int w;	//liczba wierzcholkow
	int *wynik;		//permutacja - wynik dzialania algorytmow
	int *permutacja;	//obecna permutacja
};

#endif