class Case
{
	private:
		int _value;
		bool _isValueValids[9];

	public:
		Case();
		Case(int value);
		int getValue();
		bool setValue(int value);
		bool invalidateValue(int value);
		bool isValueValid(int value);
};
