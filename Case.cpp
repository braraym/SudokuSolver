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

	return true;
}

bool Case::invaliderValeur(int valeur)
{
	if(Valeur != 0 || valeur < 1 || valeur > 9)
		return false;

	_estPossible[valeur-1] = false;

	int nombrePossible = 0;
	int valeurPossible = 0;
	for(int i = 0; i <= 8; i++)
	{
		if(_estPossible[i])
		{
			valeurPossible = i+1;
			nombrePossible++;
		}
	}

	return nombrePossible == 1 && definirValeur(valeurPossible);
}
