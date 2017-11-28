#ifndef GRAF_INCLUDED
#define GRAF_INCLUDED

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>

using namespace std;

struct wartoscMinimum {
	int wartosc;	//wartosc sciezki
	int minimum;	//wierzcholek z ktorego przybyto
};

class Graf {
public:
	int **macierz;

	map<vector<int>, wartoscMinimum> D;	//wartosci

	Graf() {};

	Graf(int n);

	~Graf();

	void algorytmBHKRekurencja();

	void display();

	void displayRozwiazanie();

	int loadFromFile(string FileName, char symetria);

	void generateGraf(int lwierzch);

	void clear();

private:
	int w;	//liczba wierzcholkow
	int *wynik;		//permutacja - wynik dzialania algorytmow
	int wynikk;		//liczba - najkrótsza ścieżka
	int ktoryOstatni = -1;	//ostatni wierzcholek
	vector<int> settt;	//wektor ze wszystkmi wartościami do wywołania funkcji rekurencyjnej

	int rekurencja(vector<int> set);
};

#endif