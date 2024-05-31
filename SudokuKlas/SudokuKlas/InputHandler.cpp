#include "InputHandler.h"

void InputHandler::handleKeyPress(sf::Keyboard::Key key) {
    auto& board = sudokuBoard.getBoard();
    auto difficulty = sudokuBoard.getDifficulty();
    auto selectedCell = sudokuBoard.getSelectedCell();

    if (selectedCell.x != -1 && selectedCell.y != -1) {
        int row = selectedCell.x;
        int col = selectedCell.y;

        if (board[row][col].editable) {
            if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
                int value = key - sf::Keyboard::Num0;

                // Check if the entered value repeats in the same column
                for (int i = 0; i < boardSize; ++i) {
                    if (i != row && board[i][col].value == value) {
                        return; // Value already exists in this column
                    }
                }

                // Check if the entered value repeats in the same row
                for (int j = 0; j < boardSize; ++j) {
                    if (j != col && board[row][j].value == value) {
                        return; // Value already exists in this row
                    }
                }

                // Check if the entered value repeats in the same 3x3 box
                int startRow = (row / 3) * 3;
                int startCol = (col / 3) * 3;
                for (int i = startRow; i < startRow + 3; ++i) {
                    for (int j = startCol; j < startCol + 3; ++j) {
                        if (i != row && j != col && board[i][j].value == value) {
                            return; // Value already exists in the same 3x3 box
                        }
                    }
                }

                // Value satisfies Sudoku rules, it can be added to the board
                sudokuBoard.setCellValue(row, col, value);
            }
            else if (key == sf::Keyboard::Delete) {
                sudokuBoard.setCellValue(row, col, 0); // Clear the cell
            }
        }
    }
}