#include "stdafx.h"
#include <conio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <iomanip>

using namespace std;

class TimeCounter {
	double PCFreq = 0.0;
	__int64 CounterStart = 0;	//64bitowy int

public:

	void StartCounter();

	double GetCounter();
};

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


class UnionFind {

private:
	int *set;	//las zbiorów roz³¹cznych wskazuj¹cych na rodzica
public:
	UnionFind(int n);

	~UnionFind();

	int FindSet(int e);

	void Union(int x, int y);
};

UnionFind::UnionFind(int n) {
	set = new int[n];	//nowa tablica
	for (int i = 0; i < n; i++) {	//kazdy element wskazuje na siebie tzn jest w osobnym zbiorze
		set[i] = i;
	}
};

UnionFind::~UnionFind() {
	delete[]set;
}

int UnionFind::FindSet(int e) {	//funkcja szuka rodzica elementu e
	int h = e;	//zapamietuje liczbe e
	while (e != set[e]) {	//e w petli staje sie rodzicem calego zbioru
		e = set[e];
	}
	while (h != set[h]) {	//kompresja sciezek (wszystkie elementy wskazuja na rodzica zbioru)
		int l = set[h];
		set[h] = e;
		h = l;
	}
	return e;
}

void UnionFind::Union(int x, int y) {	//funkcja scala grupy dwoch elementow
	int k = FindSet(x);	
	int l = FindSet(y);
	if (k != l) {	//jesli nie sa w tej samej grupie
		if (k<l) {
			set[l] = k;
		}
		else {
			set[k] = l;
		}
	}
}


struct Stack_Element {	//element stosu
	Stack_Element* next;
	int value;
};

class Stack {	//klasa stos LIFO do algorytmu Forda-Fulkersona w glab
private:
	Stack_Element* first = NULL;

public:

	~Stack();

	void put(int wartosc);

	bool isEmpty();

	int getFirst();

	void pop();
};

Stack::~Stack() {
	while (first != NULL) {
		pop();
	}
}

void Stack::put(int wartosc) {
	Stack_Element *nowy = new Stack_Element;
	(nowy->value) = wartosc;
	if (first)
		(nowy->next) = first;
	else
		(nowy->next) = NULL;
	first = nowy;
}

bool Stack::isEmpty() {
	return (first == NULL);
}

int Stack::getFirst() {
	return (first->value);
}

void Stack::pop() {
	if (first) {
		Stack_Element *nowy = first;
		if (first->next)
			first = (first->next);
		else
			first = NULL;
		delete nowy;
	}
}


struct Queue_Element {	//element stosu
	Queue_Element* next;
	int value;
};

class Queue {	//klasa kolejka FIFO do algorytmu Forda-Fulkersona wszerz
private:
	Queue_Element* first = NULL;
	Queue_Element* last = NULL;

public:

	~Queue();

	void put(int wartosc);

	bool isEmpty();

	int getFirst();

	void pop();
};

Queue::~Queue() {
	while (first != NULL) {
		pop();
	}
}

void Queue::put(int wartosc) {
	Queue_Element *nowy = new Queue_Element;
	(nowy->value) = wartosc;
	(nowy->next) = NULL;
	if (first) {
		(last->next) = nowy;
	}
	else {
		first = nowy;
	}
	last = nowy;
}

bool Queue::isEmpty() {
	return (first == NULL);
}

int Queue::getFirst() {
	return (first->value);
}

void Queue::pop() {
	if (first) {
		Queue_Element *nowy = first;
		if (first==last) {
			first = NULL;
			last = NULL;
		}
		else {
			first = (first->next);
		}
		delete nowy;
	}
}


struct List_Element {	//struktura jako element listy
	int value;	//wskazanie na wierzcholek
	int dane; //wartosc krawedzi
	int f; //przep³yw
	List_Element* next;	//wskaznik na nastepny element
};


class Graf {
public:
	int **macierz;
	List_Element **lista;

	Graf() {};

	Graf(int n, int m);

	~Graf();

	void PrimMacierz();

	void PrimLista();

	void KruskalMacierz();

	void KruskalLista();

	void DijkstraMacierz();

	void DijkstraLista();

	bool FBMacierz();

	bool FBLista();

	void FFMacierzWglab();

	void FFListaWglab();

	void FFMacierzWszerz();

	void FFListaWszerz();

	void displayLista();

	void displayMacierz();

	int loadFromFile(string FileName);

	int loadFromFileMST(string FileName);

	int loadFromFilePrzeplyw(string FileName);

	void generateGraf(int lwierzch, int gestosc);

	void generateGrafUjemny(int lwierzch, int gestosc);

	void generateGrafMST(int lwierzch, int gestosc);

	void generateGrafPrzeplyw(int lwierzch, int gestosc);

private:
	int w, k;
	int wpoczatkowy, wkoncowy;
};

Graf::Graf(int n, int m) {
	w = n;
	k = m;
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
}

