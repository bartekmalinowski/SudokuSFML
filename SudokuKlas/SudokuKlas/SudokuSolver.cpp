#include "SudokuSolver.h"
#include <random>

void SudokuSolver::generateSudokuSolution(SudokuBoard& sudokuBoard) {
    auto& board = sudokuBoard.getBoard(); // Pobieramy referencjê do oryginalnej tablicy
    std::vector<std::vector<int>> tempBoard(boardSize, std::vector<int>(boardSize, 0));
    std::vector<std::vector<bool>> usedInRow(boardSize, std::vector<bool>(boardSize + 1, false));
    std::vector<std::vector<bool>> usedInCol(boardSize, std::vector<bool>(boardSize + 1, false));
    std::vector<std::vector<bool>> usedInBox(boardSize, std::vector<bool>(boardSize + 1, false));

    generateSudokuSolutionUtil(0, 0, tempBoard, usedInRow, usedInCol, usedInBox, sudokuBoard);

    // Kopiujemy wygenerowan¹ tablicê do instancji SudokuBoard
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j].value = tempBoard[i][j];
            board[i][j].initial = true;
        }
    }
}

bool SudokuSolver::generateSudokuSolutionUtil(int row, int col, std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& usedInRow, std::vector<std::vector<bool>>& usedInCol, std::vector<std::vector<bool>>& usedInBox, SudokuBoard& sudokuBoard) {
    if (row == boardSize - 1 && col == boardSize) {
        return true; // Board is full, return true
    }

    if (col == boardSize) {
        row++;
        col = 0;
    }

    if (board[row][col] != 0) {
        return generateSudokuSolutionUtil(row, col + 1, board, usedInRow, usedInCol, usedInBox, sudokuBoard);
    }

    //auto& boardRef = sudokuBoard.getBoard();

    std::vector<int> numbers;
    for (int i = 1; i <= boardSize; ++i) {
        numbers.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    for (int num : numbers) {
        if (!usedInRow[row][num] && !usedInCol[col][num] && !usedInBox[row / 3 * 3 + col / 3][num]) {
            board[row][col] = num;
            usedInRow[row][num] = true;
            usedInCol[col][num] = true;
            usedInBox[row / 3 * 3 + col / 3][num] = true;

            if (generateSudokuSolutionUtil(row, col + 1, board, usedInRow, usedInCol, usedInBox, sudokuBoard)) {
                return true;
            }

            board[row][col] = 0;
            usedInRow[row][num] = false;
            usedInCol[col][num] = false;
            usedInBox[static_cast<std::vector<std::vector<bool, std::allocator<bool>>, std::allocator<std::vector<bool, std::allocator<bool>>>>::size_type>(row / 3) * 3 + col / 3][num] = false;
        }
    }

    return false; // No valid number found, backtrack
}
void SudokuSolver::generateRandomNumbers(SudokuBoard& sudokuBoard, int difficulty) {
    auto& board = sudokuBoard.getBoard();

    // Clear the board
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j].value = 0;
            board[i][j].editable = true; // reset editability
        }
    }

    // Generate a correct Sudoku board
    generateSudokuSolution(sudokuBoard);

    // Remove random numbers, leaving the desired number of digits
    int numCount = 0;
    while (numCount < boardSize * boardSize - difficulty) {
        int row = rand() % boardSize;
        int col = rand() % boardSize;
        if (board[row][col].value != 0) {
            board[row][col].value = 0;
            board[row][col].editable = true; // make removed cells editable
            ++numCount;
        }
    }

    // Mark initially generated cells as non-editable
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j].value != 0) {
                board[i][j].editable = false; // initially generated cells are non-editable
            }
        }
    }
}

void SudokuSolver::generateNewBoard(SudokuBoard& sudokuBoard, int difficulty) {
    // Clear the board
    auto& board = sudokuBoard.getBoard();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j].value = 0;
            board[i][j].initial = false;
        }
    }

    generateRandomNumbers(sudokuBoard, difficulty);
}

SudokuSolver::SudokuSolver(SudokuBoard& sudokuBoard, int difficulty) {}
