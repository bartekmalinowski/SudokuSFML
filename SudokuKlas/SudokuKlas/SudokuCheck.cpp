#include "SudokuCheck.h"
#include <future>

bool SudokuCheck::checkSolution() const {
    auto& board = sudokuBoard.getBoard();
    // Check each row
    for (int i = 0; i < boardSize; ++i) {
        bool used[boardSize + 1] = { false }; // Array to track used numbers in the row
        for (int j = 0; j < boardSize; ++j) {
            int num = board[i][j].value;
            if (num != 0 && used[num]) {
                return false; // Repeating number in the row
            }
            used[num] = true;
        }
    }

    // Check each column
    for (int j = 0; j < boardSize; ++j) {
        bool used[boardSize + 1] = { false }; // Array to track used numbers in the column
        for (int i = 0; i < boardSize; ++i) {
            int num = board[i][j].value;
            if (num != 0 && used[num]) {
                return false; // Repeating number in the column
            }
            used[num] = true;
        }
    }

    // Check each 3x3 box
    for (int i = 0; i < boardSize; i += 3) {
        for (int j = 0; j < boardSize; j += 3) {
            bool used[boardSize + 1] = { false }; // Array to track used numbers in the 3x3 box
            for (int k = i; k < i + 3; ++k) {
                for (int l = j; l < j + 3; ++l) {
                    int num = board[k][l].value;
                    if (num != 0 && used[num]) {
                        return false; // Repeating number in the 3x3 box
                    }
                    used[num] = true;
                }
            }
        }
    }

    return true; // Solution is correct
}

bool SudokuCheck::checkSolutionAsync() const {
    return std::async(std::launch::async, [&]() {
        return checkSolution();
        }).get();
}