Graf::~Graf() {
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++){
		elem1 = lista[i];
		while (elem1){
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;


	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
}

void Graf::PrimMacierz() {
	bool *odwiedzone = new bool[w];	//tablica odwiedzonych wierzcholkow
	int *pocz = new int[((w*w) - w) / 2]; //wierzcholek poczatkowy
	int *konc = new int[((w*w) - w) / 2]; //wierzcholek koncowy
	int *heap = new int[((w*w) - w) / 2]; //kopiec
	int cnt = 0; //rozmiar kopca
	int syn, ojciec;
	int x, y; //zmienne do nawigacji w macierzy(dane sa tylko w polowie)
	int suma=0; //wartosc sumy drzewa
	for (int i = 0; i < w; i++) {
		odwiedzone[i] = false;
	}

	List_Element **T;	//zbior krawedzi z wagami - minimalne drzewo rozpinajace
	T = new List_Element *[w];
	for (int i = 0; i < w; i++)
		T[i] = NULL;

	int wierzcholek = 0;	//wierzcholek poczatkowy
	odwiedzone[wierzcholek] = true;

	for (int i = 0; i < w - 1; i++) {	//w-1 krawedzi
		for (int j = 0; j < w; j++) {
			if (wierzcholek > j) {
				x = j;
				y = wierzcholek;
			}
			else if (wierzcholek < j) {
				x = wierzcholek;
				y = j;
			}
			else {
				continue;
			}
			if (macierz[x][y] != 0) {	//sprawdzam czy istnieje krawedz
				if (!odwiedzone[j]) {	//jesli wierzcholek docelowy nie jest odwiedzony
					heap[cnt] = macierz[x][y];
					pocz[cnt] = wierzcholek;
					konc[cnt] = j;
					cnt++;

					//naprawa kopca w gore po dodaniu
					syn = cnt - 1;
					ojciec = (syn - 1) / 2;
					while (syn != 0 && heap[ojciec] > heap[syn]) {
						int pomocnicze = heap[ojciec];	//zamieniamy ta liczbe i rodzica
						heap[ojciec] = heap[syn];
						heap[syn] = pomocnicze;

						pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
						pocz[ojciec] = pocz[syn];
						pocz[syn] = pomocnicze;

						pomocnicze = konc[ojciec];	//i koncowy
						konc[ojciec] = konc[syn];
						konc[syn] = pomocnicze;

						syn = ojciec;
						ojciec = (ojciec - 1) / 2;	//miejsce wskazuje nadal na dodawany element
					}
				}
			}
		}

		while (cnt != 0 && odwiedzone[konc[0]]) {	//jesli wierzcholek koncowy odwiedzony to zdejmujemy krawedz i bierzemy nastepna
			cnt--;
			heap[0] = heap[cnt];
			heap[cnt] = 0;
			pocz[0] = pocz[cnt];
			konc[0] = konc[cnt];
			ojciec = 0;
			//naprawa w dol kopca po usunieciu pierwszej krawedzi
			while (true) {
				syn = 2 * ojciec + 1;
				if (syn >= cnt)  //koniec gdy wyjdziemy poza kopiec
					break;
				if (syn + 1 < cnt && (heap[syn] > heap[syn + 1])) {
					syn++;
				}
				if (heap[ojciec] <= heap[syn]) //koniec gdy ojciec jest mniejszy od mniejszego syna
					break;

				int pomocnicze = heap[ojciec];	//zamiana w kopcu wierzcholkow ojca i wiekszego syna
				heap[ojciec] = heap[syn];
				heap[syn] = pomocnicze;

				pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
				pocz[ojciec] = pocz[syn];
				pocz[syn] = pomocnicze;

				pomocnicze = konc[ojciec];	//i koncowy
				konc[ojciec] = konc[syn];
				konc[syn] = pomocnicze;

				ojciec = syn;	//przejscie poziom nizej
			}
		}
		if (cnt != 0) {	//jeœli s¹ jeszcze krawêdzie
			List_Element *nowy = new List_Element;	//dodajemy pierwszy element kopca do naszych krawedzi
			(nowy->value) = pocz[0];
			(nowy->dane) = heap[0];
			(nowy->next) = T[konc[0]];
			T[konc[0]] = nowy;
		
			odwiedzone[konc[0]] = true;
			
			wierzcholek = konc[0];
		}
	}
	//wyswietlenie wyniku
	cout << "Wynik macierzowy: " << endl;
	for (int i = 0; i < w; i++) {
		cout << "Lista[" << i << "] = ";
		List_Element *nowy = T[i];
		while (nowy) {
			cout << (nowy->value) << "(" << (nowy->dane) << ")" << ' ';
			suma = suma + (nowy->dane);
			nowy = (nowy->next);
		}
		cout << endl;
	}
	cout << "Suma krawedzi: " << suma << endl;

	//usuwanie listy T
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = T[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] T;
	delete[] pocz;
	delete[] konc;
	delete[] heap;
	delete[] odwiedzone;
}

void Graf::PrimLista() {
	bool *odwiedzone = new bool[w];	//tablica odwiedzonych wierzcholkow
	int *pocz = new int[((w*w) - w) / 2]; //wierzcholek poczatkowy
	int *konc = new int[((w*w) - w) / 2]; //wierzcholek koncowy
	int *heap = new int[((w*w) - w) / 2]; //kopiec
	int cnt = 0; //rozmiar kopca
	int syn, ojciec;
	int suma = 0; //wartosc sumy drzewa
	List_Element *element = NULL;
	for (int i = 0; i < w; i++) {
		odwiedzone[i] = false;
	}

	List_Element **T;	//zbior krawedzi z wagami - minimalne drzewo rozpinajace
	T = new List_Element *[w];
	for (int i = 0; i < w; i++)
		T[i] = NULL;

	int wierzcholek = 0;	//wierzcholek poczatkowy
	odwiedzone[wierzcholek] = true;
	for (int i = 0; i < w - 1; i++) {	//w-1 krawedzi
		for (element = lista[wierzcholek]; element; element = element->next) {	//dla wszystkich krawedzi od korzenia
			if (!odwiedzone[element->value]) {	//jesli wierzcholek docelowy nie jest odwiedzony
				heap[cnt] = (element->dane);
				pocz[cnt] = wierzcholek;
				konc[cnt] = (element->value);
				cnt++;

				//naprawa kopca w gore po dodaniu
				syn = cnt - 1;
				ojciec = (syn - 1) / 2;
				while (syn != 0 && heap[ojciec] > heap[syn]) {
					int pomocnicze = heap[ojciec];	//zamieniamy ta liczbe i rodzica
					heap[ojciec] = heap[syn];
					heap[syn] = pomocnicze;

					pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
					pocz[ojciec] = pocz[syn];
					pocz[syn] = pomocnicze;

					pomocnicze = konc[ojciec];	//i koncowy
					konc[ojciec] = konc[syn];
					konc[syn] = pomocnicze;

					syn = ojciec;
					ojciec = (ojciec - 1) / 2;	//miejsce wskazuje nadal na dodawany element
				}
			}
		}

		while (cnt != 0 && odwiedzone[konc[0]]) {	//jesli wierzcholek koncowy odwiedzony to zdejmujemy krawedz i bierzemy nastepna
			cnt--;
			heap[0] = heap[cnt];
			heap[cnt] = 0;
			pocz[0] = pocz[cnt];
			konc[0] = konc[cnt];
			ojciec = 0;
			//naprawa w dol kopca po usunieciu pierwszej krawedzi
			while (true) {
				syn = 2 * ojciec + 1;
				if (syn >= cnt)  //koniec gdy wyjdziemy poza kopiec
					break;
				if (syn + 1 < cnt && (heap[syn] > heap[syn + 1])) {
					syn++;
				}
				if (heap[ojciec] <= heap[syn]) //koniec gdy ojciec jest mniejszy od mniejszego syna
					break;

				int pomocnicze = heap[ojciec];	//zamiana w kopcu wierzcholkow ojca i wiekszego syna
				heap[ojciec] = heap[syn];
				heap[syn] = pomocnicze;

				pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
				pocz[ojciec] = pocz[syn];
				pocz[syn] = pomocnicze;

				pomocnicze = konc[ojciec];	//i koncowy
				konc[ojciec] = konc[syn];
				konc[syn] = pomocnicze;

				ojciec = syn;	//przejscie poziom nizej
			}
		}
		if (cnt != 0) {	//jeœli s¹ jeszcze krawêdzie
			List_Element *nowy = new List_Element;	//dodajemy pierwszy element kopca do naszych krawedzi
			(nowy->value) = pocz[0];
			(nowy->dane) = heap[0];
			(nowy->next) = T[konc[0]];
			T[konc[0]] = nowy;

			odwiedzone[konc[0]] = true;

			wierzcholek = konc[0];
		}
	}
	//wyswietlenie wyniku
	cout << "Wynik macierzowy: " << endl;
	for (int i = 0; i < w; i++) {
		cout << "Lista[" << i << "] = ";
		List_Element *nowy = T[i];
		while (nowy) {
			cout << (nowy->value) << "(" << (nowy->dane) << ")" << ' ';
			suma = suma + (nowy->dane);
			nowy = (nowy->next);
		}
		cout << endl;
	}
	cout << "Suma krawedzi: " << suma << endl;

	//usuwanie listy T
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = T[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] T;
	delete[] pocz;
	delete[] konc;
	delete[] heap;
	delete[] odwiedzone;
}

void Graf::KruskalMacierz(){
	//kazdy wierzcholek jest osobnym zbiorem rozlacznym
	UnionFind *zbiory = new UnionFind(w);
	
	//kolejka priorytetowa jako kopiec
	int *pocz = new int[((w*w) - w) / 2]; //wierzcholek poczatkowy
	int *konc = new int[((w*w) - w) / 2]; //wierzcholek koncowy
	int *heap = new int[((w*w) - w) / 2]; //kopiec
	int cnt = 0;	//ilosc elementow (krawedzi) w kopcu
	int syn, ojciec;

	int suma = 0;
	
	//zbior krawedzi z wagami - minimalne drzewo rozpinajace
	List_Element **T;	
	T = new List_Element *[w];
	for (int i = 0; i < w; i++)
		T[i] = NULL;
	for (int i = 0; i < w-1; i++) {	//dodajemy wszystkie krawedzie do kopca
		for (int j = i+1; j < w; j++) {
			if (macierz[i][j] != 0) {	//sprawdzam czy istnieje krawedz
				heap[cnt] = macierz[i][j];
				pocz[cnt] = i;
				konc[cnt] = j;
				cnt++;

				//naprawa kopca w gore po dodaniu
				syn = cnt - 1;
				ojciec = (syn - 1) / 2;
				while (syn != 0 && heap[ojciec] > heap[syn]) {
					int pomocnicze = heap[ojciec];	//zamieniamy ta liczbe i rodzica
					heap[ojciec] = heap[syn];
					heap[syn] = pomocnicze;

					pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
					pocz[ojciec] = pocz[syn];
					pocz[syn] = pomocnicze;

					pomocnicze = konc[ojciec];	//i koncowy
					konc[ojciec] = konc[syn];
					konc[syn] = pomocnicze;

					syn = ojciec;
					ojciec = (ojciec - 1) / 2;	//miejsce wskazuje nadal na dodawany element
				}
			}
		}
	}

	for (int i = 1; i < w; i++) {
		while (cnt != 0 && (zbiory->FindSet(pocz[0])==zbiory->FindSet(konc[0]))) {	//jesli wierzcholki sa w tym samym zbiorze to zdejmujemy krawedz i bierzemy nastepna
			cnt--;
			heap[0] = heap[cnt];
			heap[cnt] = 0;
			pocz[0] = pocz[cnt];
			konc[0] = konc[cnt];
			ojciec = 0;
			//naprawa w dol kopca po usunieciu pierwszej krawedzi
			while (true) {
				syn = 2 * ojciec + 1;
				if (syn >= cnt)  //koniec gdy wyjdziemy poza kopiec
					break;
				if (syn + 1 < cnt && (heap[syn] > heap[syn + 1])) {
					syn++;
				}
				if (heap[ojciec] <= heap[syn]) //koniec gdy ojciec jest mniejszy od mniejszego syna
					break;

				int pomocnicze = heap[ojciec];	//zamiana w kopcu wierzcholkow ojca i wiekszego syna
				heap[ojciec] = heap[syn];
				heap[syn] = pomocnicze;

				pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
				pocz[ojciec] = pocz[syn];
				pocz[syn] = pomocnicze;

				pomocnicze = konc[ojciec];	//i koncowy
				konc[ojciec] = konc[syn];
				konc[syn] = pomocnicze;

				ojciec = syn;	//przejscie poziom nizej
			}
		}
		if (cnt != 0) {	//jeœli s¹ jeszcze krawêdzie
			List_Element *nowy = new List_Element;	//dodajemy pierwszy element kopca do naszych krawedzi
			(nowy->value) = pocz[0];
			(nowy->dane) = heap[0];
			(nowy->next) = T[konc[0]];
			T[konc[0]] = nowy;

			zbiory->Union(pocz[0], konc[0]);
		}
	}
	//wyswietlenie wyniku
	cout << "Wynik macierzowy: " << endl;
	for (int i = 0; i < w; i++) {
		cout << "Lista[" << i << "] = ";
		List_Element *nowy = T[i];
		while (nowy) {
			cout << (nowy->value) << "(" << (nowy->dane) << ")" << ' ';
			suma = suma + (nowy->dane);
			nowy = (nowy->next);
		}
		cout << endl;
	}
	cout << "Suma krawedzi: " << suma << endl;



	//usuwanie listy T
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = T[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] T;
	delete[] pocz;
	delete[] konc;
	delete[] heap;
}

void Graf::KruskalLista() {
	//kazdy wierzcholek jest osobnym zbiorem rozlacznym
	UnionFind *zbiory = new UnionFind(2*w);

	//kolejka priorytetowa jako kopiec
	int *pocz = new int[w*w]; //wierzcholek poczatkowy
	int *konc = new int[w*w]; //wierzcholek koncowy
	int *heap = new int[w*w]; //kopiec
	int cnt = 0;	//ilosc elementow (krawedzi) w kopcu
	int syn, ojciec;

	List_Element *element = NULL;
	int suma = 0;

	//zbior krawedzi z wagami - minimalne drzewo rozpinajace
	List_Element **T;
	T = new List_Element *[w];
	for (int i = 0; i < w; i++)
		T[i] = NULL;
	for (int i = 0; i < w - 1; i++) {	//dodajemy wszystkie krawedzie do kopca
		for (element = lista[i]; element; element = element->next) {	//dla wszystkich krawedzi od korzenia
			if ((element->value) != 0) {	//sprawdzam czy istnieje krawedz
				heap[cnt] = (element->dane);
				pocz[cnt] = i;
				konc[cnt] = (element->value);
				cnt++;

				//naprawa kopca w gore po dodaniu
				syn = cnt - 1;
				ojciec = (syn - 1) / 2;
				while (syn != 0 && heap[ojciec] > heap[syn]) {
					int pomocnicze = heap[ojciec];	//zamieniamy ta liczbe i rodzica
					heap[ojciec] = heap[syn];
					heap[syn] = pomocnicze;

					pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
					pocz[ojciec] = pocz[syn];
					pocz[syn] = pomocnicze;

					pomocnicze = konc[ojciec];	//i koncowy
					konc[ojciec] = konc[syn];
					konc[syn] = pomocnicze;

					syn = ojciec;
					ojciec = (ojciec - 1) / 2;	//miejsce wskazuje nadal na dodawany element
				}
			}
		}
	}

	for (int i = 1; i < w; i++) {
		while (cnt != 0 && (zbiory->FindSet(pocz[0]) == zbiory->FindSet(konc[0]))) {	//jesli wierzcholki sa w tym samym zbiorze to zdejmujemy krawedz i bierzemy nastepna
			cnt--;
			heap[0] = heap[cnt];
			heap[cnt] = 0;
			pocz[0] = pocz[cnt];
			konc[0] = konc[cnt];
			ojciec = 0;
			//naprawa w dol kopca po usunieciu pierwszej krawedzi
			while (true) {
				syn = 2 * ojciec + 1;
				if (syn >= cnt)  //koniec gdy wyjdziemy poza kopiec
					break;
				if (syn + 1 < cnt && (heap[syn] > heap[syn + 1])) {
					syn++;
				}
				if (heap[ojciec] <= heap[syn]) //koniec gdy ojciec jest mniejszy od mniejszego syna
					break;

				int pomocnicze = heap[ojciec];	//zamiana w kopcu wierzcholkow ojca i wiekszego syna
				heap[ojciec] = heap[syn];
				heap[syn] = pomocnicze;

				pomocnicze = pocz[ojciec];	//i wierzolek poczatkowy
				pocz[ojciec] = pocz[syn];
				pocz[syn] = pomocnicze;

				pomocnicze = konc[ojciec];	//i koncowy
				konc[ojciec] = konc[syn];
				konc[syn] = pomocnicze;

				ojciec = syn;	//przejscie poziom nizej
			}
		}
		if (cnt != 0) {	//jeœli s¹ jeszcze krawêdzie
			List_Element *nowy = new List_Element;	//dodajemy pierwszy element kopca do naszych krawedzi
			(nowy->value) = pocz[0];
			(nowy->dane) = heap[0];
			(nowy->next) = T[konc[0]];
			T[konc[0]] = nowy;

			zbiory->Union(pocz[0], konc[0]);
		}
	}
	//wyswietlenie wyniku
	cout << "Wynik listowy: " << endl;
	for (int i = 0; i < w; i++) {
		cout << "Lista[" << i << "] = ";
		List_Element *nowy = T[i];
		while (nowy) {
			cout << (nowy->value) << "(" << (nowy->dane) << ")" << ' ';
			suma = suma + (nowy->dane);
			nowy = (nowy->next);
		}
		cout << endl;
	}
	cout << "Suma krawedzi: " << suma << endl;



	//usuwanie listy T
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = T[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] T;
	delete[] pocz;
	delete[] konc;
	delete[] heap;
}

void Graf::DijkstraMacierz(){
	int *d = new int[w];//odleglosc od startowego wierzcholka
	int *p = new int[w]; //wierzcholek z ktorego osiagnieto dany wierzcholek
	int *h = new int[w]; //pozycja wierzcholka w kopcu
	int *heap = new int[w]; //kopiec
	int korzen, ojciec, syn;
	bool ktory = false;
	bool *QS = new bool[w]; //zbior Q-wierzcholki z niepoliczonymi sciezkami (false), S-wierzcholki z policzonymi sciazkami (true)
	int dlugosckopca = w;

	for (int i = 0; i < w; i++) {
		QS[i] = false;
		d[i] = MAXINT;
		p[i] = -1;
		h[i] = i;
		heap[i] = i;
	}

	d[wpoczatkowy] = 0;
	int pomoc = heap[0];	//wstawiamy poczatkowy wierzcholek na gore (ma d=0)
	heap[0] = heap[wpoczatkowy]; 
	heap[wpoczatkowy] = pomoc;
	h[wpoczatkowy] = 0; 
	h[0] = wpoczatkowy;

	for (int i = 0; i < w; i++) {
		korzen = heap[0];

		for (int j = 0; j < w; j++) {	//dla mozliwych krawedzi 
			if (macierz[korzen][j] != 0) {	//sprawdzam czy krawedz istnieje
				if (!QS[j] && d[korzen] + macierz[korzen][j] < d[j]) {	//jesli droga do niej jest krotsza od dotychczasowej
					d[j] = d[korzen] + macierz[korzen][j];	//to aktualizuje ja
					p[j] = korzen;
					//naprawa w gore
					syn = h[j];
					ojciec = (syn - 1) / 2;
					while (syn != 0 && d[heap[ojciec]] > d[heap[syn]]) {
						int pomocnicze = heap[ojciec];	//zamieniamy ta liczbe i rodzica
						heap[ojciec] = heap[syn];
						heap[syn] = pomocnicze;

						h[heap[ojciec]] = ojciec;
						h[heap[syn]] = syn;

						syn = ojciec;
						ojciec = (ojciec - 1) / 2;	//i miejsce wskazuje nadal na dodawany element
					}
				}
			}
		}

		//usuniecie korzenia kopca i naprawa w dol
		dlugosckopca--;
		heap[0] = heap[dlugosckopca];
		h[heap[0]] = 0;
		ojciec = 0;
		while (true) {
			syn = 2 * ojciec + 1;
			if (syn >= dlugosckopca)  //koniec gdy wyjdziemy poza kopiec
				break;
			if (syn + 1 < dlugosckopca && (d[heap[syn]] > d[heap[syn + 1]])) {
				syn++;
			}
			if (d[heap[ojciec]] <= d[heap[syn]]) //koniec gdy ojciec jest mniejszy od mniejszego syna
				break;

			pomoc = heap[ojciec];	//zamiana w kopcu wierzcholkow ojca i wiekszego syna
			heap[ojciec] = heap[syn];
			heap[syn] = pomoc;
			h[heap[ojciec]] = ojciec;	//zamiana w pozycji wierzcholka zeby dobrze wskazywala
			h[heap[syn]] = syn;
			ojciec = syn;	//przejscie poziom nizej
		}
		QS[korzen] = true;	//wierzcholek oznaczamy jako odwiedzony
	}

	//wynik macierzowy
	cout << "Wynik macierzowy: " << endl;
	int pe; //wskazuje aktualny wierzcholek przy wypisywaniu
	for (int i = 0; i < w; i++) {
		if (p[i]==-1) {
			cout << i << ": " << ("Brak sciezki") << endl;;
		}
		else{
			cout << i << ": " << i << " <- ";
			pe = p[i];
			while (pe != wpoczatkowy) {
				cout << pe << " <- ";
				pe = p[pe];
			}
			cout << pe << "(" << d[i] << ")" << endl;
		}
	}
	cout << endl;

	delete[]d;
	delete[]p;
	delete[]h;
	delete[]heap;
	delete[]QS;
}

void Graf::DijkstraLista() {
	int *d = new int[w];//odleglosc od startowego wierzcholka
	int *p = new int[w]; //wierzcholek z ktorego osiagnieto dany wierzcholek
	int *h = new int[w]; //pozycja wierzcholka w kopcu
	int *heap = new int[w]; //kopiec
	int korzen, ojciec, syn;
	bool ktory = false;
	bool *QS = new bool[w]; //zbior Q-wierzcholki z niepoliczonymi sciezkami (false), S-wierzcholki z policzonymi sciazkami (true)
	int dlugosckopca = w;
	List_Element *element = NULL;

	for (int i = 0; i < w; i++) {
		QS[i] = false;
		d[i] = MAXINT;
		p[i] = -1;
		h[i] = i;
		heap[i] = i;
	}

	d[wpoczatkowy] = 0;
	int pomoc = heap[0];	//wstawiamy poczatkowy wierzcholek na gore (ma d=0)
	heap[0] = heap[wpoczatkowy];
	heap[wpoczatkowy] = pomoc;
	h[wpoczatkowy] = 0;
	h[0] = wpoczatkowy;

	for (int i = 0; i < w; i++) {
		korzen = heap[0];

		for (element = lista[korzen]; element; element = element->next) {	//dla wszystkich krawedzi od korzenia
			if (!QS[element->value] && d[korzen] + (element->dane) < d[element->value]) {	//jesli droga do krawedzi jest krotsza od dotychczasowej
				d[element->value] = d[korzen] + (element->dane);	//to aktualizuje ja
				p[element->value] = korzen;
				//naprawa w gore
				syn = h[element->value];
				ojciec = (syn - 1) / 2;
				while (syn != 0 && d[heap[ojciec]] > d[heap[syn]]) {
					int pomocnicze = heap[ojciec];	//zamieniamy ta liczbe i rodzica
					heap[ojciec] = heap[syn];
					heap[syn] = pomocnicze;

					h[heap[ojciec]] = ojciec;
					h[heap[syn]] = syn;

					syn = ojciec;
					ojciec = (ojciec - 1) / 2;	//i miejsce wskazuje nadal na dodawany element
				}
			}
		}

		//usuniecie korzenia kopca i naprawa w dol
		dlugosckopca--;
		heap[0] = heap[dlugosckopca];
		h[heap[0]] = 0;
		ojciec = 0;
		while (true) {
			syn = 2 * ojciec + 1;
			if (syn >= dlugosckopca)  //koniec gdy wyjdziemy poza kopiec
				break;
			if (syn + 1 < dlugosckopca && (d[heap[syn]] > d[heap[syn + 1]])) {
				syn++;
			}
			if (d[heap[ojciec]] <= d[heap[syn]]) //koniec gdy ojciec jest mniejszy od mniejszego syna
				break;

			pomoc = heap[ojciec];	//zamiana w kopcu wierzcholkow ojca i wiekszego syna
			heap[ojciec] = heap[syn];
			heap[syn] = pomoc;
			h[heap[ojciec]] = ojciec;	//zamiana w pozycji wierzcholka zeby dobrze wskazywala
			h[heap[syn]] = syn;
			ojciec = syn;	//przejscie poziom nizej
		}
		QS[korzen] = true;	//wierzcholek oznaczamy jako odwiedzony
	}

	//wynik listowy
	cout << "Wynik listowy: " << endl;
	int pe; //wskazuje aktualny wierzcholek przy wypisywaniu
	for (int i = 0; i < w; i++) {
		if (p[i]==-1) {
			cout << i << ": " << ("Brak sciezki") << endl;;
		}
		else {
			cout << i << ": " << i << " <- ";
			pe = p[i];
			while (pe != wpoczatkowy) {
				cout << pe << " <- ";
				pe = p[pe];
			}
			cout << pe << "(" << d[i] << ")" << endl;
		}
	}
	cout << endl;

	delete[]d;
	delete[]p;
	delete[]h;
	delete[]heap;
	delete[]QS;
}

bool Graf::FBMacierz() {
	int *d = new int[w];//odleglosc od startowego wierzcholka
	int *p = new int[w]; //wierzcholek z ktorego osiagnieto dany wierzcholek
	int *h = new int[w]; //pozycja wierzcholka w kopcu
	int *heap = new int[w]; //kopiec
	bool ktory = false;
	bool *QS = new bool[w]; //zbior Q-wierzcholki z niepoliczonymi sciezkami (false), S-wierzcholki z policzonymi sciazkami (true)
	int dlugosckopca = w;
	bool zmiany;

	for (int i = 0; i < w; i++) {
		QS[i] = false;
		d[i] = MAXINT;
		p[i] = -1;
		h[i] = i;
		heap[i] = i;
	}

	d[wpoczatkowy] = 0;

	for (int i = 0; i < w; i++) {
		zmiany = true;
		for (int k = 0; k < w; k++) {
			for (int j = 0; j < w; j++) {	//dla mozliwych krawedzi 
				if (macierz[k][j] != 0) {	//sprawdzam czy krawedz istnieje
					if (d[k]!=MAXINT && d[k] + macierz[k][j] < d[j]) {	//jesli droga do niej jest krotsza od dotychczasowej
						zmiany = false;	//zaszly zmiany
						d[j] = d[k] + macierz[k][j];	//to aktualizuje ja
						p[j] = k;
					}
				}
			}
		}
		
		if (zmiany) {	//jesli nie bylo zmian wypisujemy wynik
			//wynik macierzowy
			cout << "Wynik macierzowy: " << endl;
			int pe; //wskazuje aktualny wierzcholek przy wypisywaniu
			for (int i = 0; i < w; i++) {
				if (p[i] == -1) {
					cout << i << ": " << ("Brak sciezki") << endl;;
				}
				else {
					cout << i << ": " << i << " <- ";
					pe = p[i];
					while (pe != wpoczatkowy) {
						cout << pe << " <- ";
						pe = p[pe];
					}
					cout << pe << "(" << d[i] << ")" << endl;
				}
			}
			cout << endl;
			delete[]d;
			delete[]p;
			delete[]h;
			delete[]heap;
			delete[]QS;
			return 0;
		}

	}

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {	//dla mozliwych krawedzi 
			if (macierz[i][j] != 0) {	//sprawdzam czy krawedz istnieje
				if (d[i] + macierz[i][j] < d[j]) {	//jesli droga do niej jest krotsza od dotychczasowej
					cout << "Cykl ujemny!" << endl;
					delete[]d;
					delete[]p;
					delete[]h;
					delete[]heap;
					delete[]QS;
					return 0;
				}
			}
		}
	}

	//wynik listowy
	cout << "Wynik listowy: " << endl;
	int pe; //wskazuje aktualny wierzcholek przy wypisywaniu
	for (int i = 0; i < w; i++) {
		if (p[i] == -1) {
			cout << i << ": " << ("Brak sciezki") << endl;;
		}
		else {
			cout << i << ": " << i << " <- ";
			pe = p[i];
			while (pe != wpoczatkowy) {
				cout << pe << " <- ";
				pe = p[pe];
			}
			cout << pe << "(" << d[i] << ")" << endl;
		}
	}
	cout << endl;

	delete[]d;
	delete[]p;
	delete[]h;
	delete[]heap;
	delete[]QS;
	return 0;
}

