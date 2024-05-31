#pragma once
#include "SudokuBoard.h"


class SudokuCheck
{
private:
	SudokuBoard& sudokuBoard;


public:
	SudokuCheck(SudokuBoard& sudokuBoard) : sudokuBoard(sudokuBoard) {}
	SudokuCheck() : sudokuBoard(*(new SudokuBoard())) {}
	bool checkSolution() const;
	bool checkSolutionAsync() const;

};

