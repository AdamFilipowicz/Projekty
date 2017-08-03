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

void TimeCounter::StartCounter(){
	LARGE_INTEGER li;	//64bitowa unia(jedno miejsce w pamiêci dla paru obiektów ró¿nego typu)
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart);	//QuadPart to znakowany 64bitowy int z LARGE_INTEGER

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double TimeCounter::GetCounter(){
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}



class Table{
	int *tab = NULL;
	int cnt=0; //iloœæ elementów w tablicy

	public:

		~Table();

		int loadFromFile(string FileName);

		bool isValueInTable(int val);

		void addValue(int index, int value);

		void deleteFromTable(int index);

		void display();

		void generateTable(int size);

};

Table::~Table() {
	if (tab != NULL) {	//jeœli tablica istnieje
		delete[]tab;	//to j¹ usuwam
	}
}

int Table::loadFromFile(string FileName) {
	if (tab != NULL) {	//jeœli tablica istnieje
		delete[]tab;	//to j¹ usuwam
	}
	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	plik >> cnt;	//odczytuje liczbe liczb
	tab = new int[cnt];
	for (int i = 0; i < cnt; i++) {	//odczytuje liczby
		plik >> tab[i];
	}
	return 1;
}

bool Table::isValueInTable(int val) {
	if (tab != NULL) {	//jeœli tablica nie istnieje
		for (int i = 0; i < cnt; i++) {	//jesli jakas z wartosci w tablicy jest rowna podanej zwracam true
			if (tab[i] == val) {
				return true;
			}
		}
	}
	return false;
}

void Table::addValue(int index, int value) {
	if (tab != NULL) {	//jeœli tablica nie istnieje
		int *tab2;	//deklaruje nowa tablice
		if (index > cnt) {	//przypadek gdy podamy index wykraczajacy za rozmiar talicy
			//nowa tablica o rozmiarze index+1 wypelnia sie poprzedni¹ i zerami oraz podana wartoscia
			tab2 = new int[index + 1];
			for (int i = 0; i < cnt; i++) {
				tab2[i] = tab[i];
			}
			for (int i = cnt; i < index; i++) {
				tab2[i] = 0;
			}
			tab2[index] = value;
			cnt = index + 1;
		}
		else {	//przypadek gdy chcemy wsadzic element 'w œrodek' tablicy
			//nowa tablica o rozmiarze wiekszym o 1 wypelnia sie poprzednia do podanego indexu, 
			//nastepnie podana wartoscia i kolejnymi wartosciami z poprzedniej tablicy
			tab2 = new int[cnt + 1];
			for (int i = 0; i < index; i++) {
				tab2[i] = tab[i];
			}
			tab2[index] = value;
			for (int i = index; i < cnt + 1; i++) {
				tab2[i + 1] = tab[i];
			}
			cnt++;
		}
		delete[]tab;	//zwalniamy pamiec
		tab = tab2;		//nowy wskaznik tablicy
	}
}

void Table::deleteFromTable(int index) {
	if (tab != NULL) {	//jeœli tablica istnieje
		if (index < cnt && index >= 0) {	//usuwanie dziala tylko gdy podany index jest mniejszy niz rozmiar tablicy i dodatni
			int *tab2 = new int[cnt - 1];	//inicjalizacja tablicy o 1 pozycje mniejsza
			//nowa tablica wypelnia sie wartosciami oprocz wartosci na podanym indexie
			for (int i = 0; i < index; i++) {
				tab2[i] = tab[i];
			}
			for (int i = index; i < cnt - 1; i++) {
				tab2[i] = tab[i + 1];
			}
			delete[]tab;	//zwalniamy pamiec
			tab = tab2;		//nowy wskaznik tablicy
			cnt--;
		}
		else {
			cout << "Podaj poprawny index!\n";
		}
	}
}

void Table::display() {
	if (tab == NULL) {	//jeœli tablica nie istnieje
		cout << "Najpierw utworz tablice!\n";
	}
	else {
		for (int i = 0; i < cnt; i++) {	//wszystkie wartosci w tablicy podzielone przerwami
			cout << tab[i] << " ";
		}
	}
}

void Table::generateTable(int size) {
	if (tab != NULL) {	//jeœli tablica istnieje
		delete[]tab;	//to j¹ usuwam
	}
	cnt = size;
	tab = new int[cnt];
	for (int i = 0; i < cnt; i++) {	//wszystkie wartosci w tablicy wygenerowane losowo od 0 do RAND_MAX
		tab[i] = rand();
	}
}



struct List_Element {	//struktura jako element listy
	int value;	//wartosc elementu
	List_Element* next;	//wskaznik na nastepny element
	List_Element* prev;	//wskaznik na poprzedni element
};

class List {
	List_Element* first=NULL;	//wskaznik na pierwszy element listy
	List_Element* last=NULL;	//wskaznik na ostatni element listy

	public:

		~List();

		int loadFromFile(string FileName);

		bool isValueInList(int val);

		void addValue(int index, int value);

		void addFirst(int value);

		void addLast(int value);

		bool deleteFromList(int index);

		void deleteFirst();

		void deleteLast();

		void display();

		void generateList(int size);

		int getValue(int index);
};

List::~List() {
	while (first != NULL) {	//lista usuwa siê od pierwszego elementu
		last = first->next;
		delete  first;
		first = last;
	};
}

int List::loadFromFile(string FileName) {
	while (first != NULL) {	//lista usuwa siê od pierwszego elementu
		last = first->next;
		delete  first;
		first = last;
	};
	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int liczbaLiczb;
	plik >> liczbaLiczb;
	for (int i = 0; i < liczbaLiczb; i++) {	//odczytuje liczby i kazda dodaje na koniec listy
		List_Element *nowy = new List_Element;
		if (i == 0) {	//pierwszy element dodawany inaczej niz reszta (bo last=NULL) i sam staje siê first i last
			(nowy->next) = NULL;
			(nowy->prev) = NULL;
			plik >> (nowy->value);
			first = nowy;
			last = nowy;
		}
		else {
			(nowy->next) = NULL;
			(nowy->prev) = last;
			plik >> (nowy->value);
			(last->next) = nowy;
			last = (last->next);
		}
	}
	return 1;
}

