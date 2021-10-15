all: sudoku_solver clean

sudoku_solver: main.o Sudoku.o Case.o
	gcc -o sudoku_solver main.o Sudoku.o Case.o -lstdc++

main.o: main.cpp
	gcc -o main.o -c main.cpp

Sudoku.o: Sudoku.h Sudoku.cpp
	gcc -o Sudoku.o -c Sudoku.cpp

Case.o: Case.h Case.cpp
	gcc -o Case.o -c Case.cpp

clean:
	rm Case.o Sudoku.o main.o
