

#include"stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

#include "board.h"

Board::Board() {
	// tworzy tablice 15x15 
	for (int i = 0; i<15; i++) {
		for (int j = 0; j<15; j++) {
			data[i][j] = '_';
		}
	}
	// zaczynamy od punktu (0,0)
	for (int row = 0; row<20; row++) {
		for (int col = 0; col<2; col++) {
			locations[row][col] = 0;
		}
	}
	
	place = 1;

	// sprawdza gdzie bylo poprzednie slowo
	for (int i = 0; i<20; i++) {
		direction[i] = " ";
	}
}

// destructor
Board::~Board() {}

// printBoard pokazuje odpowiedzi krzyzowki
void Board::printBoard() {
	for (int i = 0; i<15; i++) {
		for (int j = 0; j<15; j++) {
			cout << data[i][j];
			// miejsce miedzy kolumnami i wierszami
			cout << " ";
		}
		cout << endl;
	}
}


// printHidden method pokazuje ktore pola nie sa wypelnione naszymi wyrazami
void Board::printHidden() {

	
	

	for (int i = 0; i<15; i++) {
		for (int j = 0; j<15; j++) {
			int n = rand() % 26; // generowanie losowych liter
			char c = (char)(n + 65);
			if (data[i][j] == '_') cout << c;
			else cout << data[i][j];
			// dodaje miejsce miedzy wierszami i kolumnami
			cout << " ";
		}
		cout << endl;
	}

}


void Board::setSpot(char c, int row, int col) {
	data[row][col] = c;
}


// getRowLoc zwraca wiersz w ktorym slowo bylo umieszczone 
int Board::getRowLoc(int x) {
	return locations[x][0] + 1; //dodaje 1 do wspolrzednych 1-15 nie  0-14
}


// getColLoc zwraca kolumne w ktorym slowo bylo umieszczone
int Board::getColLoc(int y) {
	return locations[y][1] + 1; // dodaje 1 do wspolrzednych 1-15 nie  0-14
}



// placeList pobiera liste z maina do Boardu
void Board::placeList(vector<string>& list) {
	int hold;

	for (int i = 0; i<list.size(); i++) {
		if (i == 0) {
			for (int j = 0; j<list[0].size(); j++) {
				// miejsce pierwsze slowo w srodku horyzontalnie
				setSpot((list[0])[j], 7, (15 - list[0].size()) / 2 + j);
				direction[0] = "POZIOMO";
			}
			locations[0][0] = 7;
			locations[0][1] = (15 - list[0].size()) / 2;
		} // jeœli powyzszy algorytm nie zadziala

		if (i != 0 && i % 2 == 0) {
			if (placeNextVer(list[i])) {
				direction[i] = "PIONOWO";
			}
			else if (placeNextHor(list[i])) {
				direction[i] = "POZIOMO";
			}
			else {
				cout << "Nie mozna umiescic slowa: " << list[i] << endl;
				list[i] = " ";
				place++;
				direction[i] = " ";
			}
		}
		else if (i != 0 && i % 2 != 0) {
			if (placeNextHor(list[i])) {
				direction[i] = "POZIOMO";
			}
			else if (placeNextVer(list[i])) {
				direction[i] = "PIONOWO";
			}
			else {
				cout << "Nie mozna umiescic slowa: " << list[i] << endl;
				list[i] = " ";
				place++;
				direction[i] = " ";
			}
		}
	} 
} 



char Board::getSpot(int i, int j) {
	return data[i][j];
}

string Board::getDir(int x) {
	return direction[x];
}



// placeNextVer metoda stara sie znalezc nastepne slowo i umiescic je , horyzontalnie
bool Board::placeNextVer(string word) {
	int match = 0;
	bool isPlaced = 0, key = 0;
	for (int j = 0; j<15; j++) {
		for (int i = 0; i<15 + 1 - word.size(); i++) {
			for (int k = 0; k<word.size(); k++) {
				if (getSpot(i + k, j) == '_' || getSpot(i + k, j) == word[k]) {
					match++;
				}
				if (getSpot(i + k, j) == word[k]) {
					if (getSpot(i + k + 1, j) == '_' && getSpot(i + k - 1, j) == '_') {
						match = match + 2;
						key = 1;
					}
				}
				if (getSpot(i + k, j + 1) == '_'&&getSpot(i + k, j - 1) == '_') {
					match = match + 2;
				}
				if (getSpot(i - 1, j) == '_' && getSpot((i + word.size()), j) == '_') {
					if (k == 0) match = match + 2;
				}
			} 
			if (match == 3 * word.size() + 2 && key == 1 && isPlaced == 0) {
				// umieszczaeni slowa
				for (int p = 0; p<word.size(); p++) {
					setSpot(word[p], i + p, j);
				}
				// ustawia isPlaced na prawdziwe
				isPlaced = 1;
				// podaje wspolrzedne nowo wstawionego slowa
				locations[place][0] = i;
				locations[place][1] = j;
				place++;
				return 1;

			}
			match = 0;
			key = 0;
		} 
	} 
	return 0; 
} 



  // placeNextHor metoda stara sie umiescic kolejne pionowo
bool Board::placeNextHor(string word) {
	int match = 0;
	bool isPlaced = 0, key = 0;
	for (int j = 0; j<15; j++) {
		for (int i = 0; i<15 + 1 - word.size(); i++) {
			for (int k = 0; k<word.size(); k++) {
				if (getSpot(j, i + k) == '_' || getSpot(j, i + k) == word[k]) {
					match++;
				}
				if (getSpot(j, i + k) == word[k]) {
					if (getSpot(j, i + k + 1) == '_' && getSpot(j, i + k - 1) == '_') {
						match = match + 2;
						key = 1;
					}
				}
				if (getSpot(j + 1, i + k) == '_'&&getSpot(j - 1, i + k) == '_') {
					match = match + 2;
				}
				if (getSpot(j, i - 1) == '_' && getSpot(j, i + word.size()) == '_') {
					if (k == 0) match = match + 2;
				}
			} 
			if (match == 3 * word.size() + 2 && key == 1 && isPlaced == 0) {
				// umiesznienie slowa
				for (int p = 0; p<word.size(); p++) {
					setSpot(word[p], j, i + p);
				}
				locations[place][0] = j;
				locations[place][1] = i;
				place++;

				// ustawia isPlaced na true
				isPlaced = 1;
				return 1;

			}
			match = 0;
			key = 0;
		} 
	} 
	return 0;
} 




  // findMatch sprawdzanie poprawnosci
int Board::findMatch(string word) {
	for (int i = 0; i<15; i++) {
		for (int j = 0; j<15; j++) {
			for (int k = 0; k<word.size(); k++) {
				if (word[k] == getSpot(i, j)) return 1;
			}
		}
	}
	while (1)
		return 0;
}