bool Graf::FBLista() {
	int *d = new int[w];//odleglosc od startowego wierzcholka
	int *p = new int[w]; //wierzcholek z ktorego osiagnieto dany wierzcholek
	bool ktory = false;
	bool *QS = new bool[w]; //zbior Q-wierzcholki z niepoliczonymi sciezkami (false), S-wierzcholki z policzonymi sciazkami (true)
	int dlugosckopca = w;
	List_Element *element = NULL;
	bool zmiany;

	for (int i = 0; i < w; i++) {
		QS[i] = false;
		d[i] = MAXINT;
		p[i] = -1;
	}

	d[wpoczatkowy] = 0;

	for (int i = 1; i < w; i++) {	//pêtla relaksacji n-1 razy
		zmiany = true;
		for (int j = 0; j < w; j++) {
			for (element = lista[j]; element; element = element->next) {	//dla wszystkich krawedzi od korzenia
				if (d[j]!=MAXINT && d[j] + (element->dane) < d[element->value]) {	//jesli droga do krawedzi jest krotsza od dotychczasowej
					zmiany = false;	//zaszly zmiany
					d[element->value] = d[j] + (element->dane);	//to aktualizuje ja
					p[element->value] = j;
				}
			}
		}
		if (zmiany) {	//jesli nie bylo zmian wypisujemy wynik (tzn, ¿e nie ma cykli ujemnych)
			//wynik listowy
			cout << "Wynik listowy: " << endl;
			int pe; //wskazuje aktualny wierzcholek przy wypisywaniu
			for (int i = 0; i < w; i++) {
				if (p[i] == -1) {
					cout << i << ": " << ("Brak sciezki") << endl;;
				}
				else {
					cout << i << ": " << i << " <- ";
					pe = p[i];
					while (pe != wpoczatkowy) {
						cout << pe << " <- ";
						pe = p[pe];
					}
					cout << pe << "(" << d[i] << ")" << endl;
				}
			}
			cout << endl;
			delete[]d;
			delete[]p;
			delete[]QS;
			return 0;
		}

	}

	for (int i = 0; i < w; i++) {
		for (element = lista[i]; element; element = element->next) {	//dla wszystkich krawedzi od korzenia
			if (d[i] + (element->dane) < d[element->value]) {
				cout << "Cykl ujemny!" << endl;
				delete[]d;
				delete[]p;
				delete[]QS;
				return 0;
			}
		}
	}

	//wynik listowy
	cout << "Wynik listowy: " << endl;
	int pe; //wskazuje aktualny wierzcholek przy wypisywaniu
	for (int i = 0; i < w; i++) {
		if (p[i] == -1) {
			cout << i << ": " << ("Brak sciezki") << endl;;
		}
		else {
			cout << i << ": " << i << " <- ";
			pe = p[i];
			while (pe != wpoczatkowy) {
				cout << pe << " <- ";
				pe = p[pe];
			}
			cout << pe << "(" << d[i] << ")" << endl;
		}
	}
	cout << endl;

	delete[]d;
	delete[]p;
	delete[]QS;
	return 0;
}

