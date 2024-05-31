#pragma once
#include <fstream>
#include <regex>
#include <filesystem>
#include <iostream>
#include "SudokuBoard.h"


class FileHandler
{
private:
	SudokuBoard& sudokuBoard;
public:
	FileHandler(SudokuBoard& sudokuBoard) : sudokuBoard(sudokuBoard) {}
	FileHandler() : sudokuBoard(*(new SudokuBoard())) {}
	void saveBoardToFile(const std::string& filename);
	void loadBoardFromFile(const std::string& filename);
};

