

#include"stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>



#include "board.h"
using namespace std;

void sortHighLow(vector<string>&);
void makeCaps(vector<string>&);
bool checkForLetters(string);

int main(int argc, char *argv[]) {





	cout << "\n\n------------------------------------------------" << endl;
	cout << "                     Krzyzowka                      " << endl;
	cout << "------------------------------------------------\n\n" << endl;


	vector<string> list;
	string temp;


	if (argc == 1) {
		// tworzy listę stringow wprowadzona przez uzytkownika
		cout << "Instrukcja:\n\nmax slow: 20\nmax liter 15 " << endl;
		cout << "Jak skonczysz wpisywac slowa postaw '.' i wcisnij ENTER\n" << endl;
		cout << "Wprowadz swoje slowa\n" << endl;

		getline(cin, temp);

		while (temp[0] != '.') {
			if (list.size() == 20) {
				cout << "--------------------------------------------------" << endl;
				cout << "20 slow zostalo umieszczonych - osoganieto maximum" << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "\n" << endl;
				break;
			}
			if (checkForLetters(temp)) {
				list.push_back(temp);
			}
			else {
				cout << "Error: " << temp << " to slowo nie jest poprawne";
				cout << " lub ma za duzo liter (max 15)" << endl;
			}

			getline(cin, temp);
		}

		cout << "\nDziekuje lista zostala zapisana.\n" << endl;
	}


	// Tworzy obiekt Board
	Board board;

	// Sortowanie listy
	sortHighLow(list);
	makeCaps(list);

	// Drukowanie posortowanej listy
	cout << "\n      Posortowana lista slow:       " << endl;
	cout << "--------------------------------------" << endl;
	for (int a = 0; a < list.size(); a++) {
		cout << list[a] << endl;
	}
	cout << endl;

	// Lista --> board
	board.placeList(list);



	// drukowanie ukrytej krzyzowki
	cout << "\n\nUkryta krzyzowka:\n" << endl;
	board.printHidden();

	// drukowanie rozwiazanej krzyzowki
	cout << "---------------------------------------------" << endl;
	cout << "Twoja krzyzowka zostala wygenerowana!" << endl;
	cout << "oto rozwiazanie !:\n" << endl;
	board.printBoard();

	// drukowanie podpwiedzi 
	cout << "\n\nPodpowiedzi odnosnie rozwiazania krzyzowki: \n" << endl;
	for (int s = 0; s < list.size(); s++) {
		random_shuffle(list[s].begin(), list[s].end());
	}

	for (int t = 0; t < list.size(); t++) {
		if (list[t][0] != ' ') {
			cout << "Wiersz: " << board.getRowLoc(t) << ", Kolumna: " << board.getColLoc(t) << endl;

		}
	}

	while (1) {}
	return 0;
} // koniec maina



  // sortowanie listy 
void sortHighLow(vector<string>& list) {
	string temp;
	// algorytm bubble sorta
	for (int i = 0; i<list.size() - 1; i++) {
		for (int j = 0; j<list.size() - i - 1; j++) {
			if (list[j].size() < list[j + 1].size()) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}


void makeCaps(vector<string>& list) {
	for (int i = 0; i<list.size(); i++) {
		for (int j = 0; j<list[i].size(); j++) {
			(list[i])[j] = toupper((list[i])[j]);
		}
	}
}


// sprawdza czy wszystkie litery sa poprawne
bool checkForLetters(string word) {
	// najpierw czy slowo ma mniej niz 15 liter
	if (word.size()>15) return false;
	// nastepnie czy w slowie nie ma cyfr kropek itd 
	for (int i = 0; i<word.size(); i++) {
		if (word[i]<65 || word[i]>122 || (word[i]>90 && word[i]<97)) {
			return false;
		}
	}


	return true;
}