bool List::isValueInList(int val) {
	List_Element *sprawdzacz = first;
	while (sprawdzacz != NULL) {	//element zaczynaj¹c od first sprawdza swoj¹ wartoœæ dopóki nie wyjdzie poza last
		if ((sprawdzacz->value) == val) {
			return true;
		}
		sprawdzacz = (sprawdzacz->next);
	}
	return false;
}

void List::addValue(int indexx, int valuee) {
	int index = 0;
	//element jest dodany tylko jeœli nic nie ma w tablicy i index jest=0
	List_Element *nowy = new List_Element;	//dodawany element
	if (indexx == 0) {
		if (first == NULL) {	//przypadek gdy lista jest pusta
			(nowy->next) = NULL;
			(nowy->prev) = NULL;
			(nowy->value) = valuee;
			first = nowy;
			last = nowy;
		}
		else {	//przypadek gdy coœ jest ju¿ w liœcie
			(nowy->next) = first;
			(nowy->prev) = NULL;
			(nowy->value) = valuee;
			(first->prev) = nowy;
			first = (first->prev);
		}
		return;
	}
	//jeœli nie, szukamy podanego indexu licznikiem
	List_Element *poprzedni = NULL;//tworzymy elementy które w pêtli znajd¹ pozycje pomiêdzy dodawanym elementem
	List_Element *szukajacy = first;
	while (szukajacy != NULL) {
		poprzedni = szukajacy;
		szukajacy = (szukajacy->next);
		index++;
		if (index == indexx)
			break;
	}
	if (poprzedni == last) {//1 przypadek: dodajemy na koniec listy
		(nowy->next) = NULL;
		(nowy->prev) = last;
		(nowy->value) = valuee;
		(last->next) = nowy;
		last = (last->next);
	}
	else {//2 przypadek: dodajemy w srodek listy
		(nowy->next) = szukajacy;
		(nowy->prev) = poprzedni;
		(nowy->value) = valuee;
		(szukajacy->prev) = nowy;
		(poprzedni->next) = nowy;
	}
}

void List::addFirst(int val) {
	//funkcja u¿ywana do testów: dodanie na pierwsz¹ pozycjê
	List_Element *nowy = new List_Element;
	(nowy->next) = first;
	(nowy->prev) = NULL;
	(nowy->value) = val;
	(first->prev) = nowy;
	first = (first->prev);
}

void List::addLast(int val) {
	//funkcja u¿ywana do testów: dodanie na ostatni¹ pozycjê
	List_Element *nowy = new List_Element;
	(nowy->next) = NULL;
	(nowy->prev) = last;
	(nowy->value) = val;
	(last->next) = nowy;
	last = (last->next);
}

bool List::deleteFromList(int val) {
	List_Element *sprawdzacz = first;
	while (sprawdzacz != NULL) {	//element zaczyna od first podobnie jak przy szukaniu wartosci
		if ((sprawdzacz->value) == val) {	//jesli znajde zadana wartosc to usuwam ja w ktoryms przypadku i return true
			if (sprawdzacz == first) {
				if (first == last) { //1 przypadek szukany element jest pierwszy i ostatni
					delete sprawdzacz;
					first = NULL;
					last = NULL;
					return true;
				}
				else {	//2 przypadek szukany element jest pierwszy i nie ostatni
					sprawdzacz = (sprawdzacz->next);
					delete (sprawdzacz->prev);
					(sprawdzacz->prev) = NULL;
					first = sprawdzacz;
				}
			}
			else if (sprawdzacz == last) {	//3 przypadek szukany element jest ostatni i nie pierwszy
				last = (sprawdzacz->prev);
				(last->next) = NULL;
				delete sprawdzacz;
				return true;
			}
			else {	//4 przypadek szukany element jest w srodku tablicy
				//tworze pomocniczy element ktory usune bo nic juz nie bedzie na niego wskazywalo 
				//po przeniesieniu sprawdzacza
				List_Element *pomocniczy = sprawdzacz;
				((sprawdzacz->prev)->next) = (sprawdzacz->next);
				((sprawdzacz->next)->prev) = (sprawdzacz->prev);
				sprawdzacz = (sprawdzacz->next);
				delete pomocniczy;
			}
			return true;
		}
		sprawdzacz = (sprawdzacz->next);
	}
	cout << "Podanej wartosci nie ma w liscie\n";
	return false;
}

void List::deleteFirst() {
	//funkcja u¿ywana do testów: usuniêcie z pierwszej pozycji
	first = (first->next);
	delete (first->prev);
	(first->prev) = NULL;
}

void List::deleteLast() {
	//funkcja u¿ywana do testów: usuniêcie z ostatniej pozycji
	last = (last->prev);
	delete (last->next);
	(last->next) = NULL;
}

void List::display() {//wyœwietlamy wartoœæ ka¿dego elementu od pocz¹tku do koñca
	List_Element *szukajacy = first;
	while (szukajacy != NULL) {
		cout << szukajacy->value << " ";
		szukajacy = (szukajacy->next);
	}
	cout << "\n";//i od koñca do pocz¹tku
	szukajacy = last;
	while (szukajacy != NULL) {
		cout << szukajacy->value << " ";
		szukajacy = (szukajacy->prev);
	}
}

