#include <iostream>
#include "Case.h"
using namespace std;

class Sudoku
{
	private:
		Case _cases[81];
		bool _toProcessLines[9];
		bool _toProcessColumns[9];
		bool _toProcessBlocks[9];

	public:
		Sudoku();
		bool setValue(int x, int y, int value);
		int getValue(int x, int y);
		bool invalidateValue(int x, int y, int value);
		bool isValueValid(int x, int y, int value);

		void markToProcess(int x, int y);
		bool processLine(int y);
		bool processColumn(int x);
		bool processBlock(int b);

		bool findSolution();
};

ostream & operator<<(ostream &stream, Sudoku sudoku);
