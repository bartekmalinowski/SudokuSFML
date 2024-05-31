#include "SudokuBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ranges>
#include "SudokuSolver.h"



SudokuBoard::SudokuBoard() {
    for (int i = 0; i < boardSize; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < boardSize; ++j) {
            Cell cell;
            row.push_back(cell);
        }
        board.push_back(row);
    }
    selectedCell = sf::Vector2i(-1, -1);
    srand(time(nullptr));
    difficulty = 0; // Initialize difficulty to 0
    escapePressedDuringGame = false;
}

bool SudokuBoard::setCellValue(int row, int col, int value, bool initial) {
    if (!isNumberValid(row, col, value)) {
        return false;
    }
    board[row][col].value = value;
    board[row][col].initial = initial;
    return true;
}

void SudokuBoard::setSelectedCell(int row, int col) {
    selectedCell.x = row;
    selectedCell.y = col;
}

sf::Vector2i SudokuBoard::getSelectedCell() const {
    return selectedCell;
}

bool SudokuBoard::isBoardFilled() const {
    return std::ranges::all_of(board, [](const auto& row) {
        return std::ranges::all_of(row, [](const Cell& cell) {
            return cell.value != 0;
            });
        });
}

void SudokuBoard::draw(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile(fontPath);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);

    // Draw border
    sf::RectangleShape borderRect(sf::Vector2f(cellSize * boardSize, cellSize * boardSize));
    borderRect.setFillColor(sf::Color::White);
    borderRect.setOutlineThickness(5); 
    borderRect.setOutlineColor(sf::Color::Black);
    borderRect.setPosition(0, 0);
    window.draw(borderRect);

    // Draw numbers
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j].value != 0) {
                if (board[i][j].initial) {
                    text.setFillColor(sf::Color::Blue); 
                }
                else {
                    text.setFillColor(sf::Color::Black); 
                }
                text.setString(std::to_string(board[i][j].value));
                text.setPosition(j * cellSize + 0.4 * cellSize, i * cellSize);
                window.draw(text);
            }
        }
    }

    // Draw vertical lines to separate numbers
    sf::VertexArray verticalLines(sf::Lines, 2);
    verticalLines[0].color = sf::Color::Black;
    verticalLines[1].color = sf::Color::Black;
    for (int i = 1; i < boardSize; ++i) {
        verticalLines[0].position = sf::Vector2f(i * cellSize, 0);
        verticalLines[1].position = sf::Vector2f(i * cellSize, windowHeight);
        window.draw(verticalLines);
    }

    // Draw horizontal lines to separate numbers
    sf::VertexArray horizontalLines(sf::Lines, 2);
    horizontalLines[0].color = sf::Color::Black;
    horizontalLines[1].color = sf::Color::Black;
    for (int i = 1; i < boardSize; ++i) {
        horizontalLines[0].position = sf::Vector2f(0, i * cellSize);
        horizontalLines[1].position = sf::Vector2f(windowWidth, i * cellSize);
        window.draw(horizontalLines);
    }

    // Draw thicker lines around each 3x3 grid
    sf::RectangleShape thickerLines(sf::Vector2f(5, cellSize * boardSize));
    thickerLines.setFillColor(sf::Color::Black);
    window.draw(thickerLines);
    thickerLines.setSize(sf::Vector2f(cellSize * boardSize, 5));
    thickerLines.setPosition(0, 0);
    window.draw(thickerLines);

    for (int i = 1; i < 3; ++i) {
        thickerLines.setSize(sf::Vector2f(5, cellSize * boardSize));
        thickerLines.setPosition(i * 3 * cellSize - 2, 0);
        window.draw(thickerLines);
        thickerLines.setSize(sf::Vector2f(cellSize * boardSize, 5));
        thickerLines.setPosition(0, i * 3 * cellSize - 2);
        window.draw(thickerLines);
    }

    // Draw rectangle around selected cell
    if (selectedCell.x != -1 && selectedCell.y != -1) {
        sf::RectangleShape selectionRect(sf::Vector2f(cellSize, cellSize));
        selectionRect.setFillColor(sf::Color(255, 255, 255, 128));
        selectionRect.setOutlineThickness(2);
        selectionRect.setOutlineColor(sf::Color::Blue);
        selectionRect.setPosition(selectedCell.y * cellSize, selectedCell.x * cellSize);
        window.draw(selectionRect);
    }
}


bool SudokuBoard::isNumberValid(int row, int col, int num) const {
    // Check if num already exists in the same row or column
    for (int i = 0; i < boardSize; ++i) {
        if (board[row][i].value == num || board[i][col].value == num) {
            return false;
        }
    }

    // Check if num already exists in the same 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (board[i][j].value == num) {
                return false;
            }
        }
    }

    return true;
}