void Graf::FFMacierzWglab() {
	int przeplyw = 0;	//przeplyw maksymalny
	int *maxprzep = new int[w];	//maksymalny przeplyw do danego wierzcholka w pojedynczej sciezce
	int *zktorego = new int[w]; //z ktorego wierzcholka prowadzila sciezka
	int **obecnyprzeplyw = new int*[w]; //ilosc juz 'przeplynieta' dla kazdej krawedzi
	for (int i = 0; i < w; i++)
		obecnyprzeplyw[i] = new int[w];
	bool *visited = new bool[w]; //czy wierzcholek juz odwiedzony
	int element = wpoczatkowy;	//wskazuje na aktualny element
	int teraz;	//pomocnicza
	Stack *stos = new Stack;	//inicjalizujemy stos
	stos->put(element);	//wkladamy wierzcholek poczatkowy
	for (int i = 0; i < w; i++) {
		maxprzep[i] = 0;
		zktorego[i] = -1;
		visited[i] = false;
		for (int j = 0; j < w; j++) {
			obecnyprzeplyw[i][j] = 0;
		}
	}
	maxprzep[element] = MAXINT;	//zeby nie blokowal zadnego przeplywu

	while (true) {
		while (!(stos->isEmpty()) && element != wkoncowy) {	//petla pojedynczej sciezki przeplywu
			for (int i = 0; i < w; i++) {	//sprawdzamy wszystkie krawedzie z obecnego wierzcholka
				if (macierz[element][i] - obecnyprzeplyw[element][i] > 0) {	//jesli jest jeszcze mozliwy przeplyw
					if (!visited[i]) {	//i wierzcholek docelowy jeszcze jest nieodwiedzony
						stos->put(i);	//to klade go na stos
						zktorego[i] = element;	//oznaczam przychodze do niego z danego wierzcholka
						maxprzep[i] = min(macierz[element][i] - obecnyprzeplyw[element][i], maxprzep[element]);	//i wyliczam jego maksymalny przeplyw w danej sciezce
						visited[i] = true;	//odwiedzony (bo jest w stosie)
					}
				}
			}
			element = (stos->getFirst());
			stos->pop();
		}
		if (element != wkoncowy){	//koniec jesli nie ma juz sciezki rozpinajacej
			break;
		}
		else {
			przeplyw += maxprzep[element];	//przeplyw grafu zwieksza sie o przeplyw maksymalny dla sciezki
			teraz = maxprzep[element];
			while (element != wpoczatkowy) {	//do wszystkich elementow na sciezce dodajemy przeplyw uzyskany w iteracji petli while
				obecnyprzeplyw[zktorego[element]][element] += teraz;
				element = zktorego[element];
			}
			//powrot zmiennych do stanu poczatkowego - gotowe do kolejnej sciezki
			for (int i = 0; i < w; i++) {
				maxprzep[i] = 0;
				zktorego[i] = -1;
				visited[i] = false;
			}
			element = wpoczatkowy;
			maxprzep[element] = MAXINT;
			while (!(stos->isEmpty())) {
				stos->pop();
			}
			stos->put(element);
		}
	}
	//wyswietlenie wyniku
	//cout << "Wynik macierzowy: " << endl;
	//cout << "Maksymalny przeplyw: " << przeplyw << endl;
	for (int i = 0; i < w; i++) {
		delete[] obecnyprzeplyw[i];
	}
	delete[] obecnyprzeplyw;
	delete[] maxprzep;
	delete[] zktorego;
	delete[] visited;
}

