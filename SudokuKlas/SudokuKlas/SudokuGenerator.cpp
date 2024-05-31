#include "SudokuGenerator.h"

SudokuGame::SudokuGame()
    : window(sf::VideoMode(windowWidth, windowHeight), "Sudoku"),
    fileHandler(sudokuBoard), sudokuCheck(sudokuBoard), inputHandler(sudokuBoard),
    sudokuSolver(sudokuBoard, 0), isMenuOpen(true), isGameRunning(false), isGameOver(false), difficulty(0) {

    font.loadFromFile(fontPath);

    playButton.setFont(font);
    playButton.setString("Play");
    playButton.setCharacterSize(30);
    playButton.setPosition(290, 290);

    loadButton.setFont(font);
    loadButton.setString("Load");
    loadButton.setCharacterSize(30);
    loadButton.setPosition(290, 320);

    exitButton.setFont(font);
    exitButton.setString("Exit");
    exitButton.setCharacterSize(30);
    exitButton.setPosition(290, 350);

    gameOverPlayAgainButton.setFont(font);
    gameOverPlayAgainButton.setString("Play again");
    gameOverPlayAgainButton.setCharacterSize(30);
    gameOverPlayAgainButton.setPosition(290, 270);

    gameOverCheckButton.setFont(font);
    gameOverCheckButton.setString("Check");
    gameOverCheckButton.setCharacterSize(30);
    gameOverCheckButton.setPosition(290, 300);

    gameOverSaveButton.setFont(font);
    gameOverSaveButton.setString("Save");
    gameOverSaveButton.setCharacterSize(30);
    gameOverSaveButton.setPosition(290, 330);

    gameOverExitButton.setFont(font);
    gameOverExitButton.setString("Exit");
    gameOverExitButton.setCharacterSize(30);
    gameOverExitButton.setPosition(290, 360);

    returnToGameButton.setFont(font);
    returnToGameButton.setString("Return to game");
    returnToGameButton.setCharacterSize(30);
    returnToGameButton.setPosition(290, 240);

    easyButton.setFont(font);
    easyButton.setString("Easy");
    easyButton.setCharacterSize(30);
    easyButton.setPosition(290, 290);

    mediumButton.setFont(font);
    mediumButton.setString("Medium");
    mediumButton.setCharacterSize(30);
    mediumButton.setPosition(290, 320);

    hardButton.setFont(font);
    hardButton.setString("Hard");
    hardButton.setCharacterSize(30);
    hardButton.setPosition(290, 350);
}

void SudokuGame::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void SudokuGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (isMenuOpen) {
                handleMenuEvent(event);
            }
            else if (isGameRunning) {
                handleGameEvent(event);
            }
            else if (isGameOver) {
                handleGameOverEvent(event);
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (isGameRunning) {
                    isGameOver = true;
                    isGameRunning = false;
                }
                else {
                    isMenuOpen = true;
                    isGameRunning = false;
                }
            }
            else if (event.key.code == sf::Keyboard::R) {
                sudokuSolver.generateNewBoard(sudokuBoard, difficulty);
            }
            else {
                inputHandler.handleKeyPress(event.key.code);
            }
        }
    }
}

void SudokuGame::render() {
    window.clear();
    if (isMenuOpen) {
        drawMenu();
    }
    else if (isGameRunning) {
        drawGame();
    }
    else if (isGameOver) {
        drawGameOver();
    }
    window.display();
}

void SudokuGame::handleMenuEvent(const sf::Event& event) {
    if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isMenuOpen = false;
        while (true) {
            window.clear();
            window.draw(easyButton);
            window.draw(mediumButton);
            window.draw(hardButton);
            window.display();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (easyButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        difficulty = 40; // Easy difficulty
                    }
                    else if (mediumButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        difficulty = 20; // Medium difficulty
                    }
                    else if (hardButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        difficulty = 14; // Hard difficulty
                    }
                    else {
                        continue;
                    }
                    isGameRunning = true;
                    sudokuSolver.generateRandomNumbers(sudokuBoard, difficulty);
                    return;
                }
            }
        }
    }
    else if (loadButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isMenuOpen = false;
        isGameRunning = true;
        fileHandler.loadBoardFromFile("save.csv");
    }
    else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        window.close();
    }
}

void SudokuGame::handleGameEvent(const sf::Event& event) {
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    int cellX = mouseX / cellSize;
    int cellY = mouseY / cellSize;
    sudokuBoard.setSelectedCell(cellY, cellX);
}

void SudokuGame::handleGameOverEvent(const sf::Event& event) {
    if (gameOverPlayAgainButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isGameOver = false;
        sudokuSolver.generateNewBoard(sudokuBoard, difficulty);
        isGameRunning = true;
    }
    else if (returnToGameButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isGameOver = false;
        isGameRunning = true;
    }
    else if (gameOverCheckButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        if (sudokuBoard.isBoardFilled()) {
            bool isSolutionCorrect = sudokuCheck.checkSolutionAsync();
            sf::Text message(isSolutionCorrect ? "Congratulations! You solved the Sudoku correctly!" : "Sorry, your solution is incorrect. Try again!", font, 30);
            message.setPosition(100, 100);
            message.setFillColor(sf::Color::White);
            showMessage(message);
        }
        else {
            sf::Text message("Sorry, the Sudoku is not complete.", font, 30);
            message.setPosition(100, 100);
            message.setFillColor(sf::Color::White);
            showMessage(message);
        }
    }
    else if (gameOverSaveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        fileHandler.saveBoardToFile("save.csv");
        sf::Text message("Board successfully saved!", font, 30);
        message.setPosition(100, 100);
        message.setFillColor(sf::Color::White);
        showMessage(message);
    }
    else if (gameOverExitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        window.close();
    }
}

void SudokuGame::drawMenu() {
    window.draw(playButton);
    window.draw(loadButton);
    window.draw(exitButton);
}

void SudokuGame::drawGame() {
    sudokuBoard.draw(window);
}

void SudokuGame::drawGameOver() {
    window.draw(gameOverPlayAgainButton);
    window.draw(returnToGameButton);
    window.draw(gameOverCheckButton);
    window.draw(gameOverSaveButton);
    window.draw(gameOverExitButton);
}

void SudokuGame::showMessage(const sf::Text& message) {
    window.clear();
    window.draw(message);
    window.display();
    bool showMessage = true;
    sf::Event event;
    while (showMessage) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                showMessage = false;
                isGameRunning = true;
                break;
            }
        }
    }
}