void List::generateList(int size) {
	while (first != NULL) {	//lista usuwa siê od pierwszego elementu
		last = first->next;
		delete  first;
		first = last;
	};
	for (int i = 0; i < size; i++) {	//generowanie jak w loadFromFile tylko losowane wartoœci rand()
		List_Element *nowy = new List_Element;
		if (i == 0) {	//pierwszy element dodawany inaczej niz reszta (bo last=NULL) i sam staje siê first i last
			(nowy->next) = NULL;
			(nowy->prev) = NULL;
			(nowy->value) = rand();
			first = nowy;
			last = nowy;
		}
		else {
			(nowy->next) = NULL;
			(nowy->prev) = last;
			(nowy->value) = rand();
			(last->next) = nowy;
			last = (last->next);
		}
	}
}

int List::getValue(int indexx) {	//funkcja u¿ywana przy testach: zwraca wartoœæ dla podanego indexu
	int index = 0;
	List_Element *sprawdzacz = first;
	while (sprawdzacz != NULL) {	//element zaczynaj¹c od first sprawdza swoj¹ wartoœæ dopóki nie wyjdzie poza last
		if (index == indexx) {
			return (sprawdzacz->value);
		}
		sprawdzacz = (sprawdzacz->next);
		index++;
	}
	return 0;
}



class Heap {
	int *heap = NULL;
	int size = 20002; //maksymalna wielkosc kopca
	int cnt=0;

public:

	~Heap();

	int loadFromFile(string FileName);

	bool isValueInHeap(int val);

	void addValue(int value);

	bool deleteFromHeap(int index);

	void deleteFirst();

	void display();

	void generateHeap(int size);

	int getValue(int index);

};

Heap::~Heap() {
	if (heap != NULL) {	//jeœli kopiec istnieje
		delete[]heap;	//to go usuwam
	}
}

int Heap::loadFromFile(string FileName) {
	if (heap != NULL) {	//jeœli kopiec istnieje
		delete[]heap;	//to go usuwam
	}
	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int tempcnt;
	plik >> tempcnt;	//odczytuje liczbe liczb
	cnt = 0;
	heap = new int[size];
	int wartosc;
	for (int i = 0; i < tempcnt; i++) {	//odczytuje liczby
		plik >> wartosc;
		addValue(wartosc);	//funkcja addValue dla kazdej liczby z osobna
	}
	return 1;
}

bool Heap::isValueInHeap(int val) {
	if (heap == NULL) {
		heap = new int[size];
	}
	if (val > heap[0])	//jesli wartosc jest wieksza niz max zwracamy false
		return false;
	for (int i = 0; i < cnt; i++) {	//jesli jakas z wartosci w tablicy jest rowna podanej zwracam true
		if (heap[i] == val) {
			return true;
		}
	}
	return false;
}

void Heap::addValue(int value) {
	if (heap == NULL) {
		heap = new int[size];
	}
	heap[cnt] = value;	//dodajemy na najnizszy element
	int miejsce = cnt;	//pomocnicza zmienna wskazujaca na aktualna pozycje dodanego elementu
	//petla dopoki nie dotarlismy na szczyt kopca i dopoki rodzic jest mniejszy od dodawanego elementu
	while (miejsce != 0 && heap[miejsce] > heap[(int)floor((miejsce - 1) / 2)]) {
		int pomocnicze = heap[miejsce];	//zamieniamy ta liczbe i rodzica
		heap[miejsce] = heap[(int)floor((miejsce - 1) / 2)];
		heap[(int)floor((miejsce - 1) / 2)] = pomocnicze;
		miejsce = (int)floor((miejsce - 1) / 2);	//i miejsce wskazuje nadal na dodawany element
	}
	cnt++;	//zwiekszenie liczby elementow kopca
}

bool Heap::deleteFromHeap(int value) {
	if (heap == NULL) {
		heap = new int[size];
	}
	//szukamy elementu o podanej wartosci
	int wskaznik = -1;
	if (value > heap[0])
		return false;
	for (int i = 0; i < cnt; i++) {
		if (value == heap[i]) {
			wskaznik = i;
			break;
		}
	}
	if (wskaznik == -1) {
		return false;
	}
	else if (wskaznik == cnt - 1) {
		heap[wskaznik] = NULL;
		cnt--;
		return true;
	}
	heap[wskaznik] = heap[cnt-1];	//zamieniamy element przeznaczony do usuniecia tym z konca kopca
	heap[cnt-1] = NULL;	//usuwamy ostatni element
	cnt--;	//zmniejszenie liczby elementow kopca
	while (wskaznik != 0 && heap[wskaznik] > heap[(int)floor((wskaznik - 1) / 2)]) {
		cout << "jestem" << endl;
		int pomocnicze = heap[wskaznik];	//zamieniamy ta liczbe i rodzica
		heap[wskaznik] = heap[(int)floor((wskaznik - 1) / 2)];
		heap[(int)floor((wskaznik - 1) / 2)] = pomocnicze;
		wskaznik = (int)floor((wskaznik - 1) / 2);	//i miejsce wskazuje nadal na dodawany element
	}
	int syn = wskaznik*2+1;	//wskazuje lewego syna
	while (syn < cnt-1) {	//dopoki istnieje syn
		if (syn + 1 < cnt-1 && heap[syn + 1] > heap[syn]) {	//sprawdzamy ktory syn jest wiekszy
			syn++;
		}
		if (heap[wskaznik] > heap[syn]) {	//jesli syn jest mniejszy niz liczba koniec petli
			break;
		}
		int pomocnicze = heap[wskaznik];	//zamieniamy liczbe i wiekszego syna
		heap[wskaznik] = heap[syn];
		heap[syn] = pomocnicze;
		wskaznik = syn;	//idziemy poziom w dó³
		syn = 2 * syn + 1;
	}
	return true;
}