void Graf::FFListaWglab() {
	int przeplyw = 0;	//przeplyw maksymalny
	int *maxprzep = new int[w];	//maksymalny przeplyw do danego wierzcholka w pojedynczej sciezce
	int *zktorego = new int[w]; //z ktorego wierzcholka prowadzila sciezka
	bool *visited = new bool[w]; //czy wierzcholek juz odwiedzony
	int element = wpoczatkowy;	//wskazuje na aktualny element
	int teraz, naktory;	//pomocnicze
	Stack *stos = new Stack;	//inicjalizujemy stos
	stos->put(element);	//wkladamy wierzcholek poczatkowy
	for (int i = 0; i < w; i++) {
		maxprzep[i] = 0;
		zktorego[i] = -1;
		visited[i] = false;
		for (List_Element *elem = lista[i]; elem; elem = elem->next) {	//dla wszystkich krawedzi od korzenia
			(elem->f) = 0;	//zeruje aktualny przeplyw
		}
	}
	maxprzep[element] = MAXINT;	//zeby nie blokowal zadnego przeplywu

	while (true) {
		while (!(stos->isEmpty()) && element != wkoncowy) {	//petla pojedynczej sciezki przeplywu
			for (List_Element *elem = lista[element]; elem; elem = elem->next) {	//dla wszystkich krawedzi od korzenia
				if ((elem->dane) - (elem->f) > 0) {	//jesli jest jeszcze mozliwy przeplyw
					if (!visited[(elem->value)]) {	//i wierzcholek docelowy jeszcze jest nieodwiedzony
						stos->put((elem->value));	//to klade go na stos
						zktorego[(elem->value)] = element;	//oznaczam przychodze do niego z danego wierzcholka
						maxprzep[(elem->value)] = min((elem->dane) - (elem->f), maxprzep[element]);	//i wyliczam jego maksymalny przeplyw w danej sciezce
						visited[(elem->value)] = true;	//odwiedzony (bo jest w stosie)
					}
				}
			}
			element = stos->getFirst();
			stos->pop();
		}
		if (element != wkoncowy) {	//koniec jesli nie ma juz sciezki rozpinajacej
			break;
		}
		else {
			przeplyw += maxprzep[element];	//przeplyw grafu zwieksza sie o przeplyw maksymalny dla sciezki
			teraz = maxprzep[element];
			while (element != wpoczatkowy) {	//do wszystkich elementow na sciezce dodajemy przeplyw uzyskany w iteracji petli while
				naktory = element;
				element = zktorego[element];
				for (List_Element *elem = lista[element]; elem; elem = elem->next) {	//dla wszystkich krawedzi od korzenia
					if ((elem->value) == naktory) {
						(elem->f) += teraz;
						break;
					}
				}
			}
			//powrot zmiennych do stanu poczatkowego - gotowe do kolejnej sciezki
			for (int i = 0; i < w; i++) {
				maxprzep[i] = 0;
				zktorego[i] = -1;
				visited[i] = false;
			}
			element = wpoczatkowy;
			maxprzep[element] = MAXINT;
			while (!(stos->isEmpty())) {
				stos->pop();
			}
			stos->put(element);
		}
	}
	//wyswietlenie wyniku
	//cout << "Wynik listowy: " << endl;
	//cout << "Maksymalny przeplyw: " << przeplyw << endl;

	delete[] maxprzep;
	delete[] zktorego;
	delete[] visited;
}

