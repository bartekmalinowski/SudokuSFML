#pragma once

#include <SFML/Graphics.hpp>
#include "SudokuBoard.h"
#include "SudokuGenerator.h"
#include "FileHandler.h"
#include "SudokuCheck.h"
#include "InputHandler.h"
#include "SudokuSolver.h"

class SudokuGame {
public:
    SudokuGame();
    void run();

private:
    void processEvents();
    void render();
    void handleMenuEvent(const sf::Event& event);
    void handleGameEvent(const sf::Event& event);
    void handleGameOverEvent(const sf::Event& event);
    void drawMenu();
    void drawGame();
    void drawGameOver();
    void showMessage(const sf::Text& message);

    sf::RenderWindow window;
    SudokuBoard sudokuBoard;
    FileHandler fileHandler;
    SudokuCheck sudokuCheck;
    InputHandler inputHandler;
    SudokuSolver sudokuSolver;

    sf::Font font;
    sf::Text playButton, loadButton, saveButton, exitButton;
    sf::Text gameOverPlayAgainButton, gameOverCheckButton, gameOverSaveButton, gameOverExitButton, returnToGameButton;
    sf::Text easyButton, mediumButton, hardButton;

    bool isMenuOpen;
    bool isGameRunning;
    bool isGameOver;
    int difficulty;
};
