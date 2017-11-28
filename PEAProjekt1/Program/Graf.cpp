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
	D.clear();
	wynik = new int[w];
}

Graf::~Graf() {
	D.clear();
	for (int i = 0; i < w; i++)
		delete[] macierz[i];
	delete[] macierz;
	delete[] wynik;
}

void Graf::clear() {
	D.clear();
	settt.clear();
}

int Graf::rekurencja(vector<int> set) {
	//podzbiory 1-elementowych - tylko odczyt danych z macierzy
	wartoscMinimum minn;
	if (set.size() == 2) {
		minn.wartosc = macierz[0][set.front()];
		minn.minimum = set.front();
		D.insert(pair<vector<int>, wartoscMinimum>(set, minn));
		return minn.wartosc;
	}
	map<vector<int>, wartoscMinimum>::iterator help;
	vector<int> help2;
	int min = INT_MAX;
	int minaktualne;
		
	for (int p = 0; p < set.size(); p++)
		help2.push_back(set.at(p));
	int pp = set.back();
	set.pop_back();	//wyrzucam ostatni element wektora (koncowy wierzcholek)
	for (int k = 0; k < set.size(); k++) {
		if (set.at(k) == pp) {
			set.erase(set.begin() + k);	//wyrzucam element rowny ostatniemu
			break;
		}
	}
	int najmniejszy = set.front();
	for (int j = 0; j < set.size(); j++) {
		set.push_back(set.at(j));
		help = D.find(set);
		if (help == D.end()) {	//jesli set nie istnieje w mapie
			minaktualne = rekurencja(set) + macierz[set.at(j)][pp];	//to wywolujemy dla niego rekurencje
		}
		else {	//jesli istnieje
			minaktualne = help->second.wartosc + macierz[set.at(j)][pp];	//to bierzemy jego wartosc i wartosc do nastepnego wierzcholka
		}
		if (minaktualne < min) {	//patrzymy na minimum do tej pory
			min = minaktualne;	//wartosc minimalna
			najmniejszy = set.at(j);	//ustalamy najmniejszy element zbioru do znalezienia sciezki
			//czyli minimum
		}
		set.pop_back();
	}
	minn.wartosc = min;
	minn.minimum = najmniejszy;
	D.insert(pair<vector<int>, wartoscMinimum>(help2, minn));	//dodajemy set do mapy
	return min;
}

void Graf::algorytmBHKRekurencja() { //alg. Bellmana-Helda-Karpa rekurencyjny
	int *tab = new int[w - 1];	//tablica do obliczania minimum
	int *sciezka = new int[w];	//sciezka minimalnej trasy
	int minimumCalkowite;
	ktoryOstatni = 1;
	wartoscMinimum minn;
	for (int i = 1; i < w; i++) {
		settt.push_back(i);
	}

	settt.push_back(1);
	tab[0] = rekurencja(settt) + macierz[1][0];	//wywołanie pierwszej rekurencji (ostatnie miasto=1)
	wynikk = tab[0];
	for (int p = 1; p < settt.size() - 1; p++) {	//dla wszystkich wartości
		settt.pop_back();
		settt.push_back(p + 1);
		tab[p] = rekurencja(settt) + macierz[p + 1][0];	//wywolujemy rekurencyjna funkcje podajac pelny zbior wierzcholkow z roznymi wierzcholkami koncowymi
		if (tab[p] < wynikk) {	//jeśli znaleźliśmy minimum - zapisujemy je
			wynikk = tab[p];
			ktoryOstatni = p + 1;
		}
	}
	cout << endl;
	delete tab;
	delete sciezka;
	/*for (auto elem : D) {	//wypisanie wszystkich podzbiorow i ich wag
		cout << "[ ";
		for (int i = 0; i < elem.first.size(); ++i)
		cout << elem.first.at(i) << ' ';
		cout << "]  ";
		cout << elem.second.minimum << "   " << elem.second.wartosc << endl;
	}*/
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
	/*for (auto elem : D) {	//wypisanie wszystkich podzbiorow i ich wag
	cout << "[ ";
	for (int i = 0; i < elem.first.size(); ++i)
	cout << elem.first.at(i) << ' ';
	cout << "]  ";
	cout << elem.second.minimum << "   " << elem.second.wartosc << endl;
	}*/
	if (ktoryOstatni != -1) {
		cout << "Minimum: " << wynikk << endl;
		//wyznaczenie sciezki
		while (!settt.empty())
			settt.pop_back();
		wynik[0] = ktoryOstatni;
		for (int i = 1; i < w; i++) {
			settt.push_back(i);
		}
		settt.push_back(ktoryOstatni);
		int n, push;
		for (int i = 1; i < w - 1; i++) {
			n = settt.back();
			push = D.find(settt)->second.minimum;
			settt.pop_back();
			for (int k = 0; k < settt.size(); k++) {
				if (settt.at(k) == n) {
					settt.erase(settt.begin() + k);	//wyrzucam element rowny ostatniemu
					break;
				}
			}
			settt.push_back(push);
			wynik[i] = push;
		}
		cout << "Sciezka: 0 ";
		/*cout << macierz[0][wynik[w - 2]] << " + ";
		for (int q = 1; q < w - 1; q++) {
			cout << macierz[wynik[w - q - 1]][wynik[w - q - 2]] << " + ";
		}
		cout << macierz[wynik[0]][0];
		cout << endl;*/

		cout << " ( " << macierz[0][wynik[w - 2]] << " ) " << wynik[w - 2];
		for (int q = 1; q < w - 1; q++) {
			cout << " ( " << macierz[wynik[w - q - 1]][wynik[w - q - 2]] << " ) " << wynik[w - q - 2];
		}
		cout << " ( " << macierz[wynik[0]][0] << " ) 0.";
		cout << endl;
	}
	clear();
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
	int r;
	for (int j = 1; j < w; j++) {
		for (int k = 0; k < j; k++) {
			r = rand();
			macierz[j][k] = r;
			macierz[k][j] = r;
		}
	}
}