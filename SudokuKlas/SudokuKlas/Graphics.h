#pragma once
#include "SFML/Graphics.hpp"
#include "SudokuBoard.h"

class Graphics
{
private:
	SudokuBoard& sudokuBoard;
public:
	Graphics(SudokuBoard& sudokuBoard) : sudokuBoard(sudokuBoard) {}
	void draw(sf::RenderWindow& window);
};