void Heap::deleteFirst() {
	//funkcja do testów: usuwanie korzenia
	int wskaznik = 0;
	heap[wskaznik] = heap[cnt - 1];	//zamieniamy element przeznaczony do usuniecia tym z konca kopca
	heap[cnt - 1] = NULL;	//usuwamy ostatni element
	cnt--;	//zmniejszenie liczby elementow kopca
	int syn = wskaznik * 2 + 1;	//wskazuje lewego syna
	while (syn < cnt - 1) {	//dopoki istnieje syn
		if (syn + 1 < cnt - 1 && heap[syn + 1] > heap[syn]) {	//sprawdzamy ktory syn jest wiekszy
			syn++;
		}
		if (heap[wskaznik] > heap[syn]) {	//jesli syn jest mniejszy niz liczba koniec petli
			break;
		}
		int pomocnicze = heap[wskaznik];	//zamieniamy liczbe i wiekszego syna
		heap[wskaznik] = heap[syn];
		heap[syn] = pomocnicze;
		wskaznik = syn;	//idziemy poziom w dó³
		syn = 2 * syn + 1;
	}
	return;
}

void Heap::display() {
	if (heap == NULL) {
		heap = new int[size];
	}
	if (cnt == 0)
		return;
	//w³asna funkcja. generalne dzia³anie: przeznaczenie na ka¿d¹ liczbê 10 miejsc i przerwa miêdzy liczbami 2 spacje
	//wyswietlanie poziomami i próba wyœrodkowania liczb ¿eby uwidoczniæ (przynajmniej na pocz¹tkowych poziomach)
	//rodziców i potomków
	int liczbapoziomow = 1;
	int copycnt = cnt;
	int liczbakrateknajnizej;
	int liczbakrateknapoziomie;
	while (copycnt != 1) {
		liczbapoziomow++;
		copycnt /= 2;
	}
	liczbakrateknajnizej = (int)pow(2, liczbapoziomow - 1) * 10 + ((int)pow(2, liczbapoziomow - 1) - 1) * 2;
	for (int i = 0; i < liczbapoziomow; i++) {
		liczbakrateknapoziomie = (int)pow(2, i) * 10 + ((int)pow(2, i) - 1) * 2;
		for (int j = 0; j < (liczbakrateknajnizej - liczbakrateknapoziomie) / 2; j++){
			cout << " ";
		}
		for (int j = 0; j < (int)pow(2, i); j++) {
			if (cnt >= (int)pow(2, i) + j) {
				cout.width(10);
				cout << internal << heap[(int)pow(2, i) + j - 1] << "   ";
			}
			else {
				cout << "     (0)    ";
			}
		}
		cout << "\n";
	}

	for (int i = 0; i < cnt; i++) {
		cout << heap[i] << " ";
	}
	cout << endl;
}

void Heap::generateHeap(int sizee) {
	if (heap != NULL) {	//jeœli kopiec istnieje
		delete[]heap;	//to go usuwam
	}
	cnt = 0;
	heap = new int[size];
	for (int i = 0; i < sizee; i++) {	//wszystkie wartosci w kopcu wygenerowane losowo od 0 do RAND_MAX
		addValue(rand());	//i dodane funkcja addValue
	}
}

int Heap::getValue(int index){
	return heap[index];
}



struct BST_Element {	//struktura jako element drzewa
	int value;		//wartosc elementu
	BST_Element* parent;//wskaznik na rodzica
	BST_Element* left;	//wskaznik na lewy element
	BST_Element* right;	//wskaznik na prawy element
};

class BST {
	BST_Element* korzen = NULL;	//wskaznik na pierwszy element drzewa

public:

	~BST();

	void destruktor(BST_Element *element);

	int loadFromFile(string FileName);

	bool isValueInBST(int val);

	void addValue(int value);

	bool deleteFromBST(int value);

	void display();

	void generateBST(int size);

	int glebokosc(BST_Element *element);

	void kolejka(int *queue, BST_Element *korzenn, int index);

	void rotLewo(BST_Element *rotowany);

	void rotPrawo(BST_Element *rotowany);

	void DSW();
}; 

BST::~BST() {
	destruktor(korzen);
}

void BST::destruktor(BST_Element *korzenn) {
	//Rekurencyjna funkcja podobna do wyswietlenia drzewa. Funkcja usuwa kazdy element drzewa.
	if (korzenn == NULL)
		return;

	destruktor(korzenn->left);
	destruktor(korzenn->right);

	delete korzenn;
}

int BST::loadFromFile(string FileName) {
	if (korzen != NULL) {	//jeœli drzewo istnieje
		destruktor(korzen);	//to je usuwam
		korzen = NULL;
	}
	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nazwe pliku
		return 0;
	int tempcnt;
	plik >> tempcnt;	//odczytuje liczbe liczb
	int wartosc;
	for (int i = 0; i < tempcnt; i++) {	//odczytuje liczby
		plik >> wartosc;
		addValue(wartosc);	//funkcja addValue dla kazdej liczby z osobna
	}
	return 1;
}

bool BST::isValueInBST(int valuee) {
	BST_Element *temp = korzen;
	BST_Element *prev = temp;	//prev to bêdzie poprzednia wartoœæ temp
	if (korzen == NULL) {	//przypadek gdy nie ma niczego w drzewie
		return false;
	}
	while (true) {
		//w pêtli przechodzimy coraz nizej sprawdzajac wartosci na kazdym poziomie, a¿ temp==NULL.
		if (valuee == (temp->value)) {
			return true;
		}
		if (valuee < (temp->value)) {	//gdy wartosc podana jest mniejsza idziemy w lewo
			prev = temp;
			temp = (temp->left);
			if (temp == NULL) {
				return false;
			}
		}
		else {	//gdy wartosc podana jest wieksza idziemy w prawo
			prev = temp;
			temp = (temp->right);
			if (temp == NULL) {
				return false;
			}
		}
	}
}