void Graf::FFMacierzWszerz() {
	int przeplyw = 0;	//przeplyw maksymalny
	int *maxprzep = new int[w];	//maksymalny przeplyw do danego wierzcholka w pojedynczej sciezce
	int *zktorego = new int[w]; //z ktorego wierzcholka prowadzila sciezka
	int **obecnyprzeplyw = new int*[w]; //ilosc juz 'przeplynieta' dla kazdej krawedzi
	for (int i = 0; i < w; i++)
		obecnyprzeplyw[i] = new int[w];
	bool *visited = new bool[w]; //czy wierzcholek juz odwiedzony
	int element = wpoczatkowy;	//wskazuje na aktualny element
	int teraz;	//pomocnicza
	Queue *kolejka = new Queue;	//inicjalizujemy kolejke
	kolejka->put(element);	//wkladamy wierzcholek poczatkowy
	for (int i = 0; i < w; i++) {
		maxprzep[i] = 0;
		zktorego[i] = -1;
		visited[i] = false;
		for (int j = 0; j < w; j++) {
			obecnyprzeplyw[i][j] = 0;
		}
	}
	maxprzep[element] = MAXINT;	//zeby nie blokowal zadnego przeplywu
	visited[element] = true;
	
	while (true) {
		while (!(kolejka->isEmpty()) && element != wkoncowy) {	//petla pojedynczej sciezki przeplywu
			for (int i = 0; i < w; i++) {	//sprawdzamy wszystkie krawedzie z obecnego wierzcholka
				if (macierz[element][i] - obecnyprzeplyw[element][i] > 0) {	//jesli jest jeszcze mozliwy przeplyw
					if (!visited[i]) {	//i wierzcholek docelowy jeszcze jest nieodwiedzony
						kolejka->put(i);	//to klade go na kolejke
						zktorego[i] = element;	//oznaczam przychodze do niego z danego wierzcholka
						maxprzep[i] = min(macierz[element][i] - obecnyprzeplyw[element][i], maxprzep[element]);	//i wyliczam jego maksymalny przeplyw w danej sciezce
						visited[i] = true;	//odwiedzony (bo jest w kolejce)
					}
				}
			}
			kolejka->pop();
			if (kolejka->isEmpty())
				break;
			element = (kolejka->getFirst());

		}
		if (element != wkoncowy) {	//koniec jesli nie ma juz sciezki rozpinajacej
			break;
		}
		else {
			przeplyw += maxprzep[element];	//przeplyw grafu zwieksza sie o przeplyw maksymalny dla sciezki
			teraz = maxprzep[element];
			while (element != wpoczatkowy) {	//do wszystkich elementow na sciezce dodajemy przeplyw uzyskany w iteracji petli while
				obecnyprzeplyw[zktorego[element]][element] += teraz;
				element = zktorego[element];
			}
			//powrot zmiennych do stanu poczatkowego - gotowe do kolejnej sciezki
			for (int i = 0; i < w; i++) {
				maxprzep[i] = 0;
				zktorego[i] = -1;
				visited[i] = false;
			}
			element = wpoczatkowy;
			maxprzep[element] = MAXINT;
			visited[element] = true;
			while (!(kolejka->isEmpty())) {
				kolejka->pop();
			}

			kolejka->put(element);
		}
	}
	//wyswietlenie wyniku
	//cout << "Wynik macierzowy: " << endl;
	//cout << "Maksymalny przeplyw: " << przeplyw << endl;
	for (int i = 0; i < w; i++) {
		delete[] obecnyprzeplyw[i];
	}
	delete[] obecnyprzeplyw;
	delete[] maxprzep;
	delete[] zktorego;
	delete[] visited;
}

void Graf::FFListaWszerz() {
	int przeplyw = 0;	//przeplyw maksymalny
	int *maxprzep = new int[w];	//maksymalny przeplyw do danego wierzcholka w pojedynczej sciezce
	int *zktorego = new int[w]; //z ktorego wierzcholka prowadzila sciezka
	bool *visited = new bool[w]; //czy wierzcholek juz odwiedzony
	int element = wpoczatkowy;	//wskazuje na aktualny element
	int teraz, naktory;	//pomocnicze
	Queue *kolejka = new Queue;	//inicjalizujemy kolejke
	kolejka->put(element);	//wkladamy wierzcholek poczatkowy
	for (int i = 0; i < w; i++) {
		maxprzep[i] = 0;
		zktorego[i] = -1;
		visited[i] = false;
		for (List_Element *elem = lista[i]; elem; elem = elem->next) {	//dla wszystkich krawedzi od korzenia
			(elem->f) = 0;	//zeruje aktualny przeplyw
		}
	}
	maxprzep[element] = MAXINT;	//zeby nie blokowal zadnego przeplywu

	while (true) {
		while (!(kolejka->isEmpty()) && element != wkoncowy) {	//petla pojedynczej sciezki przeplywu
			for (List_Element *elem = lista[element]; elem; elem = elem->next) {	//dla wszystkich krawedzi od korzenia
				if ((elem->dane) - (elem->f) > 0) {	//jesli jest jeszcze mozliwy przeplyw
					if (!visited[(elem->value)]) {	//i wierzcholek docelowy jeszcze jest nieodwiedzony
						kolejka->put((elem->value));	//to klade go na kolejke
						zktorego[(elem->value)] = element;	//oznaczam przychodze do niego z danego wierzcholka
						maxprzep[(elem->value)] = min((elem->dane) - (elem->f), maxprzep[element]);	//i wyliczam jego maksymalny przeplyw w danej sciezce
						visited[(elem->value)] = true;	//odwiedzony (bo jest w kolejce)
					}
				}
			}
			kolejka->pop();
			if (kolejka->isEmpty())
				break;
			element = (kolejka->getFirst());
		}
		if (element != wkoncowy) {	//koniec jesli nie ma juz sciezki rozpinajacej
			break;
		}
		else {
			przeplyw += maxprzep[element];	//przeplyw grafu zwieksza sie o przeplyw maksymalny dla sciezki
			teraz = maxprzep[element];
			while (element != wpoczatkowy) {	//do wszystkich elementow na sciezce dodajemy przeplyw uzyskany w iteracji petli while
				naktory = element;
				element = zktorego[element];
				for (List_Element *elem = lista[element]; elem; elem = elem->next) {	//dla wszystkich krawedzi od korzenia
					if ((elem->value) == naktory) {
						(elem->f) += teraz;
						break;
					}
				}
			}
			//powrot zmiennych do stanu poczatkowego - gotowe do kolejnej sciezki
			for (int i = 0; i < w; i++) {
				maxprzep[i] = 0;
				zktorego[i] = -1;
				visited[i] = false;
			}
			element = wpoczatkowy;
			maxprzep[element] = MAXINT;
			while (!(kolejka->isEmpty())) {
				kolejka->pop();
			}
			kolejka->put(element);
		}
	}
	//wyswietlenie wyniku
	//cout << "Wynik listowy: " << endl;
	//cout << "Maksymalny przeplyw: " << przeplyw << endl;

	delete[] maxprzep;
	delete[] zktorego;
	delete[] visited;
}

