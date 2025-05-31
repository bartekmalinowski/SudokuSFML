# SudokuSFML

SudokuSFML is a modern implementation of the classic Sudoku puzzle game built using SFML (Simple and Fast Multimedia Library). The game features a graphical user interface, puzzle generation, solving capabilities, and save/load functionality.

## Introduction

This project aims to provide an engaging and user-friendly Sudoku experience with modern graphics and intuitive controls. Built with C++ and SFML, it offers a robust implementation of the popular number puzzle game with additional features like puzzle generation and solving assistance.

## Features

- **Graphical User Interface**: Modern and intuitive interface built with SFML
- **Puzzle Generation**: Automatic generation of valid Sudoku puzzles with varying difficulty levels
- **Game Mechanics**:
  - Input validation
  - Real-time error checking
  - Save/Load game progress
- **Additional Features**:
  - Puzzle solving assistance
  - File handling for game state persistence
  - Customizable difficulty levels

## Prerequisites

- Windows operating system
- Visual Studio (recommended for development)
- SFML 2.x library
- C++ compiler with C++11 or later support

## Installation

1. Clone this repository to your local machine
2. Ensure you have SFML 2.x installed on your system
3. Open the solution file `SudokuKlas.sln` in Visual Studio
4. Build the project using Visual Studio

## Running the Game

1. After building the project, navigate to the `x64/Debug` or `x64/Release` directory
2. Run the executable file `SudokuKlas.exe`
3. The game window will open, and you can start playing immediately

## Project Structure

The project is organized into several key components:

- `SudokuBoard`: Core game board implementation
- `SudokuGenerator`: Handles puzzle generation
- `SudokuSolver`: Implements solving algorithms
- `Graphics`: Manages the SFML-based graphical interface
- `InputHandler`: Processes user input
- `FileHandler`: Manages save/load functionality
- `Cell`: Represents individual Sudoku cells

## Contributing

Contributions are welcome! To contribute:

1. Fork this repository
2. Create a new branch for your feature
3. Make your changes
4. Submit a pull request with a detailed description of your modifications

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Author

Created by Bartosz Malinowski from Silesian University of Technology as a programming project.