void BST::addValue(int valuee) {
	BST_Element *temp = korzen;
	BST_Element *prev = temp;	//prev to bêdzie poprzednia wartoœæ temp
	if (korzen == NULL) {	//przypadek gdy nie ma niczego w drzewie
		BST_Element *dodaj = new BST_Element;
		(dodaj->left) = NULL;
		(dodaj->right) = NULL;
		(dodaj->parent) = NULL;
		(dodaj->value) = valuee;
		korzen = dodaj;
		return;
	}
	while (true) {	
		//w pêtli przechodzimy na sam dó³ dopóki temp==NULL. Wtedy prev pokazuje rodzica i podczepiamy nowy element.
		if (valuee < (temp->value)) {	//gdy wartosc podana jest mniejsza idziemy w lewo
			prev = temp;
			temp = (temp->left);
			if (temp == NULL) {
				BST_Element *dodaj = new BST_Element;
				(dodaj->left) = NULL;
				(dodaj->right) = NULL;
				(dodaj->parent) = prev;
				(dodaj->value) = valuee;
				(prev->left) = dodaj;
				return;
			}
		}
		else {	//gdy wartosc podana jest wieksza idziemy w prawo
			prev = temp;
			temp = (temp->right);
			if (temp == NULL) {
				BST_Element *dodaj = new BST_Element;
				(dodaj->left) = NULL;
				(dodaj->right) = NULL;
				(dodaj->parent) = prev;
				(dodaj->value) = valuee;
				(prev->right) = dodaj;
				return;
			}
		}
	}
}

bool BST::deleteFromBST(int valuee) {
	BST_Element *temp = korzen;
	BST_Element *prev = temp;	//prev to bêdzie poprzednia wartoœæ temp
	if (korzen == NULL) {	//przypadek gdy nie ma niczego w drzewie
		return false;
	}
	while (true) {
		//w pêtli przechodzimy coraz nizej sprawdzajac wartosci na kazdym poziomie, a¿ temp==NULL.
		if (valuee == (temp->value)) {	//jesli znaleŸliœmy wartoœæ do usuniêcia
			if ((temp->left) == NULL && (temp->right) == NULL) {	//1 przypadek gdy nie ma dzieci
				if (prev != temp) {	//jesli nie pierwszy element
					if ((prev->value) > (temp->value)) {
						(prev->left) = NULL;
					}
					else {
						(prev->right) = NULL;
					}
				}
				else {
					korzen = NULL;	//jesli pierwszy element to korzen=NULL
				}
				delete temp;
			}
			else if ((temp->left) != NULL && (temp->right) != NULL) {	//2 przypadek gdy istnieja obaj synowie
				BST_Element *nastepnik = (temp->right);	//szukany nastepnik
				BST_Element *prev2 = nastepnik;
				BST_Element *nastpar=NULL;	//faktyczny ojciec nastepnika
				while ((nastepnik->left)!=NULL) {	//zje¿d¿amy w dó³ po lewych synach nastêpnika
					prev2 = nastepnik;
					nastepnik = (nastepnik->left);
				}
				//szczególny przypadek gdy istnieje prawy syn nastêpnika(trzeba go podpi¹æ pod ojca nastêpnika)
				if ((nastepnik->right) != NULL) {	
					BST_Element *syn = (nastepnik->right);
					if (prev2 != nastepnik) {
						if ((prev2->value) > (nastepnik->value)) {
							(prev2->left) = syn;
						}
						else {
							(prev2->right) = syn;
						}
						(syn->parent) = prev2;
					}
					else {
						BST_Element *dziadek = (nastepnik->parent);	//ojciec nastepnika
						if ((dziadek->value) > (nastepnik->value)) {
							(dziadek->left) = syn;
						}
						else {
							(dziadek->right) = syn;
						}
						(syn->parent) = dziadek;
					}
				}
				else {	//gdy nie istnieje prawy syn nastepnika musimy znullowaæ miejsce po nim
					nastpar = (nastepnik->parent);
					if ((nastpar->value) > (nastepnik->value)) {
						(nastpar->left) = NULL;
					}
					else {
						(nastpar->right) = NULL;
					}
				}
				//nastêpnie przestawiamy wskaŸniki obu synów liczby któr¹ usuwamy
				BST_Element *syno = (temp->left);
				(syno->parent) = nastepnik;
				if (temp != nastpar) {	//prawy syn tylko jeœli liczba któr¹ usuwamy nie jest ojcem nastêpnika (inaczej ju¿ by³ usuniêty)
					BST_Element *syno2 = (temp->right);
					(syno2->parent) = nastepnik;
				}
				if (prev != temp) {	//gdy usuwamy nie korzeñ
					if ((prev->value) > (temp->value)) {
						(prev->left) = nastepnik;
					}
					else {
						(prev->right) = nastepnik;
					}
					(nastepnik->parent) = prev;
				}
				else {	//gdy usuwamy korzeñ
					(nastepnik->parent) = NULL;
					korzen = nastepnik;
				}
				//przestawienie wskaŸników synów nastêpnika
				(nastepnik->left) = (temp->left);
				(nastepnik->right) = (temp->right);
				delete temp;
			}
			else {	//3 przypadek gdy istnieje tylko jeden z synów
				BST_Element *syn;
				if ((temp->left) != NULL) {
					syn = (temp->left);
				}
				else {
					syn = (temp->right);
				}
				if (prev != temp) {	//gdy nie usuwamy korzenia po prostu ustawiamy syna na dziadka i odwrotnie
					if ((prev->value) > (temp->value)) {
						(prev->left) = syn;
					}
					else {
						(prev->right) = syn;
					}
					(syn->parent) = prev;
				}
				else {	//gdy usuwamy korzeñ
					(syn->parent) = NULL;
					korzen = syn;
				}
				delete temp;
			}
			return true;
		}
		if (valuee < (temp->value)) {	//gdy wartosc podana jest mniejsza idziemy w lewo
			prev = temp;
			temp = (temp->left);
			if (temp == NULL) {
				return false;
			}
		}
		else {	//gdy wartosc podana jest wieksza idziemy w prawo
			prev = temp;
			temp = (temp->right);
			if (temp == NULL) {
				return false;
			}
		}

	}
}

