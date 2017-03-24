#include <iostream>
#include <string>
#include "Sudoku.h"

using namespace std;

int main()
{
	Sudoku sudoku = Sudoku();

	string ligne;
	for(int y = 0; y <= 8; y++)
	{
		getline(cin, ligne);
		for(int x = 0; x <= 8; x++)
		{
			int valeur;
			switch(ligne[x])
			{
				case '1': valeur = 1; break;
				case '2': valeur = 2; break;
				case '3': valeur = 3; break;
				case '4': valeur = 4; break;
				case '5': valeur = 5; break;
				case '6': valeur = 6; break;
				case '7': valeur = 7; break;
				case '8': valeur = 8; break;
				case '9': valeur = 9; break;
				default: valeur = 0; break;
			}
			sudoku.definirValeur(x, y, valeur);
		}
	}

	int retour = sudoku.trouverSolution() ? 0 : 1;
	cout << sudoku;

	cerr << (retour == 0 ? "Complete solution" : "Incomplete solution") << endl;
	return retour;
}
