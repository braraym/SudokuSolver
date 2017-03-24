#include <iostream>
#include "Case.h"
using namespace std;

class Sudoku
{
	private:
		Case _cases[81];
		bool _aTraiterLignes[9];
		bool _aTraiterColonnes[9];
		bool _aTraiterBlocks[9];

		static int numeroBlock(int x, int y);

	public:
		Sudoku();
		bool definirValeur(int x, int y, int valeur);
		int recupererValeur(int x, int y);
		bool invaliderValeur(int x, int y, int valeur);

		void ajouterATraiter(int x, int y);
		bool traiterLigne(int y);
		bool traiterColonne(int x);
		bool traiterBlock(int b);

		bool trouverSolution(ostream &stream);
};

ostream & operator<<(ostream &stream, Sudoku sudoku);
