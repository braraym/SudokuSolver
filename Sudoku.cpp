#include "Sudoku.h"

Sudoku::Sudoku()
{
	for(int i = 0; i <= 80; i++)
		_cases[i] = Case();

	for(int i = 0; i <= 8; i++)
	{
		_aTraiterLignes[i] = true;
		_aTraiterColonnes[i] = true;
		_aTraiterBlocks[i] = true;
	}
}

bool Sudoku::definirValeur(int x, int y, int valeur)
{
	return _cases[x+y*9].definirValeur(valeur);
}

int Sudoku::recupererValeur(int x, int y)
{
	return _cases[x+y*9].Valeur;
}

bool Sudoku::invaliderValeur(int x, int y, int valeur)
{
	return _cases[x+y*9].invaliderValeur(valeur);
}

bool Sudoku::estPossible(int x, int y, int valeur)
{
	return _cases[x+y*9].estPossible(valeur);
}

void Sudoku::ajouterATraiter(int x, int y)
{
	_aTraiterLignes[y] = true;
	_aTraiterColonnes[x] = true;
	_aTraiterBlocks[((x-(x%3))/3)+(y-(y%3))] = true;
}

bool Sudoku::traiterLigne(int y)
{
	_aTraiterLignes[y] = false;

	for(int x = 0; x <= 8; x++)
	{
		int valeur = recupererValeur(x, y);
		if(valeur != 0)
		{
			for(int x2 = 0; x2 <= 8; x2++)
			{
				if(invaliderValeur(x2, y, valeur))
					ajouterATraiter(x2, y);
			}
		}
	}

	for(int valeur = 1; valeur <= 9; valeur++)
	{
		int nombrePossible = 0;
		int xPossible;
		for(int x = 0; x <= 8; x++)
		{
			if(estPossible(x, y, valeur))
			{
				nombrePossible++;
				xPossible = x;
			}
		}

		if(nombrePossible == 1)
		{
			if(definirValeur(xPossible, y, valeur))
				ajouterATraiter(xPossible, y);
		}
	}

	return _aTraiterLignes[y];
}

bool Sudoku::traiterColonne(int x)
{
	_aTraiterColonnes[x] = false;

	for(int y = 0; y <= 8; y++)
	{
		int valeur = recupererValeur(x, y);
		if(valeur != 0)
		{
			for(int y2 = 0; y2 <= 8; y2++)
				if(invaliderValeur(x, y2, valeur))
					ajouterATraiter(x, y2);
		}
	}

	for(int valeur = 1; valeur <= 9; valeur++)
	{
		int nombrePossible = 0;
		int yPossible;
		for(int y = 0; y <= 8; y++)
		{
			if(estPossible(x, y, valeur))
			{
				nombrePossible++;
				yPossible = y;
			}
		}

		if(nombrePossible == 1)
		{
			if(definirValeur(x, yPossible, valeur))
				ajouterATraiter(x, yPossible);
		}
	}

	return _aTraiterColonnes[x];
}

bool Sudoku::traiterBlock(int b)
{
	_aTraiterBlocks[b] = false;

	for(int x = ((b%3)*3); x <= ((b%3)*3)+2; x++)
	{
		for(int y = b-(b%3); y <= (b-(b%3))+2; y++)
		{
			int valeur = recupererValeur(x, y);
			if(valeur != 0)
			{
				for(int x2 = ((b%3)*3); x2 <= ((b%3)*3)+2; x2++)
				{
					for(int y2 = b-(b%3); y2 <= (b-(b%3))+2; y2++)
						if(invaliderValeur(x2, y2, valeur))
							ajouterATraiter(x2, y2);
				}
			}
		}
	}

	for(int valeur = 1; valeur <= 9; valeur++)
	{
		int nombrePossible = 0;
		int xPossible;
		int yPossible;

		for(int x = ((b%3)*3); x <= ((b%3)*3)+2; x++)
		{
			for(int y = b-(b%3); y <= (b-(b%3))+2; y++)
			{
				if(estPossible(x, y, valeur))
				{
					nombrePossible++;
					xPossible = x;
					yPossible = y;
				}
			}
		}

		if(nombrePossible == 1)
		{
			if(definirValeur(xPossible, yPossible, valeur))
				ajouterATraiter(xPossible, yPossible);
		}
	}

	return _aTraiterBlocks[b];
}

bool Sudoku::trouverSolution(ostream &stream)
{
	bool traiter = true;
	while(traiter)
	{
		traiter = false;
		for(int i = 0; i <= 8; i++)
		{
			if(_aTraiterColonnes[i] && traiterColonne(i))
			{
				stream << "Colonne:" << i << endl;
				traiter = true;
			}

			if(_aTraiterLignes[i] && traiterLigne(i))
			{
				stream << "Ligne:" << i << endl;
				traiter = true;
			}

			if(_aTraiterBlocks[i] && traiterBlock(i))
			{
				stream << "Block:" << i << endl;
				traiter = true;
			}
		}

		if(traiter)
			stream << *this << endl;
	}

	for(int i = 0; i <= 80; i++)
		if(_cases[i].Valeur == 0)
			return false;

	return true;
}

ostream & operator<<(ostream &stream, Sudoku sudoku)
{
	int valeur;
	for(int y = 0; y <= 8; y++)
	{
		for(int x = 0; x <= 8; x++)
		{
			valeur = sudoku.recupererValeur(x, y);
			stream << (valeur != 0 ? to_string(valeur) : " ");
		}
		stream << endl;
	}
	return stream;
}
