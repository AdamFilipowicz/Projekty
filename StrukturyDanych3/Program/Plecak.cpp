#include "stdafx.h"
#include "Plecak.h"
#include "Kopiec.h"

Plecak::Plecak(int liczbaEl, int pojemnoscPlecaka) {
	n = liczbaEl;
	b = pojemnoscPlecaka;
	rozmiar = new int[n]; //rozmiar o podanej ilosci elementow
	wartosc = new int[n]; //wartosc o podanej ilosci elementow
	rozwiazanie = new bool[n]; //rozwiazanie algorytmow: 0-element nie w plecaku, 1-element w plecaku
	for (int i = 0; i < n; i++) {
		rozwiazanie[i] = 0;
	}
	A = new int*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		A[i] = new int[b + 1];
		for (int j = 0; j < b + 1; j++) {
			A[i][j] = 0;
		}
	}
}

Plecak::~Plecak() {
	delete[] rozmiar;
	delete[] wartosc;
	delete[] rozwiazanie;
	for (int i = 0; i < n + 1; i++) {
		delete[] A[i];
	}
	delete[] A;
}

void Plecak::algorytmZupelny() {
	long maxcena = 0;	//po iteracji wybieramy maksymalna cene
	long cenaaktualna;	//cena ktorej uzywamy przy kazdej iteracji i porownujemy z maxcena
	long obciazenieaktualne;	//obciazenie plecaka - przerywa, gdy za duze
	bool* mozerozwiazanie = new bool[n];
	for (int i = 1; i < (1 << n); i++) {	//i przechodzi przez wszystkie binarne permutacje zbioru n elementowego
		cenaaktualna = 0;
		obciazenieaktualne = 0;
		for (int j = 0; j < n; j++) {	//sprawdza kazdy bit, jesli jest 1 - dodaje cene i obciazenie elementu
			mozerozwiazanie[j] = (i & (1 << (n - j - 1))) > 0;
			if (mozerozwiazanie[j]) {
				obciazenieaktualne += rozmiar[j];
				if (obciazenieaktualne > b) {	//sprawdzam czy obciazenie juz przekroczylo b 
					cenaaktualna = 0;	//jesli tak to ustawiam na duza liczbe zeby nie wybrac jej
					break;
				}
				cenaaktualna += wartosc[j];	//zwiekszamy cene przejscia
			}
		}
		if (cenaaktualna > maxcena) {	//jesli znalezlismy lepsza sciezke
			maxcena = cenaaktualna;	//aktualizujemy maksymalna cene
			for (int j = 0; j < n; j++) {	//i uaktualniamy rozwiazanie
				rozwiazanie[j] = mozerozwiazanie[j];
			}
		}
	}
	if (maxcena == 0) {	//jesli zadna sciezka nie zmienila ceny
		for (int j = 0; j < n; j++) {	//to znaczy ze nie ma rozwiazania
			rozwiazanie[j] = 0;
		}
	}

	delete[] mozerozwiazanie;
}

