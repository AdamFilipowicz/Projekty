#include "stdafx.h"
#include "Graf.h"

Graf::Graf(int n) {
	w = n;
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	permutacja = new int[w];
	wynik = new int[w];
}

Graf::~Graf() {
	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;
	delete[] permutacja;
	delete[] wynik;
}

void Graf::algorytmZupelny() {
	long mintrasa = 0;	//po iteracji wybieramy minimalna trase
	long trasaaktualna;	//trasa ktorej uzywamy przy kazdej iteracji i porownujemy z mintrasa
	int k;	//najwieksza liczba taka, ze permutacja[k]<permutacja[k+1]
	int l;	//najwieksza liczba taka, ze l>k i permutacja[k]<permutacja[l]
	int waktualny;	//aktualny wierzcholek
	int pomoc;
	for (int i = 0; i < w; i++) {
		permutacja[i] = i + 1;	//pierwsza permutacja
		mintrasa += macierz[i][(i + 1) % w];	//pierwsze rozwiazanie
		wynik[i] = permutacja[i];
	}
	k = 0;
	while (k != -1) {
		trasaaktualna = 0;
		//szukamy nastepnej permutacji
		k = -1;
		for (int i = w - 2; i >= 0; i--) {	//1. znajdujemy k
			if (permutacja[i] < permutacja[i + 1]) {
				k = i;
				break;
			}
		}
		if (k == -1)
			break;
		for (int i = w - 1; i > k; i--) {	//2. znajdujemy l
			if (permutacja[k] < permutacja[i]) {
				l = i;
				break;
			}
		}
		//3. zamieniamy ich wartosci
		pomoc = permutacja[k];
		permutacja[k] = permutacja[l];
		permutacja[l] = pomoc;
		//4. odwracamy wszystkie wartosci od k+1 do w
		for (int i = 0; i < (w - (k + 1)) / 2; i++) {
			pomoc = permutacja[k + 1 + i];
			permutacja[k + 1 + i] = permutacja[w - 1 - i];
			permutacja[w - 1 - i] = pomoc;
		}
		
		//znalezlismy permutacje: szukamy czy wynik jest na razie najlepszy
		waktualny = permutacja[0] - 1;
		for (int i = 1; i < w; i++) {
			trasaaktualna += macierz[waktualny][permutacja[i] - 1];
			waktualny = permutacja[i] - 1;
		}
		trasaaktualna += macierz[waktualny][permutacja[0] - 1];
		if (trasaaktualna < mintrasa) {	//jesli znalezlismy mniejsza trase
			mintrasa = trasaaktualna;	//aktualizujemy minimalna trase
			for (int i = 0; i < w; i++) {
				wynik[i] = permutacja[i];	//i aktualizujemy wynik
			}
		}
	}

}

void Graf::algorytmZachlanny(int poczatkowy) {	//alg najblizszego sasiada
	bool *odwiedzone = new bool[w];	//tablica odwiedzonych wierzcholkow
	long minimalnaodleglosc;	//minimalna odleglosc do nastepnego wierzcholka
	int ktorywierzcholek;
	int wierzcholek = poczatkowy;
	for (int i = 0; i < w; i++) {
		odwiedzone[i] = false;
	}
	odwiedzone[wierzcholek] = true;
	wynik[0] = poczatkowy + 1;
	for (int i = 1; i < w; i++) {	//w-1 krawedzi
		minimalnaodleglosc = INT_MAX;
		for (int j = 0; j < w; j++) {	//szukamy najblizszego nieodwiedzonego wierzcholka
			if (!odwiedzone[j] && minimalnaodleglosc > macierz[wierzcholek][j]) {
				minimalnaodleglosc = macierz[wierzcholek][j];
				ktorywierzcholek = j;
			}
		}
		wynik[i] = ktorywierzcholek + 1;	//dodajemy wierzcholek do permutacji wyniku
		odwiedzone[ktorywierzcholek] = true;	//oznaczamy wierzcholek jako odwiedzony
		wierzcholek = ktorywierzcholek;	//i przechodzimy do niego
	}

	delete[] odwiedzone;
}

