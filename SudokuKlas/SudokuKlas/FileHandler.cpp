#include "FileHandler.h"
#include "SudokuBoard.h"


void FileHandler::saveBoardToFile(const std::string& filename) {
    auto& board = sudokuBoard.getBoard();
    auto difficulty = sudokuBoard.getDifficulty();
    std::regex filenameRegex("[a-zA-Z0-9_]+\\.csv");
    if (!std::regex_match(filename, filenameRegex)) {
        std::cerr << "Error: invalid filename format!" << std::endl;
        return;
    }
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                file << board[i][j].value << ",";
            }
            file << "\n";
        }
        file << "difficulty," << difficulty << "\n";
        file.close();
    }
}

void FileHandler::loadBoardFromFile(const std::string& filename) {
    auto& board = sudokuBoard.getBoard();
    auto difficulty = sudokuBoard.getDifficulty();
    std::filesystem::path filePath(filename);
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "Error: file " << filename << " does not exist!" << std::endl;
        return;
    }
    std::regex filenameRegex("[a-zA-Z0-9_]+\\.csv");
    if (!std::regex_match(filename, filenameRegex)) {
        std::cerr << "Error: invalid filename format!" << std::endl;
        return;
    }
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: unable to open file " << filename << std::endl;
        return;
    }

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int value;
            file >> value;
            board[i][j].value = value;
            if (value != 0) {
                board[i][j].initial = true;
            }
            else {
                board[i][j].initial = false;
            }
            file.ignore(1, ','); // ignore the comma separator
        }
        file.ignore(1, '\n'); // ignore the newline character
    }

    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string token;
    std::getline(iss, token, ',');
    if (token == "difficulty") {
        std::getline(iss, token, ',');
        difficulty = std::stoi(token);
    }

    file.close();
}