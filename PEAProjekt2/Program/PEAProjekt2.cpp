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
	cout << "3.Wyswietl macierz" << endl;
	cout << "4.Algorytm Tabu Search" << endl;
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
	int x = 100;	//ilosc generacji danych
	long long wynikCalkowity;
	int y;	//liczba wierzcholkow do testow
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
			break;

		case '3':  //tutaj wyswietlanie grafu
			mojGraf->display();
			break;

		case '4':
			mojGraf->iteracje = 2500;
			mojGraf->aspiracja = (int)ceil((float)n / 5.0);
			mojGraf->kadencja = 3 * n;
			mojGraf->krytyczne = mojGraf->iteracje / 25;

			mojGraf->algorytmTabuSearch();
			break;
		case '5':	//wyswietlenie wyniku algorytmu
			mojGraf->displayRozwiazanie();
			break;

		case '6':
			counterr = 0;
			int nn = 50;	//liczba miast
			mojGraf = new Graf(nn);
			mojGraf->generateGraf(nn);
			
			mojGraf->iteracje = 500;
			mojGraf->kadencja = nn;
			mojGraf->krytyczne = mojGraf->iteracje/100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla "<<nn<< " miast, "<<x<<" populacji, "<<mojGraf->iteracje<<" iteracji, "<<mojGraf->aspiracja<<" aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;
			
			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 2*nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 3*nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;
			
			mojGraf->iteracje = 1000;
			mojGraf->kadencja = nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 2 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 3 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->iteracje = 1500;
			mojGraf->kadencja = nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 2 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 3 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->iteracje = 2000;
			mojGraf->kadencja = nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 2 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 3 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->iteracje = 2500;
			mojGraf->kadencja = nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 2 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->kadencja = 3 * nn;
			mojGraf->krytyczne = mojGraf->iteracje / 100;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 50;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->krytyczne = mojGraf->iteracje / 25;
			mojGraf->aspiracja = (int)ceil((float)nn / 10.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			mojGraf->aspiracja = (int)ceil((float)nn / 5.0);

			counterr = 0;
			wynikCalkowity = 0;
			for (int i = 0; i < x; i++) {
				counter.StartCounter();
				mojGraf->algorytmTabuSearch();
				wynikCalkowity += mojGraf->wynikk;
				counterr += counter.GetCounter();
			}
			cout << "Tabu Search dla " << nn << " miast, " << x << " populacji, " << mojGraf->iteracje << " iteracji, " << mojGraf->aspiracja << " aspiracji, " << mojGraf->kadencja << " kadencja, " << mojGraf->krytyczne << " krytyczne. Wynik: " << wynikCalkowity / x << endl << "Czas: " << counterr << endl;

			
			break;

		}
	} while (opt != '0');
	system("pause");
	return 0;
}
