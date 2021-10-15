#include "Sudoku.h"

Sudoku::Sudoku()
{
	for(int i = 0; i <= 80; i++)
		_cases[i] = Case();

	for(int i = 0; i <= 8; i++)
	{
		_toProcessLines[i] = true;
		_toProcessColumns[i] = true;
		_toProcessBlocks[i] = true;
	}
}

int Sudoku::getValue(int x, int y)
{
	return _cases[x+y*9].getValue();
}

void Sudoku::setValue(int x, int y, int value)
{
	if(_cases[x+y*9].setValue(value))
		markToProcess(x, y);
}

void Sudoku::invalidateValue(int x, int y, int value)
{
	if(_cases[x+y*9].invalidateValue(value))
		markToProcess(x, y);
}

bool Sudoku::isValueValid(int x, int y, int value)
{
	return _cases[x+y*9].isValueValid(value);
}

void Sudoku::markToProcess(int x, int y)
{
	_toProcessLines[y] = true;
	_toProcessColumns[x] = true;
	_toProcessBlocks[((x-(x%3))/3)+(y-(y%3))] = true;
}

bool Sudoku::processLine(int y)
{
	_toProcessLines[y] = false;

	for(int x = 0; x <= 8; x++)
	{
		int value = getValue(x, y);
		if(value != 0)
			for(int x2 = 0; x2 <= 8; x2++)
				invalidateValue(x2, y, value);
	}

	for(int value = 1; value <= 9; value++)
	{
		std::vector<int> xPossibles;
		for(int x = 0; x <= 8; x++)
			if(isValueValid(x, y, value))
				xPossibles.push_back(x);

		if(xPossibles.size() == 1)
		{
			setValue(xPossibles.front(), y, value);
		}
		else if(false) //todo
		{
			//all valid cells for `value` are in the same block, so the value can't be on any other row in that block
		}
	}

	return _toProcessLines[y];
}

bool Sudoku::processColumn(int x)
{
	_toProcessColumns[x] = false;

	for(int y = 0; y <= 8; y++)
	{
		int value = getValue(x, y);
		if(value != 0)
			for(int y2 = 0; y2 <= 8; y2++)
				invalidateValue(x, y2, value);
	}

	for(int value = 1; value <= 9; value++)
	{
		std::vector<int> yPossibles;
		for(int y = 0; y <= 8; y++)
			if(isValueValid(x, y, value))
				yPossibles.push_back(y);

		if(yPossibles.size() == 1)
		{
			setValue(x, yPossibles.front(), value);
		}
		else if(false) //todo
		{
			//all valid cells for `value` are in the same block, so the value can't be on any other column in that block
		}
	}

	return _toProcessColumns[x];
}

bool Sudoku::processBlock(int b)
{
	_toProcessBlocks[b] = false;

	for(int x = ((b%3)*3); x <= ((b%3)*3)+2; x++)
	{
		for(int y = b-(b%3); y <= (b-(b%3))+2; y++)
		{
			int value = getValue(x, y);
			if(value != 0)
				for(int x2 = ((b%3)*3); x2 <= ((b%3)*3)+2; x2++)
					for(int y2 = b-(b%3); y2 <= (b-(b%3))+2; y2++)
						invalidateValue(x2, y2, value);
		}
	}

	for(int value = 1; value <= 9; value++)
	{
		std::vector<std::tuple<int, int>> xyPossibles;

		for(int x = ((b%3)*3); x <= ((b%3)*3)+2; x++)
			for(int y = b-(b%3); y <= (b-(b%3))+2; y++)
				if(isValueValid(x, y, value))
					xyPossibles.push_back(std::make_tuple(x, y));


		if(xyPossibles.size() == 1)
		{
			std::tuple<int, int> tuple = xyPossibles.front();
			setValue(std::get<0>(tuple), std::get<1>(tuple), value);
		}
		else if(false) //todo
		{
			//all valid cells for `value` are in the same row/column for that block, so the value can't be on in any other block for that row/column
		}
	}

	return _toProcessBlocks[b];
}

bool Sudoku::findSolution()
{
	bool keepProcessing;

	do
	{
		keepProcessing = false;
		for(int i = 0; i <= 8; i++)
		{
			if(_toProcessColumns[i] && processColumn(i))
				keepProcessing = true;

			if(_toProcessLines[i] && processLine(i))
				keepProcessing = true;

			if(_toProcessBlocks[i] && processBlock(i))
				keepProcessing = true;
		}
	}
	while(keepProcessing);

	for(int i = 0; i <= 80; i++)
		if(_cases[i].getValue() == 0)
			return false;

	return true;
}

ostream & operator<<(ostream &stream, Sudoku sudoku)
{
	int value;
	for(int y = 0; y <= 8; y++)
	{
		for(int x = 0; x <= 8; x++)
		{
			value = sudoku.getValue(x, y);
			stream << (value != 0 ? to_string(value) : " ");
		}
		stream << endl;
	}
	return stream;
}
