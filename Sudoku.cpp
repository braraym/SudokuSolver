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
	_toProcessBlocks[_getBlock(x, y)] = true;
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

int Sudoku::_getBlock(int x, int y)
{
	return ((x-(x%3))/3)+(y-(y%3));
}

void Sudoku::_processPossibleCells(std::vector<std::tuple<int, int>> cellPossibles, int value)
{
	if(cellPossibles.size() == 1)
	{
		std::tuple<int, int> cell = cellPossibles.front();
		setValue(std::get<0>(cell), std::get<1>(cell), value);
	}
	else if(_areCellsInSameBlock(cellPossibles))
	{
		//all valid cells for `value` are in the same block and line (row or column), so the value can't be on in any other block on that line (row or column)
		std::tuple<int, int> cell = cellPossibles.front();
		int cellX = std::get<0>(cell);
		int cellY = std::get<1>(cell);
		int cellBlock = _getBlock(cellX, cellY);

		if(_areCellsInSameX(cellPossibles))
		{
			//invalidate values on row
			int x = cellX;
			for(int y = 0; y <= 8; y++)
				if(_getBlock(x, y) != cellBlock)
					invalidateValue(x, y, value);

			//invalidate values in block
			for(int x = ((cellBlock%3)*3); x <= ((cellBlock%3)*3)+2; x++)
				if(x != cellX)
					for(int y = cellBlock-(cellBlock%3); y <= (cellBlock-(cellBlock%3))+2; y++)
						invalidateValue(x, y, value);
		}
		else if(_areCellsInSameY(cellPossibles))
		{
			//invalidate values on column
			int y = cellY;
			for(int x = 0; x <= 8; x++)
				if(_getBlock(x, y) != cellBlock)
					invalidateValue(x, y, value);

			//invalidate values in block
			for(int x = ((cellBlock%3)*3); x <= ((cellBlock%3)*3)+2; x++)
				for(int y = cellBlock-(cellBlock%3); y <= (cellBlock-(cellBlock%3))+2; y++)
					if(y != cellY)
						invalidateValue(x, y, value);
		}
	}
}

bool Sudoku::_areCellsInSameX(std::vector<std::tuple<int, int>> cells)
{
	int x = -1;

	for(int i = 0; i < cells.size(); i++)
	{
		std::tuple<int, int> cell = cells.at(i);
		int cellX = std::get<0>(cell);

		if(x == -1)
			x = cellX;
		else if(cellX != x)
			return false;
	}

	return true;
}

bool Sudoku::_areCellsInSameY(std::vector<std::tuple<int, int>> cells)
{
	int y = -1;

	for(int i = 0; i < cells.size(); i++)
	{
		std::tuple<int, int> cell = cells.at(i);
		int cellY = std::get<1>(cell);

		if(y == -1)
			y = cellY;
		else if(cellY != y)
			return false;
	}

	return true;
}

bool Sudoku::_areCellsInSameBlock(std::vector<std::tuple<int, int>> cells)
{
	int block = -1;

	for(int i = 0; i < cells.size(); i++)
	{
		std::tuple<int, int> cell = cells.at(i);
		int cellX = std::get<0>(cell);
		int cellY = std::get<1>(cell);
		int cellBlock = _getBlock(cellX, cellY);

		if(block == -1)
			block = cellBlock;
		else if(cellBlock != block)
			return false;
	}

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