void BST::display() {
	//Po³¹czenie w³asnej funkcji z kopca z funkcjami "gotowymi".
	if (korzen == NULL) {	//jeœli drzewo istnieje
		return;
	}
	int depth = glebokosc(korzen);
	int cnt = 0;
	for (int i = 0; i < depth; ++i) {
		cnt += (int)pow(2, i);
	}
	int * queue = new int[cnt];
	for (int i = 0; i < cnt; queue[i++] = -1);
	kolejka(queue, korzen, 0);

	int liczbapoziomow = 1;
	int copycnt = cnt;
	int liczbakrateknajnizej;
	int liczbakrateknapoziomie;
	while (copycnt != 1) {
		liczbapoziomow++;
		copycnt /= 2;
	}
	liczbakrateknajnizej = (int)pow(2, liczbapoziomow - 1) * 10 + ((int)pow(2, liczbapoziomow - 1) - 1) * 2;
	for (int i = 0; i < liczbapoziomow; i++) {
		liczbakrateknapoziomie = (int)pow(2, i) * 10 + ((int)pow(2, i) - 1) * 2;
		for (int j = 0; j < (liczbakrateknajnizej - liczbakrateknapoziomie) / 2; j++) {
			cout << " ";
		}
		for (int j = 0; j < (int)pow(2, i); j++) {
			if (cnt >= (int)pow(2, i) + j) {
				cout.width(10);
				if (queue[(int)pow(2, i) + j - 1] == -1) {
					cout << "     (0)    ";
				}
				else {
					cout << internal << queue[(int)pow(2, i) + j - 1] << "   ";
				}
			}

		}
		cout << "\n";
	}
	delete[]queue;
}

void BST::generateBST(int size) {
	if (korzen != NULL) {	//jeœli drzewo istnieje
		destruktor(korzen);	//to je usuwam
		korzen = NULL;
	}
	for (int i = 0; i < size; i++) {	//odczytuje liczby
		addValue(rand());	//funkcja addValue dla kazdej liczby z osobna
	}
}

int BST::glebokosc(BST_Element *korzenn){
	//Rekurencyjna funkcja potrzebna do wyswietlenia drzewa. Funkcja wyznacza glebokosc drzewa (iloœæ poziomów).
	if (korzenn == NULL)
		return 0;

	int left_depth = glebokosc(korzenn->left);
	int right_depth = glebokosc(korzenn->right);

	return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
}

void BST::kolejka(int *queue, BST_Element *korzenn, int index){
	//Rekurencyjna funkcja potrzebna do wyœwietlenia drzewa. Tworzy kolejkê FIFO przechowuj¹c¹ BST.
	if (korzenn == NULL)
		return;

	if (index == 0)
		queue[0] = korzenn->value;

	if (korzenn->left != NULL)
	{
		queue[2 * index + 1] = korzenn->left->value;
		kolejka(queue, korzenn->left, 2 * index + 1);
	}
	if (korzenn->right != NULL)
	{
		queue[2 * index + 2] = korzenn->right->value;
		kolejka(queue, korzenn->right, 2 * index + 2);
	}
}

void BST::rotLewo(BST_Element *rotowany) {
	//Funkcja rotacji w prawo u¿ywana walgorytmie DSW. 
	//Wykonuje rotacjê w prawo zmieniaj¹c wskaŸniki poszczególnych elementów drzewa jeœli istniej¹.
	BST_Element *syn = (rotowany->right);
	if (syn != NULL) {	//alg ma sens tylko jeœli jest z czym zamieniaæ
		BST_Element *wnuk = (syn->left);
		BST_Element *ojciec = (rotowany->parent);
		if (rotowany == korzen) {	//jeœli zmieniamy korzeñ
			korzen = syn;
		}
		(rotowany->parent) = syn;	//odwrócenie po³¹czenia miêdzy rotowanym elementem a jego lewym synem
		(syn->left) = rotowany;
		if (wnuk != NULL) {	//jesli prawy syn syna rotowanego istnieje to przechodzi jako lewy syn rotowanego
			(wnuk->parent) = rotowany;
			(rotowany->right) = wnuk;
		}
		else {
			(rotowany->right) = NULL;
		}
		if (ojciec != NULL) {	//jesli ojciec istnieje to polaczenie jest miedzy nim a synem rotowanego
			(syn->parent) = ojciec;
			if ((ojciec->value) > (rotowany->value)) {
				(ojciec->left) = syn;
			}
			else {
				(ojciec->right) = syn;
			}
		}
		else {
			(syn->parent) = NULL;
		}
	}
}

void BST::rotPrawo(BST_Element *rotowany) {
	//Funkcja rotacji w prawo u¿ywana walgorytmie DSW. Brak komentarzy (odwrócenie funkcji rotLewo).
	BST_Element *syn = (rotowany->left);
	if (syn != NULL) {	//alg ma sens tylko jeœli jest z czym zamieniaæ
		BST_Element *wnuk = (syn->right);
		BST_Element *ojciec = (rotowany->parent);
		if (rotowany == korzen) {
			korzen = syn;
		}
		(rotowany->parent) = syn;
		(syn->right) = rotowany;
		if (wnuk != NULL) {
			(wnuk->parent) = rotowany;
			(rotowany->left) = wnuk;
		}
		else {
			(rotowany->left) = NULL;
		}
		if (ojciec != NULL) {
			(syn->parent) = ojciec;
			if ((ojciec->value) > (rotowany->value)) {
				(ojciec->left) = syn;
			}
			else {
				(ojciec->right) = syn;
			}
		}
		else {
			(syn->parent) = NULL;
		}
	}
}

