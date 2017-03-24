#include <iostream>
#include "Sudoku.h"

using namespace std;

main()
{
	Sudoku s1 = Sudoku();
	s1.definirValeur(2,0,7);
	s1.definirValeur(3,0,5);
	s1.definirValeur(6,0,6);
	s1.definirValeur(8,0,2);
	s1.definirValeur(1,1,3);
	s1.definirValeur(2,1,1);
	s1.definirValeur(7,1,4);
	s1.definirValeur(8,1,8);
	s1.definirValeur(0,2,4);
	s1.definirValeur(3,2,6);
	s1.definirValeur(8,2,3);
	s1.definirValeur(1,3,1);
	s1.definirValeur(6,3,4);
	s1.definirValeur(8,3,9);
	s1.definirValeur(0,4,9);
	s1.definirValeur(3,4,8);
	s1.definirValeur(4,4,7);
	s1.definirValeur(7,4,5);
	s1.definirValeur(1,5,6);
	s1.definirValeur(0,6,5);
	s1.definirValeur(4,6,9);
	s1.definirValeur(5,6,6);
	s1.definirValeur(7,6,2);
	s1.definirValeur(8,6,1);
	s1.definirValeur(1,7,2);
	s1.definirValeur(2,7,9);
	s1.definirValeur(3,8,7);
	s1.definirValeur(4,8,5);
	s1.definirValeur(7,8,9);

	Sudoku s2 = Sudoku();
	s2.definirValeur(2,0,7);
	s2.definirValeur(4,0,8);
	s2.definirValeur(7,0,2);
	s2.definirValeur(1,1,9);
	s2.definirValeur(4,1,2);
	s2.definirValeur(5,1,1);
	s2.definirValeur(7,1,6);
	s2.definirValeur(2,2,8);
	s2.definirValeur(5,2,3);
	s2.definirValeur(0,3,5);
	s2.definirValeur(1,3,7);
	s2.definirValeur(2,3,9);
	s2.definirValeur(0,4,1);
	s2.definirValeur(3,4,9);
	s2.definirValeur(7,4,7);
	s2.definirValeur(8,5,6);
	s2.definirValeur(1,6,6);
	s2.definirValeur(3,6,7);
	s2.definirValeur(5,6,4);
	s2.definirValeur(8,7,4);
	s2.definirValeur(1,8,8);
	s2.definirValeur(2,8,5);
	s2.definirValeur(3,8,1);
	s2.definirValeur(8,8,2);


	cout << "Sudoku 1" << endl << s1 << endl;
	cout << (s1.trouverSolution(cout) ? "Complet" : "Incomplet") << endl;
	cout << s1 << endl;

	cout << endl << " -  -  -  -  -  -  -  -  - " << endl;
	cout << "Sudoku 2" << endl << s2 << endl;
	cout << (s2.trouverSolution(cout) ? "Complet" : "Incomplet") << endl;
	cout << s2 << endl;

}
