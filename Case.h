class Case
{
	private:
		bool _estPossible[9];
	public:
		int Valeur;

		Case();
		bool definirValeur(int valeur);
		bool invaliderValeur(int valeur);
};
