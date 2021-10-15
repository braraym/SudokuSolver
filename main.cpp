#include <iostream>
#include <string>
#include "Sudoku.h"

using namespace std;

int main()
{
	Sudoku sudoku = Sudoku();

	string line;
	for(int y = 0; y <= 8; y++)
	{
		getline(cin, line);
		for(int x = 0; x <= 8; x++)
		{
			int value;
			switch(line[x])
			{
				case '1': value = 1; break;
				case '2': value = 2; break;
				case '3': value = 3; break;
				case '4': value = 4; break;
				case '5': value = 5; break;
				case '6': value = 6; break;
				case '7': value = 7; break;
				case '8': value = 8; break;
				case '9': value = 9; break;
				default: value = 0; break;
			}

			sudoku.setValue(x, y, value);
		}
	}

	int result = sudoku.findSolution() ? 0 : 1;
	cout << sudoku;

	cerr << (result == 0 ? "Complete solution" : "Incomplete solution") << endl;
	return result;
}
