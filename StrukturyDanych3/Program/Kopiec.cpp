#include "stdafx.h"
#include "Kopiec.h"

Kopiec::Kopiec(int sizee) {
	size = sizee;
	cnt = 0;
	kopiec = new float[size]; //kopiec o podanej ilosci elementow
	wagi = new int[size];
	numery = new int[size];
}

Kopiec::~Kopiec() {
	delete[] kopiec;	//to go usuwam
	delete[] wagi;
	delete[] numery;
}

void Kopiec::addValue(float value, int waga,int numer) {
	if (kopiec == NULL) {
		kopiec = new float[size];
		wagi = new int[size];
		numery = new int[size];
	}
	kopiec[cnt] = value;	//dodajemy na najnizszy element
	wagi[cnt] = waga;
	numery[cnt] = numer;
	int miejsce = cnt;	//pomocnicza zmienna wskazujaca na aktualna pozycje dodanego elementu
						//petla dopoki nie dotarlismy na szczyt kopca i dopoki rodzic jest mniejszy od dodawanego elementu
	while (miejsce != 0 && kopiec[miejsce] > kopiec[(int)floor((miejsce - 1) / 2)]) {
		float pomocnicze = kopiec[miejsce];	//zamieniamy ta liczbe i rodzica
		kopiec[miejsce] = kopiec[(int)floor((miejsce - 1) / 2)];
		kopiec[(int)floor((miejsce - 1) / 2)] = pomocnicze;
		int pomocnicze2 = wagi[miejsce];
		wagi[miejsce] = wagi[(int)floor((miejsce - 1) / 2)];
		wagi[(int)floor((miejsce - 1) / 2)] = pomocnicze2;
		pomocnicze2 = numery[miejsce];
		numery[miejsce] = numery[(int)floor((miejsce - 1) / 2)];
		numery[(int)floor((miejsce - 1) / 2)] = pomocnicze2;
		miejsce = (int)floor((miejsce - 1) / 2);	//i miejsce wskazuje nadal na dodawany element
	}
	cnt++;	//zwiekszenie liczby elementow kopca
}

void Kopiec::deleteFirst() {
	//funkcja do testów: usuwanie korzenia
	int wskaznik = 0;
	kopiec[wskaznik] = kopiec[cnt - 1];	//zamieniamy element przeznaczony do usuniecia tym z konca kopca
	wagi[wskaznik] = wagi[cnt - 1];
	numery[wskaznik] = numery[cnt - 1];
	kopiec[cnt - 1] = NULL;	//usuwamy ostatni element
	wagi[cnt - 1] = NULL;
	numery[cnt - 1] = NULL;
	cnt--;	//zmniejszenie liczby elementow kopca
	int syn = wskaznik * 2 + 1;	//wskazuje lewego syna
	while (syn < cnt - 1) {	//dopoki istnieje syn
		if (syn + 1 < cnt - 1 && kopiec[syn + 1] > kopiec[syn]) {	//sprawdzamy ktory syn jest wiekszy
			syn++;
		}
		if (kopiec[wskaznik] > kopiec[syn]) {	//jesli syn jest mniejszy niz liczba koniec petli
			break;
		}
		float pomocnicze = kopiec[wskaznik];	//zamieniamy liczbe i wiekszego syna
		kopiec[wskaznik] = kopiec[syn];
		kopiec[syn] = pomocnicze;
		int pomocnicze2 = wagi[wskaznik];
		wagi[wskaznik] = wagi[syn];
		wagi[syn] = pomocnicze2;
		pomocnicze2 = numery[wskaznik];
		numery[wskaznik] = numery[syn];
		numery[syn] = pomocnicze2;
		wskaznik = syn;	//idziemy poziom w dól
		syn = 2 * syn + 1;
	}
	return;
}