void BST::DSW() {
	//1. Prostowanie drzewa
	BST_Element *temp = korzen;
	while (temp != NULL) {	//od korzenia idziemy po prawej krawedzi robi¹c tyle rotacji w prawo ile siê da
		if ((temp->left) != NULL) {
			rotPrawo(temp);
			temp = (temp->parent);
		}
		else{
			temp = (temp->right);
		}
	}

	//2. Równowa¿enie drzewa
	int n = glebokosc(korzen);	//glebokosc = liczba wezlow dla wyprostowanego drzewa
	int m = (int)pow(2, (int)log2(n + 1)) - 1;	//m ze wzoru
	temp = korzen;
	for (int i = n - m; i > 0; i--) {	//n-m rotacji w lewo co drugi wierzcholek
		rotLewo(temp);
		temp = ((temp->parent)->right);
	}
	while (m > 1) {	//z algorytmu: dopóki m>1: m=[m/2] i robimy m rotacji w lewo co drugi wierzcholek
		m = (int)m / 2;
		temp = korzen;
		for (int i = m; i > 0; i--) {
			rotLewo(temp);
			temp = ((temp->parent)->right);
		}
	}
}



void displayMenu(string info){
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "8.Rownowazenie drzewa (tylko BST)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void menu_table(){
	Table myTab;
	TimeCounter counter;
	char opt;
	string fileName;
	int index, value;
	double counterr = 0;
	int n = 1000;	//ilosc generacji danych
	int m = 1000;	//dlugosc wygenerowanej tablicy
	do {
		displayMenu("--- TABLICA ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie  tablicy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			myTab.loadFromFile(fileName);
			myTab.display();
			break;

		case '2': //usuwanie elemenu z tablicy
			cout << " Podaj index:";
			cin >> index;
			myTab.deleteFromTable(index);
			myTab.display();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " Podaj index:";
			cin >> index;
			cout << " Podaj wartosc:";
			cin >> value;

			myTab.addValue(index, value);
			myTab.display();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			cout << " Podaj wartosc:";
			cin >> value;
			if (myTab.isValueInTable(value))
				cout << "Podana wartosc jest w tablicy\n";
			else
				cout << "Podanej wartosci NIE ma w tablicy\n";
			myTab.display();
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementow tablicy:";
			cin >> value;
			myTab.generateTable(value);
			myTab.display();
			break;

		case '6':  //tutaj wyœwietlanie tablicy
			myTab.display();
			break;

		case '7':
			cout << "1 - zmierz czas dodania na pierwszej pozycji\n";
			cout << "2 - zmierz czas dodania na ostatniej pozycji\n";
			cout << "3 - zmierz czas dodania na losowej pozycji\n";
			cout << "4 - zmierz czas usuniêcia z pierwszej pozycji\n";
			cout << "5 - zmierz czas usuniêcia z ostatniej pozycji\n";
			cout << "6 - zmierz czas usuniêcia z losowej pozycji\n";
			cout << "7 - zmierz czas wyszukania losowej liczby\n";
			cin >> value;
			switch (value) {
			case 1:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.addValue(0, ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr/n << "\n";
				break;
			case 2:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.addValue(m, ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 3:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					int ranpos = (int)(((double)rand() / (double)RAND_MAX) * (double)(m + 1));
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.addValue(ranpos, ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 4:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.deleteFromTable(0);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 5:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.deleteFromTable(m - 1);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 6:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranpos = (int)(((double)rand() / (double)RAND_MAX) * (double)m);
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.deleteFromTable(ranpos);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 7:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myTab.generateTable(m);
					counter.StartCounter();
					myTab.isValueInTable(ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			}
			break;
		}

	} while (opt != '0');
}

void menu_list() {
	List myList;
	TimeCounter counter;
	char opt;
	string fileName;
	int index, value;
	double counterr = 0;
	int n = 1000;	//ilosc generacji danych
	int m = 1000;	//dlugosc wygenerowanej listy

	do {
		displayMenu("--- LISTA ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie listy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			myList.loadFromFile(fileName);
			myList.display();
			break;

		case '2': //usuwanie elemenu z listy
			cout << " Podaj wartosc:";
			cin >> value;
			if (myList.deleteFromList(value))
				cout << "Element o podanej wartosci zostal usuniety\n";
			else
				cout << "Nie znaleziono elementu o podanej wartosci\n";
			myList.display();
			break;

		case '3': //tutaj dodawanie elemetu do listy
			cout << " Podaj index:";
			cin >> index;
			cout << " Podaj waertosc:";
			cin >> value;

			myList.addValue(index, value);
			myList.display();
			break;

		case '4': //tutaj znajdowanie elemetu w liscie
			cout << " Podaj wartosc:";
			cin >> value;
			if (myList.isValueInList(value))
				cout << "Podana wartosc jest w liscie\n";
			else
				cout << "Podanej wartosci NIE ma w liscie\n";
			myList.display();
			break;

		case '5':  //tutaj generowanie listy
			cout << "Podaj ilosc elementow listy:";
			cin >> value;
			myList.generateList(value);
			myList.display();
			break;

		case '6':  //tutaj wyœwietlanie listy
			myList.display();
			break;

		case '7':
			cout << "1 - zmierz czas dodania na pierwszej pozycji\n";
			cout << "2 - zmierz czas dodania na ostatniej pozycji\n";
			cout << "3 - zmierz czas dodania na losowej pozycji\n";
			cout << "4 - zmierz czas usuniêcia z pierwszej pozycji\n";
			cout << "5 - zmierz czas usuniêcia z ostatniej pozycji\n";
			cout << "6 - zmierz czas usuniêcia z losowej pozycji\n";
			cout << "7 - zmierz czas wyszukania losowej liczby\n";
			cin >> value;
			switch (value) {
			case 1:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myList.generateList(m);
					counter.StartCounter();
					myList.addFirst(ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 2:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myList.generateList(m);
					counter.StartCounter();
					myList.addLast(ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 3:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					int ranpos = (int)(((double)rand() / (double)RAND_MAX) * (double)(m + 1));
					myList.generateList(m);
					counter.StartCounter();
					myList.addValue(ranpos, ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 4:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myList.generateList(m);
					int valuee = myList.getValue(0);
					counter.StartCounter();
					myList.deleteFirst();
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 5:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myList.generateList(m);
					int valuee = myList.getValue(m - 1);
					counter.StartCounter();
					myList.deleteLast();
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 6:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myList.generateList(m);
					int ranpos = (int)(((double)rand() / (double)RAND_MAX) * (double)m);
					int valuee = myList.getValue(ranpos);
					counter.StartCounter();
					myList.deleteFromList(valuee);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 7:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myList.generateList(m);
					counter.StartCounter();
					myList.isValueInList(ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			}
			break;
		}

	} while (opt != '0');
}

void menu_heap(){
	Heap myHeap;
	TimeCounter counter;
	char opt;
	string fileName;
	int value;
	double counterr = 0;
	int n = 1000;	//ilosc generacji danych
	int m = 20000;	//dlugosc wygenerowanej listy

	do {
		displayMenu("--- KOPIEC ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie kopca z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			myHeap.loadFromFile(fileName);
			myHeap.display();
			break;

		case '2': //usuwanie elemenu z kopca
			cout << " Podaj wartosc:";
			cin >> value;
			if (myHeap.deleteFromHeap(value)) {
				cout << " Pomyslnie usunieto podana wartosc\n";
			}
			else {
				cout << " W kopcu nie znaleziono podanej wartosci\n";
			}
			myHeap.display();
			break;

		case '3': //tutaj dodawanie elemetu do kopca
			cout << " Podaj wartosc:";
			cin >> value;

			myHeap.addValue(value);
			myHeap.display();
			break;

		case '4': //tutaj znajdowanie elemetu w kopcu
			cout << " Podaj wartosc:";
			cin >> value;
			if (myHeap.isValueInHeap(value))
				cout << "Podana wartosc jest w kopcu\n";
			else
				cout << "Podanej wartosci NIE ma w kopcu\n";
			myHeap.display();
			break;

		case '5':  //tutaj generowanie kopca
			cout << "Podaj ilosc elementow kopca:";
			cin >> value;
			myHeap.generateHeap(value);
			myHeap.display();
			break;

		case '6':  //tutaj wyœwietlanie kopca
			myHeap.display();
			break;

		case '7':
			cout << "1 - zmierz czas dodania\n";
			cout << "2 - zmierz czas usuniêcia z losowej pozycji\n";
			cout << "3 - zmierz czas wyszukania losowej liczby\n";
			cin >> value;
			switch (value) {
			case 1:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myHeap.generateHeap(m);
					int ranpos = (int)(((double)rand() / (double)RAND_MAX) * (double)(m + 1));
					int valuee = myHeap.getValue(ranpos);
					counter.StartCounter();
					myHeap.addValue(valuee);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 2:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myHeap.generateHeap(m);
					counter.StartCounter();
					myHeap.deleteFirst();
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 3:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					int ranval = rand();
					myHeap.generateHeap(m);
					counter.StartCounter();
					myHeap.isValueInHeap(ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			}
			break;
		}

	} while (opt != '0');
}

void menu_BST() {
	BST myBST;
	TimeCounter counter;
	char opt;
	string fileName;
	int value;
	double counterr = 0;
	int n = 1000;	//ilosc generacji danych
	int m = 1000;	//dlugosc wygenerowanej listy

	do {
		displayMenu("--- KOPIEC ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie drzewa z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			myBST.loadFromFile(fileName);
			myBST.display();
			break;

		case '2': //usuwanie elemenu z drzewa
			cout << " Podaj wartosc:";
			cin >> value;
			if (myBST.deleteFromBST(value)) {
				cout << " Pomyslnie usunieto podana wartosc\n";
			}
			else {
				cout << " W drzewie nie znaleziono podanej wartosci\n";
			}
			myBST.display();
			break;

		case '3': //tutaj dodawanie elemetu do drzewa
			cout << " Podaj wartosc:";
			cin >> value;

			myBST.addValue(value);
			myBST.display();
			break;

		case '4': //tutaj znajdowanie elemetu w drzewie
			cout << " Podaj wartosc:";
			cin >> value;
			if (myBST.isValueInBST(value))
				cout << "Podana wartosc jest w drzewie\n";
			else
				cout << "Podanej wartosci NIE ma w drzewie\n";
			myBST.display();
			break;

		case '5':  //tutaj generowanie drzewa
			cout << "Podaj ilosc elementow drzewa:";
			cin >> value;
			myBST.generateBST(value);
			myBST.display();
			break;

		case '6':  //tutaj wyœwietlanie drzewa
			myBST.display();
			break;

		case '7':
			cout << "1 - zmierz czas dodania\n";
			cout << "2 - zmierz czas usuniêcia z losowej pozycji\n";
			cout << "3 - zmierz czas wyszukania losowej liczby\n";
			cin >> value;
			switch (value) {
			case 1:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myBST.generateBST(m);
					int ranval = rand();
					counter.StartCounter();
					myBST.addValue(ranval);
					myBST.DSW();
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 2:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myBST.generateBST(m);
					int ranval = rand();
					counter.StartCounter();
					myBST.deleteFromBST(ranval);
					myBST.DSW();
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			case 3:
				counterr = 0;
				for (int i = 0; i < n; i++) {
					myBST.generateBST(m);
					int ranval = rand();
					counter.StartCounter();
					myBST.isValueInBST(ranval);
					counterr += counter.GetCounter();
				}
				cout << (double)counterr / n << "\n";
				break;
			}
			break;
		case '8':
			myBST.DSW();
			myBST.display();
			break;
		}

	} while (opt != '0');
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Tablica" << endl;
		cout << "2.Lista" << endl;
		cout << "3.Kopiec" << endl;
		cout << "4.BST" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			menu_table();
			break;

		case '2':
			menu_list();
			break;

		case '3':
			menu_heap();
			break;
		case '4':
			menu_BST();
			break;
		}

	} while (option != '0');

	system("pause");
	return 0;
}