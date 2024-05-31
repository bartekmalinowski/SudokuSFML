#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Cell.h"

const int windowWidth = 640;
const int windowHeight = 640;
const int boardSize = 9;
const int cellSize = windowWidth / boardSize;
const std::string fontPath = "arial.ttf";

class SudokuBoard {
private:
    std::vector<std::vector<Cell>> board;
    sf::Vector2i selectedCell;
    int difficulty;
    std::vector<SudokuBoard> boards;
    bool escapePressedDuringGame;
public:
    SudokuBoard();

    std::vector<std::vector<Cell>>& getBoard() {
        return board;
    }
    auto getDifficulty() const { return difficulty; }
    void setSelectedCell(int row, int col);
    sf::Vector2i getSelectedCell() const;
    bool isBoardFilled() const;
    bool setCellValue(int row, int col, int value, bool initial = false);
    void draw(sf::RenderWindow& window);
    bool isNumberValid(int row, int col, int num) const;

};
