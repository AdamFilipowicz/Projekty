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

struct tabuPoz{	//jedna para wierzcholkow w tablicy tabu
	int mniejszy;	//wierzcholek o mniejszym numerze
	int wiekszy;	//wierzcholek o wiekszym numerze
	int kadencja;	//kadencja pozycji
};

class Graf {
public:
	int **macierz;
	int iteracje;
	int kadencja;
	int krytyczne;	//ile iteracji bez poprawy powoduje zmianę całkowitą otoczenia
	int aspiracja;	//ile z listy tabu możemy wziąć jeśli nie znajdziemy dosyć dobrego rozwiązania
	tabuPoz *tabu;	//tablica tabu
	long long wynikk;		//liczba - najkrótsza ścieżka

	Graf(int n);

	~Graf();

	void algorytmTabuSearch();

	void algorytmLokalny2();

	void display();

	void displayRozwiazanie();

	int loadFromFile(string FileName, char symetria);

	void generateGraf(int lwierzch);

private:
	int w;	//liczba wierzcholkow
	int *wynik;		//permutacja - wynik dzialania algorytmow
	int *permutacja;	//obecna permutacja

	void algorytmLokalny();
};

#endif