void Graf::displayLista(){
	cout << "Wierzcholek poczatkowy: " << wpoczatkowy << endl;
	cout << "Wierzcholek koncowy: " << wkoncowy << endl;
	cout << "Postac listy: " << endl;
	for (int i = 0; i < w; i++){
		cout << "Lista[" << i << "] = ";
		List_Element *nowy = lista[i];
		while (nowy){
			cout << (nowy->value) << "(" << (nowy->dane) << ")" << ' ';
			nowy = (nowy->next);
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::displayMacierz(){
	cout << "Postac macierzowa: " << endl;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			cout << macierz[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int Graf::loadFromFile(string FileName) {
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int omin1, omin2;
	plik >> omin1 >> omin2 >> wpoczatkowy;
	int poczatek, koniec, wartoscc;
	for (int i = 0; i < omin1; i++) {	//odczytuje tyle krawedzi ile podanych na poczatku
		plik >> poczatek >> koniec >> wartoscc;
		macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
		List_Element *nowy = new List_Element;
		(nowy->value) = koniec;
		(nowy->dane) = wartoscc;
		(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
		lista[poczatek] = nowy;
	}
	return 1;
}

int Graf::loadFromFileMST(string FileName) {
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int omin1, omin2;
	plik >> omin1 >> omin2;
	int poczatek, koniec, wartoscc;
	for (int i = 0; i < omin1; i++) {	//odczytuje tyle krawedzi ile podanych na poczatku
		plik >> poczatek >> koniec >> wartoscc;
		if(poczatek<koniec)		 //dodanie krawedzi do macierzy
			macierz[poczatek][koniec] = wartoscc;
		else
			macierz[koniec][poczatek] = wartoscc;
		List_Element *nowy = new List_Element;	//nieskierowane wiec przy liscie dodaje dwa razy
		(nowy->value) = koniec;
		(nowy->dane) = wartoscc;
		(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
		lista[poczatek] = nowy;
		if (poczatek != koniec) {
			List_Element *nowy2 = new List_Element;
			(nowy2->value) = poczatek;
			(nowy2->dane) = wartoscc;
			(nowy2->next) = lista[koniec]; //dodaje element na poczatek listy elementu koniec
			lista[koniec] = nowy2;
		}
	}
	return 1;
}

int Graf::loadFromFilePrzeplyw(string FileName) {
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int omin1, omin2;
	plik >> omin1 >> omin2 >> wpoczatkowy >> wkoncowy;
	int poczatek, koniec, wartoscc;
	for (int i = 0; i < omin1; i++) {	//odczytuje tyle krawedzi ile podanych na poczatku
		plik >> poczatek >> koniec >> wartoscc;
		macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
		List_Element *nowy = new List_Element;
		(nowy->value) = koniec;
		(nowy->dane) = wartoscc;
		(nowy->f) = 0;
		(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
		lista[poczatek] = nowy;
	}
	return 1;
}

void Graf::generateGraf(int lwierzch, int gestosc) {
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	wpoczatkowy = 0;
	int mozliwosci = lwierzch*lwierzch;
	int lkrawedzi = ((float)gestosc / 100.0)*mozliwosci;
	int poczatek, koniec, wartoscc;
	int *tabelalosowa = new int[mozliwosci];
	for (int i = 0; i < mozliwosci; i++) {
		tabelalosowa[i] = 0;
	}
	int randoo;
	for (int i = 0; i < lkrawedzi; i++) {
		if (i < lwierzch - 1) {
			poczatek = i;
			koniec = i + 1;
			wartoscc = rand();
			tabelalosowa[i*lwierzch + i + 1] = 1;
			macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element;
			(nowy->value) = koniec;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
			lista[poczatek] = nowy;
		}
		else {
			randoo = rand() % mozliwosci;
			while(tabelalosowa[randoo]!=0){
				randoo = rand() % mozliwosci;
			}
			tabelalosowa[randoo] = 1;
			poczatek = randoo / lwierzch;
			koniec = randoo % lwierzch;
			wartoscc = rand();
			macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element;
			(nowy->value) = koniec;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
			lista[poczatek] = nowy;
		}
	}
	delete tabelalosowa;
}

void Graf::generateGrafUjemny(int lwierzch, int gestosc) {
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	wpoczatkowy = 0;
	int mozliwosci = lwierzch*lwierzch;
	int lkrawedzi = ((float)gestosc / 100.0)*mozliwosci;
	int poczatek, koniec, wartoscc;
	int *tabelalosowa = new int[mozliwosci];
	for (int i = 0; i < mozliwosci; i++) {
		tabelalosowa[i] = 0;
	}
	int randoo;
	for (int i = 0; i < lkrawedzi; i++) {
		if (i < lwierzch - 1) {
			poczatek = i;
			koniec = i + 1;
			wartoscc = rand()*(-1) ^ rand();
			tabelalosowa[i*lwierzch + i + 1] = 1;
			macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element;
			(nowy->value) = koniec;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
			lista[poczatek] = nowy;
		}
		else {
			randoo = rand() % mozliwosci;
			while (tabelalosowa[randoo] != 0) {
				randoo = rand() % mozliwosci;
			}
			tabelalosowa[randoo] = 1;
			poczatek = randoo / lwierzch;
			koniec = randoo % lwierzch;
			wartoscc = rand()*(-1) ^ rand();
			macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element;
			(nowy->value) = koniec;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[poczatek]; //dodaje element na poczatek listy elementu poczatek
			lista[poczatek] = nowy;
		}
	}
	delete tabelalosowa;
}

void Graf::generateGrafMST(int lwierzch, int gestosc){
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	int mozliwosci = (((lwierzch*lwierzch) - lwierzch) / 2) + lwierzch; //mozliwe dodanie krawedzi nieskierowanych
	int lkrawedzi = ((float)gestosc / 100.0)*mozliwosci;
	int poczatek, koniec, wartoscc;

	int randx, randy;
	for (int i = 0; i < lkrawedzi; i++) {
		if (i < lwierzch - 1) {
			poczatek = i;
			koniec = i + 1;
			wartoscc = rand();
			macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element; //dodaje element do listy dwukrotnie (krawedz nieskierowana)
			(nowy->value) = koniec;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[poczatek];
			lista[poczatek] = nowy;
			if (poczatek != koniec) {
				List_Element *nowy2 = new List_Element;
				(nowy2->value) = poczatek;
				(nowy2->dane) = wartoscc;
				(nowy2->next) = lista[koniec];
				lista[koniec] = nowy2;
			}
		}
		else {
			randx = rand() % lwierzch;
			randy = rand() % lwierzch;
			if (randx > randy) {
				int pomoc = randx;
				randx = randy;
				randy = pomoc;
			}
			while (macierz[randx][randy] != 0) {
				randx = rand() % lwierzch;
				randy = rand() % lwierzch;
				if (randx > randy) {
					int pomoc = randx;
					randx = randy;
					randy = pomoc;
				}
			}
			wartoscc = rand();
			macierz[randx][randy] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element; //dodaje element dwukrotnie (krawedz skierowana)
			(nowy->value) = randx;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[randy];
			lista[randy] = nowy;
			if (randx != randy) {
				List_Element *nowy2 = new List_Element;
				(nowy2->value) = randy;
				(nowy2->dane) = wartoscc;
				(nowy2->next) = lista[randx];
				lista[randx] = nowy2;
			}
		}
	}
}

void Graf::generateGrafPrzeplyw(int lwierzch, int gestosc) {
	//usuwamy istniejaca liste i macierz
	List_Element *elem1;
	List_Element *elem2;
	for (int i = 0; i < w; i++) {
		elem1 = lista[i];
		while (elem1) {
			elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
	}
	delete[] lista;

	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	//koniec usuwania listy i macierzy

	//inicjalizujemy nowa liste i macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	lista = new List_Element *[w];
	for (int i = 0; i < w; i++)
		lista[i] = NULL;
	//koniec inicjalizacji

	int mozliwosci = (((lwierzch*lwierzch) - lwierzch) / 2); //mozliwe dodanie krawedzi nieskierowanych
	int lkrawedzi = ((float)gestosc / 100.0)*mozliwosci;
	int poczatek, koniec, wartoscc;
	wpoczatkowy = 0;
	wkoncowy = lwierzch - 1;

	int randx, randy;
	for (int i = 0; i < lkrawedzi; i++) {
		if (i < lwierzch - 1) {
			poczatek = i;
			koniec = i + 1;
			wartoscc = rand();
			macierz[poczatek][koniec] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element; //dodaje element do listy
			(nowy->value) = koniec;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[poczatek];
			lista[poczatek] = nowy;
		}
		else {
			randx = rand() % lwierzch;
			randy = rand() % lwierzch;
			if (randx > randy) {
				int pomoc = randx;
				randx = randy;
				randy = pomoc;
			}
			while (macierz[randx][randy] != 0 || randx==randy) {
				randx = rand() % lwierzch;
				randy = rand() % lwierzch;
				if (randx > randy) {
					int pomoc = randx;
					randx = randy;
					randy = pomoc;
				}
			}
			wartoscc = rand();
			macierz[randx][randy] = wartoscc; //dodanie krawedzi do macierzy
			List_Element *nowy = new List_Element; //dodaje element do listy
			(nowy->value) = randy;
			(nowy->dane) = wartoscc;
			(nowy->next) = lista[randx];
			lista[randx] = nowy;
		}
	}
}


void displayMenu1(string info) {
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Utworz losowo" << endl;
	cout << "3.Wyswietl" << endl;
	cout << "4.Algorytm Kruskala macierzowo" << endl;
	cout << "5.Algorytm Kruskala lista" << endl;
	cout << "6.Algorytm Prima macierzowo" << endl;
	cout << "7.Algorytm Prima lista" << endl;
	cout << "8.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void displayMenu2(string info) {
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Utworz losowo" << endl;
	cout << "3.Wyswietl" << endl;
	cout << "4.Algorytm Dijkstry macierzowo" << endl;
	cout << "5.Algorytm Dijkstry lista" << endl;
	cout << "6.Algorytm Forda-Bellmana macierzowo" << endl;
	cout << "7.Algorytm Forda-Bellmana lista" << endl;
	cout << "8.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void displayMenu3(string info) {
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Utworz losowo" << endl;
	cout << "3.Wyswietl" << endl;
	cout << "4.Algorytm Forda-Fulkersona macierzowo w glab" << endl;
	cout << "5.Algorytm Forda-Fulkersona lista w glab" << endl;
	cout << "6.Algorytm Forda-Fulkersona macierzowo wszerz " << endl;
	cout << "7.Algorytm Forda-Fulkersona lista wszerz" << endl;
	cout << "8.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void menu_MST() {
	Graf *mojGraf = new Graf(0, 0);
	ifstream plik;
	TimeCounter counter;
	int n, m; //n-wierzcholki, m-krawedzie
	int gestosc;
	char opt;
	string fileName;
	double counterr = 0;
	int x = 1000;	//ilosc generacji danych
	int y = 1000;	//dlugosc wygenerowanej listy

	do {
		displayMenu1("--- Najkrotsza sciezka ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie grafu z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;

			plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
			if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
				plik.close();
				break;
			}
			cout << "ok";
			plik >> m >> n;
			mojGraf = new Graf(n, m);

			mojGraf->loadFromFileMST(fileName);
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			plik.close();
			break;

		case '2':  //tutaj generowanie grafu
			cout << "Podaj liczbe wierzcholkow:";
			cin >> n;
			cout << "Podaj gestosc:";
			cin >> gestosc;

			mojGraf = new Graf(n, ((float)gestosc / 100.0)*(n*n));

			mojGraf->generateGrafMST(n, gestosc);
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			break;

		case '3':  //tutaj wyœwietlanie grafu
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			break;

		case '4':  //algorytm Kruskala macierzowo
			mojGraf->KruskalMacierz();
			break;

		case '5':  //algorytm Kruskala lista
			mojGraf->KruskalLista();
			break;

		case '6':  //algorytm Prima macierzowo
			mojGraf->PrimMacierz();
			break;

		case '7':  //algorytm Prima lista
			mojGraf->PrimLista();
			break;
		case '8':
			counterr = 0;
			int xx, yy, zz;	//zmienne do mierzenia czasu(xx-l. wierzcholkow, yy-gestosc, zz-ilosc losowan populacji(grafow)
			xx = 20;
			yy = 25;
			zz = 100;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;


			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 40;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 60;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 80;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 100;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalMacierz();
				counterr += counter.GetCounter();
			}
			cout << "KruskalMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->KruskalLista();
				counterr += counter.GetCounter();
			}
			cout << "KruskalLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimMacierz();
				counterr += counter.GetCounter();
			}
			cout << "PrimMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->PrimLista();
				counterr += counter.GetCounter();
			}
			cout << "PrimLista " << (double)counterr / zz << endl;
			break;
		}

	} while (opt != '0');
}

void menu_sciezka() {
	Graf *mojGraf=new Graf(0,0);
	ifstream plik;
	TimeCounter counter;
	int n, m; //n-wierzcholki, m-krawedzie
	int gestosc;
	char opt;
	string fileName;
	double counterr = 0;
	int x = 1000;	//ilosc generacji danych
	int y = 1000;	//dlugosc wygenerowanej listy
	bool ujemne;

	do {
		displayMenu2("--- Najkrotsza sciezka ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie grafu z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;

			plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
			if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
				plik.close();
				break;
			}
			cout << "ok";
			plik >> m >> n;
			mojGraf = new Graf(n, m);

			mojGraf->loadFromFile(fileName);
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			plik.close();
			break;

		case '2':  //tutaj generowanie grafu
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> n;
			cout << "Podaj gestosc: ";
			cin >> gestosc;
			cout << "Podaj czy maja byc wartosci ujemne(1/0) 1-tak, 0-nie: ";
			cin >> ujemne;
			mojGraf = new Graf(n, ((float)gestosc / 100.0)*(n*n));
			if (ujemne)
				mojGraf->generateGrafUjemny(n, gestosc);
			else
				mojGraf->generateGraf(n, gestosc);
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			break;

		case '3':  //tutaj wyœwietlanie grafu
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			break;

		case '4':  //algorytm Dijkstry macierzowo
			mojGraf->DijkstraMacierz();
			break;

		case '5':  //algorytm Dijkstry lista
			mojGraf->DijkstraLista();
			break;

		case '6':  //algorytm Forda-Bellmana macierzowo
			mojGraf->FBMacierz();
			break;

		case '7':  //algorytm Forda-Bellmana lista
			mojGraf->FBLista();
			break;

		case '8':
			counterr = 0;
			int xx, yy, zz;	//zmienne do mierzenia czasu(xx-l. wierzcholkow, yy-gestosc, zz-ilosc losowan populacji(grafow)
			xx = 20;
			yy = 25;
			zz = 100;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;


			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 40;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 60;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 80;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 100;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraMacierz();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->DijkstraLista();
				counterr += counter.GetCounter();
			}
			cout << "DijkstraLista " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBMacierz();
				counterr += counter.GetCounter();
			}
			cout << "FBMacierz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGraf(xx, yy);
				counter.StartCounter();
				mojGraf->FBLista();
				counterr += counter.GetCounter();
			}
			cout << "FBLista " << (double)counterr / zz << endl;
			break;
		}
	} while (opt != '0');
}

