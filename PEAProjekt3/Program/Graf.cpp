#include "stdafx.h"
#include "Graf.h"

Graf::Graf(int n) {
	w = n;
	macierz = new int*[w];
	for (int i = 0; i < w; i++){
		macierz[i] = new int[w];
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	tabOrganizmow = new int*[liczbaOrganizmow];
	for (int i = 0; i < liczbaOrganizmow; i++){
		tabOrganizmow[i] = new int[w];
		for (int j = 0; j < w; j++) {
			tabOrganizmow[i][j] = 0;
		}
	}
	tabPoczatkowych = new int*[liczbaPoczatkowych];
	for (int i = 0; i < liczbaPoczatkowych; i++) {
		tabPoczatkowych[i] = new int[w];
		for (int j = 0; j < w; j++) {
			tabPoczatkowych[i][j] = 0;
		}
	}
	permutacja = new int[w];
	wynik = new int[w];
	ocenaPoczatkowych = new long long[liczbaPoczatkowych];
	for (int i = 0; i < liczbaPoczatkowych; i++) {
		ocenaPoczatkowych[i] = 0;
	}
	ocenaOrganizmow = new long long[liczbaOrganizmow];
	for (int i = 0; i < liczbaOrganizmow; i++) {
		ocenaOrganizmow[i] = 0;
	}
}

Graf::~Graf() {
	for (int i = 0; i < w; i++)
		delete[] macierz[i];
	delete[] macierz;
	for (int i = 0; i < w; i++)
		delete[] tabOrganizmow[i];
	delete[] tabOrganizmow;
	for (int i = 0; i < w; i++)
		delete[] tabPoczatkowych[i];
	delete[] tabPoczatkowych;
	delete[] permutacja;
	delete[] wynik;
	delete[] ocenaPoczatkowych;
	delete[] ocenaOrganizmow;
}

void Graf::wyzeruj() {
	wynikk = INT_MAX;
	for (int i = 0; i < liczbaOrganizmow; i++) {
		for (int j = 0; j < w; j++) {
			tabOrganizmow[i][j] = 0;
		}
	}
	for (int i = 0; i < liczbaPoczatkowych; i++) {
		for (int j = 0; j < w; j++) {
			tabPoczatkowych[i][j] = 0;
		}
	}

	for (int i = 0; i < liczbaPoczatkowych; i++) {
		ocenaPoczatkowych[i] = 0;
	}
	for (int i = 0; i < liczbaOrganizmow; i++) {
		ocenaOrganizmow[i] = 0;
	}
	for (int i = 0; i < w; i++) {
		wynik[i] = 0;
	}
	for (int i = 0; i < w; i++) {
		permutacja[i] = 0;
	}
}

void Graf::algorytmPopulacyjny() {
	long long odleglosc = 0;	//odleglosc do wyznaczenia oceny przystosowania
	int waktualny;	//wierzcholek aktualny
	int l, pomoc;	//zmienne pomocnicze do generowania losowej permutacji
	int ktoryOsobnik;	//selekcja osobnika
	int *tabSelekcji = new int[k];	//tablica do oznaczenia miejsca z którego wzielismy k osobnikow
	for (int i = 0; i < k; i++)
		tabSelekcji[i] = 0;
	int minSelekcji = INT_MAX;	//do selekcji turniejowej
	int ktoryMinimalny;	//oznaczenie który jest liderem selekcji turniejowej
	int *pamietanieOcen = new int[k];
	for (int i = 0; i < k; i++)
		pamietanieOcen[i] = 0;
	int k1, k2; //indeksy do krzyżowania OX
	int *potomek = new int[w];	//tablica potomka
	int *potomek2 = new int[w];
	int *rodzic = new int[w];
	int iterator;	//iterator do krzyżowania w drugiego osobnika
	float mutator;	//losowy na przedziale [0,1]
	int iterator2;	//iterator do zwracania populacji do populacji oryginalnej

	//1. stworzenie losowych populacji początkowej
	for (int i = 0; i < w; i++) {
		permutacja[i] = i + 1;
	}

	for (int i = 0; i < liczbaPoczatkowych; i++) {
		for (int j = w; j >= 2; j--) {	//generuje losowa permutacje
			l = rand() % j;	//losuje wierzcholek do zamiany dla kazdego wierzcholka
			pomoc = permutacja[l];
			permutacja[l] = permutacja[j - 1];
			permutacja[j - 1] = pomoc;
		}
		for (int j = 0; j < w; j++)
			tabPoczatkowych[i][j] = permutacja[j];
		//2. ocena przystosowania populacji początkowych
		waktualny = permutacja[0] - 1;
		for (int j = 1; j < w; j++) {
			ocenaPoczatkowych[i] += macierz[waktualny][permutacja[j] - 1];
			waktualny = permutacja[j] - 1;
		}
		ocenaPoczatkowych[i] += macierz[waktualny][permutacja[0] - 1];
		if (ocenaPoczatkowych[i] < wynikk) {
			wynikk = ocenaPoczatkowych[i];
			for (int j = 0; j < w; j++)
				wynik[j] = tabPoczatkowych[i][j];
		}
	}	

	//3. główna pętla na ilość iteracji algorytmu
	for (int i = 0; i < iloscIteracji; i++) {
		//3.1 selekcja turniejowa - wybór populacji macierzystej
		for (int ii = 0; ii < liczbaOrganizmow; ii++) {	//losujemy zdefiniowana liczbę organizmow 
			minSelekcji = INT_MAX;
			for (int j = 0; j < k; j++) {	//losujemy k razy
				do {	//losuje dopoki nie wylosuje takiego którego jeszcze nie było
					ktoryOsobnik = rand() % liczbaPoczatkowych;
				} while (ocenaPoczatkowych[ktoryOsobnik] == 0);
				tabSelekcji[j] = ktoryOsobnik;	//zapamietuje jego miejsce
				if (ocenaPoczatkowych[ktoryOsobnik] < minSelekcji) {	//jeśli jest ktoś lepszy
					minSelekcji = ocenaPoczatkowych[ktoryOsobnik];
					ktoryMinimalny = ktoryOsobnik;
				}
				pamietanieOcen[j] = ocenaPoczatkowych[ktoryOsobnik];
				ocenaPoczatkowych[ktoryOsobnik] = 0;	//ustawiam że osobnik został zabrany
			}
			//po wylosowaniu k osobnikow trzeba dodac najlepszego do tabOrganizmow i zwrócić resztę do ocen poczatkowych
			for (int j = 0; j < w; j++) {
				tabOrganizmow[ii][j] = tabPoczatkowych[ktoryMinimalny][j];
			}
			ocenaOrganizmow[ii] = minSelekcji;
			for (int j = 0; j < k; j++) {
				if (tabSelekcji[j] != ktoryMinimalny)
					ocenaPoczatkowych[tabSelekcji[j]] = pamietanieOcen[j];
			}
		}

		/*iterator2 = 0;
		for (int j = 0; j < liczbaOrganizmow; j++) {
			if (ocenaOrganizmow[j] == 0) {
				iterator2++;
			}
		}
		cout << iterator2;*/

		//3.2 krzyżowanie chromosomów OX - mamy zapelniona tabOrganizmow z odpowiadajacymi ocenami organizmow
		for (int j = 0; j < liczbaOrganizmow / 2; j++) {	// /2 bo w jednej iteracji używamy dwóch organizmów
			//losowanie k1 i k2
			k1 = rand() % w;
			do {
				k2 = rand() % w;
			} while (k2 == k1);
			if (k2 < k1) {	//swap żeby k1 zawsze był mniejszy od k2
				pomoc = k1;
				k1 = k2;
				k2 = pomoc;
			}

			//tworzymy pierwszego potomka - część rodzica 1
			for (int r = k1; r <= k2; r++) {
				potomek[r] = tabOrganizmow[j * 2][r];
			}
			//przygotowanie rodzica
			for (int r = 0; r < w; r++) {
				rodzic[r] = tabOrganizmow[(j * 2) + 1][(r + k2 + 1) % w];
				for (int q = k1; q <= k2; q++)
					if (rodzic[r] == potomek[q])
						rodzic[q] = -1;
			}
			//dodajemy do niego części rodzica 2
			iterator = k2 + 1;
			for (int r = 0; r < w; r++) {
				if (rodzic[r] != -1) {
					potomek[iterator%w] = rodzic[r];
					iterator++;
				}
			}

			//tworzymy drugiego potomka
			for (int r = k1; r <= k2; r++) {
				potomek2[r] = tabOrganizmow[(j * 2) + 1][r];
			}
			//przygotowanie rodzica
			for (int r = 0; r < w; r++) {
				rodzic[r] = tabOrganizmow[j * 2][(r + k2 + 1) % w];
				for (int q = k1; q <= k2; q++)
					if (rodzic[r] == potomek2[q])
						rodzic[q] = -1;
			}
			//dodajemy do niego części rodzica 2
			iterator = k2 + 1;
			for (int r = 0; r < w; r++) {
				if (rodzic[r] != -1) {
					potomek2[iterator%w] = rodzic[r];
					iterator++;
				}
			}

			//zamiana rodzicow na potomki
			for (int r = 0; r < w; r++) {
				tabOrganizmow[(j * 2)][r] = potomek[r];
				tabOrganizmow[(j * 2) + 1][r] = potomek2[r];
			}

			//3.3 mutacja
			//pierwszy organizm
			mutator = (float)rand() / (float)INT_MAX;
			if (mutator < mutacja) {	//czyli jeśli trafiliśmy to mutujemy
				k1 = rand() % w;
				do {
					k2 = rand() % w;
				} while (k2 == k1);
				pomoc = tabOrganizmow[(j * 2)][k1];
				tabOrganizmow[(j * 2)][k1] = tabOrganizmow[j * 2][k2];
				tabOrganizmow[(j * 2)][k2] = pomoc;
			}
			//drugi organizm
			mutator = (float)rand() / (float)INT_MAX;
			if (mutator < mutacja) {	//czyli jeśli trafiliśmy to mutujemy
				k1 = rand() % w;
				do {
					k2 = rand() % w;
				} while (k2 == k1);
				pomoc = tabOrganizmow[(j * 2)][k1];
				tabOrganizmow[(j * 2)][k1] = tabOrganizmow[(j * 2) + 1][k2];
				tabOrganizmow[(j * 2)][k2] = pomoc;
			}

			//uaktualnienie ocen i końcowego wyniku
			//pierwszy organizm
			waktualny = tabOrganizmow[j * 2][0] - 1;
			for (int r = 1; r < w; r++) {
				ocenaOrganizmow[r] += macierz[waktualny][tabOrganizmow[j * 2][r] - 1];
				waktualny = tabOrganizmow[j * 2][r] - 1;
			}
			ocenaOrganizmow[j * 2] += macierz[waktualny][tabOrganizmow[j * 2][0] - 1];
			if (ocenaOrganizmow[j * 2] < wynikk) {
				wynikk = ocenaPoczatkowych[j * 2];
				for (int r = 0; r < w; r++)
					wynik[r] = tabPoczatkowych[j * 2][r];
			}
			//drugi organizm
			waktualny = tabOrganizmow[(j * 2) + 1][0] - 1;
			for (int r = 1; r < w; r++) {
				ocenaOrganizmow[r] += macierz[waktualny][tabOrganizmow[(j * 2) + 1][r] - 1];
				waktualny = tabOrganizmow[(j * 2) + 1][r] - 1;
			}
			ocenaOrganizmow[(j * 2) + 1] += macierz[waktualny][tabOrganizmow[(j * 2) + 1][0] - 1];
			if (ocenaOrganizmow[(j * 2) + 1] < wynikk) {
				wynikk = ocenaPoczatkowych[(j * 2) + 1];
				for (int r = 0; r < w; r++)
					wynik[r] = tabPoczatkowych[(j * 2) + 1][r];
			}
		}
		/*iterator2 = 0;
		for (int j = 0; j < liczbaOrganizmow; j++) {
			if (ocenaOrganizmow[j] == 0) {
				iterator2++;
			}
		}
		cout << iterator2;*/


		//zwrot tabOrganizmow razem z ocenami do tabPoczatkowego 
		iterator2 = 0;
		for (int j = 0; j < liczbaPoczatkowych; j++) {
			if (ocenaPoczatkowych[j] == 0) {
				ocenaPoczatkowych[j] = ocenaOrganizmow[iterator2];
				for (int r = 0; r < w; r++)
					tabPoczatkowych[j][r] = tabOrganizmow[iterator2][r];
				iterator2++;
			}
		}
	}

	delete[] tabSelekcji;
	delete[] pamietanieOcen;
	delete[] potomek;
	delete[] potomek2;
	delete[] rodzic;
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

int Graf::loadFromFile(string FileName, char symetria) {
	//usuwamy istniejaca macierz
	for (int i = 0; i < w; i++) {
		delete[] macierz[i];
	}
	delete[] macierz;

	ifstream plik;
	plik.open(FileName.c_str());	//otwieram plik o podanej nazwie
	if (!plik.good())		//koncze funkcje jesli podano bledna nzwe pliku
		return 0;
	plik >> w;
	//inicjalizujemy nowa macierz
	macierz = new int*[w];
	for (int i = 0; i < w; i++)
		macierz[i] = new int[w];
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			macierz[i][j] = 0;
		}
	}
	if (symetria == 's') {
		//problem symetryczny
		int wartosc = 1;
		for (int j = 0; j < w; j++) {
			for (int k = 0; k < j + 1; k++) {
				plik >> wartosc;
				macierz[j][k] = wartosc;
				macierz[k][j] = wartosc;
			}
		}
	}
	if (symetria == 'a') {
		//problem symetryczny
		int wartosc = 1;
		for (int j = 0; j < w; j++) {
			for (int k = 0; k < w; k++) {
				plik >> wartosc;
				if(k!=j)
					macierz[j][k] = wartosc;
			}
		}
	}
	
	return 1;
}

void Graf::generateGraf(int ww) {
	w = ww;
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