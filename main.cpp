#include <iostream>
#include "Sudoku.h"

using namespace std;

main()
{
	Sudoku s = Sudoku();
	s.definirValeur(2,0,7);
	s.definirValeur(3,0,5);
	s.definirValeur(6,0,6);
	s.definirValeur(8,0,2);
	s.definirValeur(1,1,3);
	s.definirValeur(2,1,1);
	s.definirValeur(7,1,4);
	s.definirValeur(8,1,8);
	s.definirValeur(0,2,4);
	s.definirValeur(3,2,6);
	s.definirValeur(8,2,3);
	s.definirValeur(1,3,1);
	s.definirValeur(6,3,4);
	s.definirValeur(8,3,9);
	s.definirValeur(0,4,9);
	s.definirValeur(3,4,8);
	s.definirValeur(4,4,7);
	s.definirValeur(7,4,5);
	s.definirValeur(1,5,6);
	s.definirValeur(0,6,5);
	s.definirValeur(4,6,9);
	s.definirValeur(5,6,6);
	s.definirValeur(7,6,2);
	s.definirValeur(8,6,1);
	s.definirValeur(1,7,2);
	s.definirValeur(2,7,9);
	s.definirValeur(3,8,7);
	s.definirValeur(4,8,5);
	s.definirValeur(7,8,9);

	cout << s << endl;

	cout << (s.trouverSolution(cout) ? "Complet" : "Incomplet") << endl;

	cout << s << endl;
}
