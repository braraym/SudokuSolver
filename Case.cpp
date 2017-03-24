#include "Case.h"
using namespace std;

Case::Case()
{
	Valeur = 0;
	for(int i = 0; i <= 8; i++)
		_estPossible[i] = true;
}

bool Case::definirValeur(int valeur)
{
	if(Valeur != 0 || valeur < 1 || valeur > 9)
		return false;

	Valeur = valeur;
	for(int i = 0; i <= 8; i++)
		_estPossible[i] = false;

	_estPossible[valeur-1] = true;

	return true;
}

bool Case::invaliderValeur(int valeur)
{
	if(Valeur != 0 || valeur < 1 || valeur > 9 || !_estPossible[valeur-1])
		return false;

	_estPossible[valeur-1] = false;

	int nombrePossible = 0;
	int valeurPossible;
	for(int v = 1; v <= 9; v++)
	{
		if(_estPossible[v-1])
		{
			valeurPossible = v;
			nombrePossible++;
		}
	}

	if(nombrePossible == 1)
		definirValeur(valeurPossible);

	return true;
}

bool Case::estPossible(int valeur)
{
	return _estPossible[valeur-1];
}
