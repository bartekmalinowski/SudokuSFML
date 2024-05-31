#pragma once
#include "SudokuBoard.h"
#include <SFML/Graphics.hpp>

class InputHandler
{
private:
	SudokuBoard& sudokuBoard;
public:
	InputHandler(SudokuBoard& sudokuBoard) : sudokuBoard(sudokuBoard) {}
	InputHandler() : sudokuBoard(*(new SudokuBoard())) {}
	void handleKeyPress(sf::Keyboard::Key key);
};