void Graf::algorytmLokalny() {
	int* najlepszaiteracja = new int[w];	//permutacja najlepszej drogi w danej iteracji
	long minodleglosc = 0;//minimalna odleglosc do porownania
	long trasaaktualna = 0;
	bool czyjestlepszadroga = true;
	int waktualny;	//wierzcholek aktualny
	int l, pomoc;	//zmienne pomocnicze do generowania losowej permutacji
	for (int i = 0; i < w; i++) {
		permutacja[i] = i + 1;
	}
	for (int i = w; i >= 2; i--) {	//generuje losowa permutacje
		l = rand() % i;	//losuje wierzcholek do zamiany dla kazdego wierzcholka
		pomoc = permutacja[l];
		permutacja[l] = permutacja[i - 1];
		permutacja[i - 1] = pomoc;
	}
	//ustalamy dlugosc pierwszej trasy
	waktualny = permutacja[0] - 1;
	for (int i = 1; i < w; i++) {
		minodleglosc += macierz[waktualny][permutacja[i] - 1];
		waktualny = permutacja[i] - 1;
	}
	minodleglosc += macierz[waktualny][permutacja[0] - 1];
	//wynik - najlepsza droga dla danej iteracji
	for (int i = 0; i < w; i++) {
		wynik[i] = permutacja[i];
		najlepszaiteracja[i] = wynik[i];
	}
	while (czyjestlepszadroga) {
		czyjestlepszadroga = false;
		for (int i = 0; i < w - 2; i++) {	//w petlach wszystkie zamiany dwukrawedziowe naszej permutacji
			trasaaktualna = 0;
			for (int j = i + 2; j < w; j++) {
				permutacja[i] = wynik[j];	//zamiana krawedzi
				permutacja[j] = wynik[i];

				//szukamy czy wynik moze byc poprawiony
				waktualny = permutacja[0] - 1;
				for (int k = 1; k < w; k++) {
					trasaaktualna += macierz[waktualny][permutacja[k] - 1];
					waktualny = permutacja[k] - 1;
				}
				trasaaktualna += macierz[waktualny][permutacja[0] - 1];
				if (trasaaktualna < minodleglosc) {	//jesli znalezlismy mniejsza trase
					minodleglosc = trasaaktualna;	//aktualizujemy minimalna trase
					for (int k = 0; k < w; k++) {
						najlepszaiteracja[k] = permutacja[k];	//aktualizujemy wynik
					}
					czyjestlepszadroga = true;	//ustalamy zeby algorytm nadal szukal lepszych drog
				}
				permutacja[i] = wynik[i];	//powrot do krawedzi
				permutacja[j] = wynik[j];
			}
		}
		for (int i = 0; i < w; i++) {
			wynik[i] = najlepszaiteracja[i];
			permutacja[i] = wynik[i];
		}
	}
	delete[] najlepszaiteracja;
}

void Graf::display() {
	cout << "Krawedzie grafu: " << endl;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			cout << macierz[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::displayRozwiazanie() {
	int sumasciezka = 0;
	int waktualny = wynik[0] - 1;
	cout << "Rozwiazanie: " << endl;
	cout << wynik[0] - 1 << "->";
	for (int i = 1; i < w; i++) {
		cout << wynik[i] - 1 << "->";
		sumasciezka += macierz[waktualny][wynik[i] - 1];
		waktualny = wynik[i] - 1;
	}
	sumasciezka += macierz[waktualny][wynik[0] - 1];
	cout << wynik[0] - 1;
	cout << endl << "Suma sciezki: " << sumasciezka << endl;
}

int Graf::loadFromFile(string FileName) {
	//usuwamy istniejaca macierz
	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;

	//inicjalizujemy nowa macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}

	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())	//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	int omin1;
	plik >> omin1;
	int wartosc;
	for (int i = 0; i < omin1; i++) {	//odczytuje tyle krawedzi ile podanych na poczatku
		for (int j = 0; j < omin1; j++) {
			plik >> wartosc;
			macierz[i][j] = wartosc; //dodanie krawedzi do macierzy
		}
	}
	return 1;
}

void Graf::generateGraf(int lwierzch) {
	//usuwamy istniejaca macierz
	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;

	//inicjalizujemy nowa macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}

	for (int i = 0; i < w; i++) {	//losujemy kazdy element macierzy nie lezacy na przekatnej glownej
		for (int j = 0; j < w; j++) {
			if (i != j) {
				macierz[i][j] = rand();
			}
		}
	}
}