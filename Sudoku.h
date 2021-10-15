#include <iostream>
#include <vector>
#include <tuple>
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
		int getValue(int x, int y);
		void setValue(int x, int y, int value);
		void invalidateValue(int x, int y, int value);
		bool isValueValid(int x, int y, int value);

		void markToProcess(int x, int y);
		bool processLine(int y);
		bool processColumn(int x);
		bool processBlock(int b);

		bool findSolution();
};

ostream & operator<<(ostream &stream, Sudoku sudoku);
