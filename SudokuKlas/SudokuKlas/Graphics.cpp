#include "Graphics.h"



void Graphics::draw(sf::RenderWindow& window) {
    auto& board = sudokuBoard.getBoard();
    auto selectedCell = sudokuBoard.getSelectedCell();
    sf::Font font;
    font.loadFromFile(fontPath);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);

    // Draw border
    sf::RectangleShape borderRect(sf::Vector2f(cellSize * boardSize, cellSize * boardSize));
    borderRect.setFillColor(sf::Color::White);
    borderRect.setOutlineThickness(5); // Thicker line
    borderRect.setOutlineColor(sf::Color::Black);
    borderRect.setPosition(0, 0);
    window.draw(borderRect);

    // Draw numbers
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j].value != 0) {
                if (board[i][j].initial) {
                    text.setFillColor(sf::Color::Blue); // Set color for initial values to blue
                }
                else {
                    text.setFillColor(sf::Color::Black); // Set color for random values to black
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