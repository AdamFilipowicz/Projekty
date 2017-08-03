#ifndef PLECAK_INCLUDED
#define PLECAK_INCLUDED

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Plecak {
public:

	Plecak() {};

	Plecak(int liczbaEl, int pojemnoscPlecaka);

	~Plecak();

	void algorytmZupelny();

	void algorytmZachlannyWartosc();

	void algorytmZachlannyWartoscWaga();

	void algorytmDynamiczny();

	void display();

	void displayRozwiazanie();

	void displayRozwiazanieDynamiczne();

	int loadFromFile(string FileName);

	long generatePlecak(int rozmiarr);

private:

	int *rozmiar;
	int *wartosc;
	bool *rozwiazanie;

	int **A;	//tablica [n+1,b+1] do algorytmu dynamicznego
	int b;	//pojemnosc plecaka
	int n;	//liczba elementow
};

#endif