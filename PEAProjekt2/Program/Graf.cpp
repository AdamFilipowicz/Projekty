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
	tabu = new tabuPoz[3 * w];	//zerowanie tablicy tabu
	tabuPoz x;
	x.kadencja = 0;
	x.mniejszy = 0;
	x.wiekszy = 0;
	for (int i = 0; i < 3 * w; i++)
		tabu[i] = x;
	permutacja = new int[w];
	wynik = new int[w];
}

Graf::~Graf() {
	for (int i = 0; i < w; i++)
		delete[] macierz[i];
	delete[] macierz;
	delete[] tabu;
	delete[] permutacja;
	delete[] wynik;
}

void Graf::algorytmTabuSearch() {
	tabu = new tabuPoz[3 * w];	//zerowanie tablicy tabu
	tabuPoz x;
	x.kadencja = 0;
	x.mniejszy = 0;
	x.wiekszy = 0;
	for (int i = 0; i < 3 * w; i++)
		tabu[i] = x;
	wynikk = 0;
	algorytmLokalny();
}

void Graf::algorytmLokalny() {
	int doKrytycznego = 0;	//aktualna ilość iteracji bez poprawy
	int krawedzMniejsza, krawedzWieksza;	//potrzebne do dodania do tablicy tabu
	int mniejszySprawdz, wiekszySprawdz;	//do sprawdzenia pary wierzchołków na liście tabu
	int aspiracjaMniejszy, aspiracjaWiekszy;	//wierzcholki do aspiracji
	bool czyMozna = true;	//czy mozna szukac minimum dla podanej pary wierzcholkow

	int* najlepszaiteracja = new int[w];	//permutacja najlepszej drogi w danej iteracji
	int* glownaiteracja = new int[w];	//iteracja od której robimy sąsiadów
	long minodleglosc = 0;//minimalna odleglosc do porownania
	long trasaaktualna = 0;
	int waktualny;	//wierzcholek aktualny
	int l, pomoc;	//zmienne pomocnicze do generowania losowej permutacji
	for (int i = 0; i < w; i++) {
		glownaiteracja[i] = i + 1;
	}
	for (int i = w; i >= 2; i--) {	//generuje losowa permutacje
		l = rand() % i;	//losuje wierzcholek do zamiany dla kazdego wierzcholka
		pomoc = glownaiteracja[l];
		glownaiteracja[l] = glownaiteracja[i - 1];
		glownaiteracja[i - 1] = pomoc;
	}
	//ustalamy dlugosc pierwszej trasy
	waktualny = glownaiteracja[0] - 1;
	wynikk = 0;
	for (int i = 1; i < w; i++) {
		wynikk += macierz[waktualny][glownaiteracja[i] - 1];
		waktualny = glownaiteracja[i] - 1;
	}
	wynikk += macierz[waktualny][glownaiteracja[0] - 1];//wynik dzialania calego algorytmu
	//wynik - najlepsza droga dla danej iteracji
	for (int i = 0; i < w; i++) {
		najlepszaiteracja[i] = glownaiteracja[i];
		permutacja[i] = glownaiteracja[i];
	}

	for (int iter = 0; iter < iteracje; iter++) {	//petla dla podanej ilosci iteracji
		minodleglosc = INT_MAX;
		for (int i = 0; i < w - 2; i++) {	//w petlach wszystkie zamiany dwuwierzchołkowe naszej permutacji
			trasaaktualna = 0;
			for (int j = i + 2; j < w; j++) {
				czyMozna = true;
				if (glownaiteracja[i] < glownaiteracja[j]) {
					mniejszySprawdz = glownaiteracja[i];
					wiekszySprawdz = glownaiteracja[j];
				}
				else {
					mniejszySprawdz = glownaiteracja[j];
					wiekszySprawdz = glownaiteracja[i];
				}
				for (int spr = 0; spr < kadencja; spr++) {	//dla wszystkich wartosci w tablicy tabu
					if (tabu[spr].mniejszy == mniejszySprawdz && tabu[spr].wiekszy == wiekszySprawdz){	//jesli oba wierzcholki sie zgadzaja
						czyMozna = false;
						break;
					}
				}
				if (czyMozna) {	//jeśli krawędzi nie ma na liście tabu
					permutacja[i] = glownaiteracja[j];	//zamiana wierzchołków
					permutacja[j] = glownaiteracja[i];

					//szukamy czy wynik moze byc poprawiony
					waktualny = permutacja[0] - 1;
					for (int k = 1; k < w; k++) {
						trasaaktualna += macierz[waktualny][permutacja[k] - 1];
						waktualny = permutacja[k] - 1;
					}
					trasaaktualna += macierz[waktualny][permutacja[0] - 1];
					if (trasaaktualna < minodleglosc) {	//jesli znalezlismy mniejsza trase
						minodleglosc = trasaaktualna;	//aktualizujemy minimalna trase
						if (permutacja[i] < permutacja[j]) {	//ustalam krawedzi do dodania do listy tabu
							krawedzMniejsza = permutacja[i];
							krawedzWieksza = permutacja[j];
						}
						else {
							krawedzMniejsza = permutacja[j];
							krawedzWieksza = permutacja[i];
						}
						for (int k = 0; k < w; k++) {
							najlepszaiteracja[k] = permutacja[k];	//aktualizujemy wynik
						}
					}
					permutacja[i] = glownaiteracja[i];	//powrot do krawedzi
					permutacja[j] = glownaiteracja[j];
				}
				czyMozna = true;
			}
		}
		if (wynikk < minodleglosc) {	//jesli nie polepszylismy wyniku to sprawdzamy najlepsze rozwiazania z listy tabu
			for (int i = 0; i < aspiracja; i++) {	//dla zadanej wartosci aspiracji
				trasaaktualna = 0;
				int licznikTabu = ((iter%kadencja) - i) % kadencja;
				if (licznikTabu < 0)
					licznikTabu += kadencja;
				aspiracjaMniejszy=tabu[licznikTabu].mniejszy;
				aspiracjaWiekszy=tabu[licznikTabu].wiekszy;
				if (aspiracjaMniejszy == 0 || aspiracjaWiekszy == 0)
					break;
				permutacja[aspiracjaMniejszy - 1] = glownaiteracja[aspiracjaWiekszy - 1];	//zamiana wierzchołków
				permutacja[aspiracjaWiekszy - 1] = glownaiteracja[aspiracjaMniejszy - 1];

				//szukamy czy wynik moze byc poprawiony
				waktualny = permutacja[0] - 1;
				for (int k = 1; k < w; k++) {
					trasaaktualna += macierz[waktualny][permutacja[k] - 1];
					waktualny = permutacja[k] - 1;
				}
				trasaaktualna += macierz[waktualny][permutacja[0] - 1];
				if (trasaaktualna < minodleglosc) {	//jesli znalezlismy mniejsza trase
					minodleglosc = trasaaktualna;	//aktualizujemy minimalna trase
					if (permutacja[aspiracjaMniejszy-1] < permutacja[aspiracjaWiekszy-1]) {	//ustalam krawedzi do dodania do listy tabu
						krawedzMniejsza = permutacja[aspiracjaMniejszy-1];
						krawedzWieksza = permutacja[aspiracjaWiekszy-1];
					}
					else {
						krawedzMniejsza = permutacja[aspiracjaWiekszy-1];
						krawedzWieksza = permutacja[aspiracjaMniejszy-1];
					}
					for (int k = 0; k < w; k++) {
						najlepszaiteracja[k] = permutacja[k];	//aktualizujemy wynik
					}
				}
				permutacja[aspiracjaMniejszy - 1] = glownaiteracja[aspiracjaMniejszy - 1];	//powrot do krawedzi
				permutacja[aspiracjaWiekszy - 1] = glownaiteracja[aspiracjaWiekszy - 1];
			}
		}

		tabuPoz x;	//dodaję x do listy tabu
		x.kadencja = kadencja;
		x.mniejszy = krawedzMniejsza;
		x.wiekszy = krawedzWieksza;
		tabu[iter%kadencja] = x;

		for (int i = 0; i < kadencja; i++) {	//zmniejszenie wszystkich kadencji
			tabu[i].kadencja--;
		}

		if (wynikk > minodleglosc) {	//jeśli znaleźliśmy lepsze rozwiązanie
			for (int i = 0; i < w; i++)
				wynik[i] = najlepszaiteracja[i];
			wynikk=minodleglosc;
			doKrytycznego = 0;
		}
		
		else
			doKrytycznego++;

		if (doKrytycznego >= krytyczne) {	//jesli nastapilo zdarzenie krytyczne
			for (int i = w; i >= 2; i--) {	//generuje losowa permutacje tak jak na początku
				l = rand() % i;
				pomoc = glownaiteracja[l];
				glownaiteracja[l] = glownaiteracja[i - 1];
				glownaiteracja[i - 1] = pomoc;
			}
			tabuPoz x;
			x.kadencja = 0;
			x.mniejszy = 0;
			x.wiekszy = 0;
			for (int i = 0; i < 3 * w; i++)
				tabu[i] = x;
			doKrytycznego = 0;
		}

		for (int i = 0; i < w; i++) {
			glownaiteracja[i] = wynik[i];
			permutacja[i] = glownaiteracja[i];
		}
	}
	delete[] najlepszaiteracja;
}

void Graf::algorytmLokalny2() {
	int* najlepszaiteracja = new int[w];	//permutacja najlepszej drogi w danej iteracji
	long long minodleglosc = 0;//minimalna odleglosc do porownania
	long long trasaaktualna = 0;
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
	minodleglosc = 0;
	wynikk = 0;
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
	for(int jjj=0;jjj<1000;jjj++){
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
	wynikk = minodleglosc;
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