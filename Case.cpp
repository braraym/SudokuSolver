#include "Case.h"
using namespace std;

Case::Case() : Case(0) { }

Case::Case(int value = 0)
{
	_value = value;
	for(int i = 0; i <= 8; i++)
		_isValueValids[i] = value == 0;
}

int Case::getValue()
{
	return _value;
}

bool Case::setValue(int value)
{
	if(_value != 0 || value < 1 || value > 9)
		return false;

	_value = value;
	for(int i = 0; i <= 8; i++)
		_isValueValids[i] = false;

	_isValueValids[value-1] = true;

	return true;
}

bool Case::invalidateValue(int value)
{
	if(_value != 0 || value < 1 || value > 9 || !_isValueValids[value-1])
		return false;

	_isValueValids[value-1] = false;

	//Check if only a single possible value is remaining
	int newValue = 0;
	for(int i = 0; i <= 8; i++)
	{
		if(_isValueValids[i])
		{
			if(newValue != 0)
				return true;

			newValue = i + 1;
		}
	}

	_value = newValue;
	return true;
}

bool Case::isValueValid(int value)
{
	return _isValueValids[value-1];
}