void Plecak::algorytmZachlannyWartosc() {
	long obciazenie = 0;
	Kopiec kopiec(n);
	for (int i = 0; i < n; i++) {
		kopiec.addValue((float)wartosc[i], rozmiar[i], i);
		rozwiazanie[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		if (obciazenie + kopiec.wagi[0] <= b) {
			obciazenie += kopiec.wagi[0];
			rozwiazanie[kopiec.numery[0]] = 1;
		}
		kopiec.deleteFirst();
	}
}

void Plecak::algorytmZachlannyWartoscWaga() {
	long obciazenie = 0;
	Kopiec kopiec(n);
	for (int i = 0; i < n; i++) {
		kopiec.addValue((float)wartosc[i]/(float)rozmiar[i], rozmiar[i], i);
		rozwiazanie[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		if (obciazenie + kopiec.wagi[0] <= b) {
			obciazenie += kopiec.wagi[0];
			rozwiazanie[kopiec.numery[0]] = 1;
		}
		kopiec.deleteFirst();
	}
}

void Plecak::algorytmDynamiczny() {
	//inicjalizacja tablicy wynikowej A
	A = new int*[n+1];
	for (int i = 0; i < n+1; i++){
		A[i] = new int[b+1];
		for (int j = 0; j < b+1; j++) {
			A[i][j] = 0;
		}
	}
	//tablica A[i][j] - najwieksza wartosc w plecaku dla j<=b oraz elementu (i-1)
	for (int i = 1; i < n + 1; i++) {
		for (int j = 0; j < b + 1; j++) {
			if (rozmiar[i - 1] > j) {	//dopoki nie mozna dodac elementu (i-1) wartosc taka sama jak dla elementu (i-2)
				A[i][j] = A[i - 1][j];
			}
			else {	//gdy mozna dodac - wartosc elementu jest 
				if (A[i - 1][j] > A[i - 1][j - rozmiar[i - 1]] + wartosc[i - 1])
					A[i][j] = A[i - 1][j];	//taka sama jak elementu (i-2) jesli nie oplaca sie dodac elementu (i-1)
				else
					A[i][j] = A[i - 1][j - rozmiar[i - 1]] + wartosc[i - 1];	//uaktualniona o dodanie elementu (i-2)
			}
		}
	}
	for (int i = 0; i < n + 1; i++) {
		delete[] A[i];
	}
	delete[] A;
}

void Plecak::display() {
	cout << "Pojemnosc plecaka: " << b << endl;
	cout << "Elementy w plecaku: [ waga(wartosc) ]" << endl;
	for (int i = 0; i < n; i++) {
		cout << rozmiar[i] << "(" << wartosc[i] << ") ";
	}
	cout << endl;
}

void Plecak::displayRozwiazanie() {
	int sumacena = 0;
	int sumawaga = 0;
	cout << "Rozwiazanie: [ waga(wartosc) ]" << endl;
	/*for (int i = 0; i < n; i++) {
		cout<<rozwiazanie[i]<<" ";
	}
	cout << endl;*/
	for (int i = 0; i < n; i++) {
		if (rozwiazanie[i]) {
			cout << rozmiar[i] << "(" << wartosc[i] << ") ";
			sumacena += wartosc[i];
			sumawaga += rozmiar[i];
		}
	}
	cout << endl << "Suma cen: " << sumacena << endl << "Suma wag: " << sumawaga << endl;
}

void Plecak::displayRozwiazanieDynamiczne() {
	for (int i = 0; i < n; i++){
		rozwiazanie[i] = 0;
	}
	int i = n;
	int j = b;
	while (i != 0) {
		if (A[i][j] != A[i - 1][j]) {
			rozwiazanie[i - 1] = 1;
			j = j - rozmiar[i - 1];
			i = i - 1;
		}
		else {
			i = i - 1;
		}
	}
	displayRozwiazanie();
}

int Plecak::loadFromFile(string FileName) {
	//usuwamy istniejace tablice
	delete[] rozmiar;
	delete[] wartosc;
	delete[] rozwiazanie;

	//inicjalizujemy nowe tablice
	rozmiar = new int[n]; //rozmiar o podanej ilosci elementow
	wartosc = new int[n]; //wartosc o podanej ilosci elementow
	rozwiazanie = new bool[n];

	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int omin1, omin2;
	plik >> omin1 >> omin2;
	int rozmiarr, wartoscc;
	for (int i = 0; i < omin2; i++) {	//odczytuje tyle krawedzi ile podanych na poczatku
		plik >> rozmiarr >> wartoscc;
		rozmiar[i] = rozmiarr; //dodanie krawedzi do macierzy
		wartosc[i] = wartoscc; //dodanie krawedzi do macierzy
		rozwiazanie[i] = 0;
	}
	return 1;
}

long Plecak::generatePlecak(int rozmiarr) {
	//usuwamy istniejace tablice
	delete[] rozmiar;
	delete[] wartosc;

	//inicjalizujemy nowe tablice
	rozmiar = new int[n]; //rozmiar o podanej ilosci elementow
	wartosc = new int[n]; //wartosc o podanej ilosci elementow

	long suma = 0;	//suma wartosci elementow
	for (int i = 0; i < n; i++) {	//losujemy kazdy element tablic
		rozmiar[i] = rand(); //dodanie krawedzi do macierzy
		wartosc[i] = rand(); //dodanie krawedzi do macierzy
		rozwiazanie[i] = 0;
		suma += rozmiar[i];
	}
	return suma;
}