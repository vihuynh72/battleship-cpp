#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

class Board {
    public:
        Board(); // Constructor to initialize the board
        void setBoardProperties(std::string, int, int); // Method to set board properties
        void displayBoard(); // Method to display the board
        
    private:
        // Player name
        std::string playerName;

        // Board dimensions
        int Rows;
        int Columns;

        // 2D vectors to represent the board for dynamic sizing
        std::vector<std::vector<std::string>> board;
};

#endif // BOARD_H