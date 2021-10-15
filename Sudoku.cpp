#include "Sudoku.h"

Sudoku::Sudoku()
{
	for(int i = 0; i <= 80; i++)
		_cases[i] = Case();

	for(int i = 0; i <= 8; i++)
	{
		_toProcessRow[i] = true;
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
	_toProcessRow[y] = true;
	_toProcessColumns[x] = true;
	_toProcessBlocks[((x-(x%3))/3)+(y-(y%3))] = true;
}

bool Sudoku::processRow(int y)
{
	_toProcessRow[y] = false;

	for(int x = 0; x <= 8; x++)
	{
		int value = getValue(x, y);
		if(value != 0)
			for(int x2 = 0; x2 <= 8; x2++)
				invalidateValue(x2, y, value);
	}

	for(int value = 1; value <= 9; value++)
	{
		std::vector<std::tuple<int, int>> cellPossibles;

		for(int x = 0; x <= 8; x++)
			if(isValueValid(x, y, value))
				cellPossibles.push_back(std::make_tuple(x, y));

		_processPossibleCells(cellPossibles, value);
	}

	return _toProcessRow[y];
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
		std::vector<std::tuple<int, int>> cellPossibles;

		for(int y = 0; y <= 8; y++)
			if(isValueValid(x, y, value))
				cellPossibles.push_back(std::make_tuple(x, y));

		_processPossibleCells(cellPossibles, value);
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
		std::vector<std::tuple<int, int>> cellPossibles;

		for(int x = ((b%3)*3); x <= ((b%3)*3)+2; x++)
			for(int y = b-(b%3); y <= (b-(b%3))+2; y++)
				if(isValueValid(x, y, value))
					cellPossibles.push_back(std::make_tuple(x, y));

		_processPossibleCells(cellPossibles, value);
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

			if(_toProcessRow[i] && processRow(i))
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

void Sudoku::_processPossibleCells(std::vector<std::tuple<int, int>> cellPossibles, int value)
{
	if(cellPossibles.size() == 1)
	{
		std::tuple<int, int> cell = cellPossibles.front();
		setValue(std::get<0>(cell), std::get<1>(cell), value);
	}
	else if(false) //todo
	{
		//all valid cells for `value` are in the same block and line (row or column), so the value can't be on in any other block on that line (row or column)
	}
}

bool Sudoku::_areCellsInSameBlockAndLine(std::vector<std::tuple<int, int>> cells)
{
	return false;
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