void menu_przeplyw() {
	Graf *mojGraf = new Graf(0, 0);
	ifstream plik;
	TimeCounter counter;
	int n, m; //n-wierzcholki, m-krawedzie
	int gestosc;
	char opt;
	string fileName;
	double counterr = 0;
	int x = 1000;	//ilosc generacji danych
	int y = 1000;	//dlugosc wygenerowanej listy

	do {
		displayMenu3("--- Najkrotsza sciezka ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie grafu z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;

			plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
			if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
				plik.close();
				break;
			}
			cout << "ok";
			plik >> m >> n;
			mojGraf = new Graf(n, m);

			mojGraf->loadFromFilePrzeplyw(fileName);
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			plik.close();
			break;

		case '2':  //tutaj generowanie grafu
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> n;
			cout << "Podaj gestosc: ";
			cin >> gestosc;
			mojGraf = new Graf(n, ((float)gestosc / 100.0)*(n*n));
			mojGraf->generateGrafPrzeplyw(n, gestosc);
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			break;

		case '3':  //tutaj wyœwietlanie grafu
			mojGraf->displayMacierz();
			mojGraf->displayLista();
			break;

		case '4':  //algorytm Dijkstry macierzowo
			mojGraf->FFMacierzWglab();
			break;

		case '5':  //algorytm Dijkstry lista
			mojGraf->FFListaWglab();
			break;

		case '6':  //algorytm Forda-Bellmana macierzowo
			mojGraf->FFMacierzWszerz();
			break;

		case '7':  //algorytm Forda-Bellmana lista
			mojGraf->FFListaWszerz();
			break;

		case '8':
			counterr = 0;
			int xx, yy, zz;	//zmienne do mierzenia czasu(xx-l. wierzcholkow, yy-gestosc, zz-ilosc losowan populacji(grafow)
			xx = 20;
			yy = 25;
			zz = 100;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;


			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 40;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 60;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 80;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			xx = 100;
			yy = 25;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			y = 50;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 75;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;

			counterr = 0;
			yy = 99;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWglab();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWglab " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFMacierzWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFMacierzWszerz " << (double)counterr / zz << endl;
			counterr = 0;
			mojGraf = new Graf(xx, ((float)yy / 100.0)*(xx*xx));
			for (int i = 0; i < zz; i++) {
				mojGraf->generateGrafPrzeplyw(xx, yy);
				counter.StartCounter();
				mojGraf->FFListaWszerz();
				counterr += counter.GetCounter();
			}
			cout << "FFListaWszerz " << (double)counterr / zz << endl;
			break;
		}
	} while (opt != '0');
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Minimalne drzewo rozpinajace" << endl;
		cout << "2.Najkrotsza sciezka w grafie" << endl;
		cout << "3.Maksymalny przeplyw" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			menu_MST();
			break;

		case '2':
			menu_sciezka();
			break;
		
		case '3':
			menu_przeplyw();
			break;

		}

	} while (option != '0');

	system("pause");
	return 0;
}