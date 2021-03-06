#include "stdafx.h"
#include "Graf.h"
#include "Plecak.h"
#include "TimeCounter.h"

#include <cstdio>
#include <conio.h>
#include <ctime>

void displayMenu1(string info) {
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Utworz losowo" << endl;
	cout << "3.Wyswietl" << endl;
	cout << "4.Przeglad zupelny" << endl;
	cout << "5.Algorytm zachlanny z kryterium wartosci" << endl;
	cout << "6.Algorytm zachlanny z kryterium stosunku wartosci i rozmiaru" << endl;
	cout << "7.Algorytm z programowaniem dynamicznym" << endl;
	cout << "8.Wyswietl rozwiazanie algorytmu" << endl;
	cout << "9.Wyswietl rozwiazanie algorytmu dynamicznego" << endl;
	cout << "a.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void displayMenu2(string info) {
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Utworz losowo" << endl;
	cout << "3.Wyswietl macierz sasiedztwa" << endl;
	cout << "4.Przeglad zupelny" << endl;
	cout << "5.Algorytm zachlanny" << endl;
	cout << "6.Algorytm przeszukiwania lokalnego" << endl;
	cout << "7.Wyswietl rozwiazanie algorytmu" << endl;
	cout << "8.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void menu_plecak() {
	Plecak *mojPlecak = new Plecak(0, 0);
	ifstream plik;
	TimeCounter counter;
	int n; //ilosc elementow
	int b; //pojemnosc plecaka 
	long suma; //suma wartosci elementow do generacji grafu
	char opt;
	string fileName;
	double counterr = 0;
	int x = 100;	//ilosc generacji danych
	int y;			//pojemnosc plecaka do testow
	int z;			//liczba przedmiotow

	do {
		displayMenu1("--- Problem plecakowy ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie z pliku
			cout << " Podaj nazwe pliku:";
			cin >> fileName;

			plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
			if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
				plik.close();
				break;
			}
			plik >> b >> n;
			mojPlecak = new Plecak(n, b);

			mojPlecak->loadFromFile(fileName);
			mojPlecak->display();
			plik.close();
			break;

		case '2':  //tutaj generowanie grafu
			cout << "Podaj liczbe elementow: ";
			cin >> n;
			cout << "Podaj pojemnosc plecaka: ";
			cin >> b;
			mojPlecak = new Plecak(n, b);
			do {
				suma=(mojPlecak->generatePlecak(n));
			} while (suma <= b);
			mojPlecak->display();
			break;

		case '3':  //tutaj wyswietlanie grafu
			mojPlecak->display();
			break;

		case '4':	//algorytm Zupelny
			mojPlecak->algorytmZupelny();
			break;

		case '5':	//algorytm Zachlanny wybierajacy przez wartosc
			mojPlecak->algorytmZachlannyWartosc();
			break;

		case '6':	//algorytm Zachlanny wybierajacy przez wartosc
			mojPlecak->algorytmZachlannyWartoscWaga();
			break;

		case '7':	//algorytm Dynamiczny
			mojPlecak->algorytmDynamiczny();
			break;

		case '8':	//wyswietlenie wyniku algorytmu
			mojPlecak->displayRozwiazanie();
			break;

		case '9':	//wyswietlenie wyniku algorytmu dynamicznego
			mojPlecak->displayRozwiazanieDynamiczne();
			break;

		case 'a':
			counterr = 0;
			y = 15;
			z = 100000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 200000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 300000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 18;
			z = 100000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 200000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 300000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 20;
			z = 100000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 200000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 300000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 23;
			z = 100000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 200000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 300000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 25;
			z = 100000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 200000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;
			counterr = 0;
			z = 300000;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartosc();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmZachlannyWartoscWaga();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny wartosc waga: " << (double)counterr / x << endl;
			counterr = 0;
			mojPlecak = new Plecak(y, z);
			for (int i = 0; i < x; i++) {
				do {
					suma = (mojPlecak->generatePlecak(y));
				} while (suma <= z);
				counter.StartCounter();
				mojPlecak->algorytmDynamiczny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm dynamiczny: " << (double)counterr / x << endl;



			break;

		}
	} while (opt != '0');
}

void menu_komiwojazer() {
	Graf *mojGraf = new Graf(0);
	ifstream plik;
	TimeCounter counter;
	int n; //liczba wierzcholkow
	char opt;
	string fileName;
	double counterr = 0;
	int x = 100;	//ilosc generacji danych
	int y;			//liczba wierzcholkow do testow
	int i;	//wierzcholek poczatkowy

	do {
		displayMenu2("--- Problem komiwojazera ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie grafu z pliku
			cout << " Podaj nazwe pliku:";
			cin >> fileName;

			plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
			if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
				plik.close();
				break;
			}
			plik >> n;
			mojGraf = new Graf(n);

			mojGraf->loadFromFile(fileName);
			mojGraf->display();
			plik.close();
			break;

		case '2':  //tutaj generowanie grafu
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> n;
			mojGraf = new Graf(n);
			mojGraf->generateGraf(n);
			mojGraf->display();
			break;

		case '3':  //tutaj wyswietlanie grafu
			mojGraf->display();
			break;

		case '4':
			mojGraf->algorytmZupelny();
			break;

		case '5':
			cout << "Podaj wierzcholek poczatkowy: ";
			do {
				cin >> i;
			}while (i > n);
			mojGraf->algorytmZachlanny(i);
			break;

		case '6':
			mojGraf->algorytmLokalny();
			break;

		case '7':	//wyswietlenie wyniku algorytmu
			mojGraf->displayRozwiazanie();
			break;

		case '8':
			counterr = 0;
			y = 6;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 7;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl; 
			counterr = 0;
			y = 8;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl; 
			counterr = 0;
			y = 9;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl; 
			counterr = 0;
			y = 10;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmZupelny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zupelny: " << (double)counterr / x << endl;

			counterr = 0;
			y = 20;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmZachlanny(o);
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny: " << (double)counterr / x << endl;
			counterr = 0;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmLokalny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm lokalny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 40;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmZachlanny(o);
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny: " << (double)counterr / x << endl;
			counterr = 0;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmLokalny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm lokalny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 60;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmZachlanny(o);
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny: " << (double)counterr / x << endl;
			counterr = 0;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmLokalny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm lokalny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 80;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmZachlanny(o);
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny: " << (double)counterr / x << endl;
			counterr = 0;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmLokalny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm lokalny: " << (double)counterr / x << endl;
			counterr = 0;
			y = 100;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmZachlanny(o);
				counterr += counter.GetCounter();
			}
			cout << "Algorytm zachlanny: " << (double)counterr / x << endl;
			counterr = 0;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				int o = rand() % y;
				mojGraf->algorytmLokalny();
				counterr += counter.GetCounter();
			}
			cout << "Algorytm lokalny: " << (double)counterr / x << endl;
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
		cout << "1.Problem plecakowy." << endl;
		cout << "2.Problem komiwojazera." << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			menu_plecak();
			break;

		case '2':
			menu_komiwojazer();
			break;

		}

	} while (option != '0');
	system("pause");
	return 0;
}