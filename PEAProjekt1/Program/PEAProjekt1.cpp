#include "stdafx.h"
#include "Graf.h"
#include "TimeCounter.h"

#include <cstdio>
#include <conio.h>
#include <ctime>

void displayMenu(string info) {
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Utworz losowo" << endl;
	cout << "3.Wyswietl macierz sasiedztwa" << endl;
	cout << "4.Algorytm dynamiczny" << endl;
	cout << "5.Wyswietl rozwiazanie algorytmu" << endl;
	cout << "6.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Graf *mojGraf = new Graf(0);
	ifstream plik;
	TimeCounter counter;
	int n; //liczba wierzcholkow
	char opt;
	char symetria;
	string fileName;
	double counterr = 0;
	int x = 10;	//ilosc generacji danych
	int y;			//liczba wierzcholkow do testow
	int i;	//wierzcholek poczatkowy

	do {
		displayMenu("--- Problem komiwojazera ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytywanie grafu z pliku
			do {
				cout << " Podaj czy graf jest asymetryczny (a) czy symetryczny (s):";
				cin >> symetria;
			} while (symetria != 'a' && symetria != 's');
			cout << " Podaj nazwe pliku:";
			cin >> fileName;

			plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
			if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
				plik.close();
				break;
			}
			plik >> n;
			mojGraf = new Graf(n);

			mojGraf->loadFromFile(fileName, symetria);
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
			mojGraf->algorytmBHKRekurencja();
			break;
		case '5':	//wyswietlenie wyniku algorytmu
			mojGraf->displayRozwiazanie();
			break;

		case '6':
			counterr = 0;
			x = 10;
			do {
				cout << " Podaj czy graf jest asymetryczny (a) czy symetryczny (s):";
				cin >> symetria;
			} while (symetria != 'a' && symetria != 's');
			cout << " Podaj nazwe pliku:";
			cin >> fileName;
			for (int i = 0; i < x; i++) {
				plik.open(fileName.c_str());	//otwieram plik o podanej nazwie
				if (!plik.good()) {	//koncze funkcje jesli podano bledna nazwe pliku
					plik.close();
					break;
				}
				plik >> n;
				mojGraf = new Graf(n);

				mojGraf->loadFromFile(fileName, 's');
				plik.close();

				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny symetryczny dla " << n << "miast: " << (double)counterr / x << endl;
			
			//zakomentowane: testy losowe dla y=4,6,8,10,12,14,16,18,20
			/*counterr = 0;
			y = 4;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 6;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 8;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 10;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 12;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 14;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 16;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 18;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;
			counterr = 0;
			y = 20;
			mojGraf = new Graf(y);
			for (int i = 0; i < x; i++) {
				mojGraf->generateGraf(y);
				counter.StartCounter();
				mojGraf->algorytmBHKRekurencja();
				counterr += counter.GetCounter();
				mojGraf->clear();
			}
			cout << "Algorytm dynamiczny dla " << y << "miast: " << (double)counterr / x << endl;*/
			break;

		}
	} while (opt != '0');
	system("pause");
	return 0;
}
