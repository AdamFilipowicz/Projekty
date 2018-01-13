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

class Graf {
public:
	int **macierz;
	int **tabOrganizmow;
	int **tabPoczatkowych;

	long long wynikk = INT_MAX;		//liczba - najkrótsza ścieżka
	int liczbaPoczatkowych = 10000;	//poczatkowa liczba organizmow
	int liczbaOrganizmow = 1000;	//liczba organizmow w algorytmie po selekcjach
	int iloscIteracji = 1000;		//ilosc iteracji głównej petli algorytmu
	int k = 10;	//wybieranie tylu organizmow z populacji poczatkowej
	float mutacja = 0.05;	//prawdopodobienstwo mutacji

	Graf(int n);

	~Graf();

	void algorytmPopulacyjny();

	void display();

	void displayRozwiazanie();

	int loadFromFile(string FileName, char symetria);

	void generateGraf(int lwierzch);

	void wyzeruj();

private:
	int w;	//liczba wierzcholkow
	int *wynik;		//permutacja - wynik dzialania algorytmow
	int *permutacja;	//permutacja na której obecnie wykonywane są działania
	long long *ocenaPoczatkowych;	//ocena przystosowania organizmów poczatkowych
	long long *ocenaOrganizmow;		//ocena przystosowania organizmów po selekcjach
};

#endif