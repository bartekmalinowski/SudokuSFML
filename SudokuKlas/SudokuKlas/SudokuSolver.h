#pragma once
#include "SudokuBoard.h"

class SudokuSolver {
public:
    static void generateSudokuSolution(SudokuBoard& sudokuBoard);
    static void generateRandomNumbers(SudokuBoard& sudokuBoard, int difficulty);
    static void generateNewBoard(SudokuBoard& sudokuBoard, int difficulty);
    SudokuSolver(SudokuBoard& sudokuBoard, int difficulty);

private:
    static bool generateSudokuSolutionUtil(int row, int col, std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& usedInRow, std::vector<std::vector<bool>>& usedInCol, std::vector<std::vector<bool>>& usedInBox, SudokuBoard& sudokuBoard);

};