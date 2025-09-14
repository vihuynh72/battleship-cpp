#ifndef BOARD_H
#define BOARD_H

#include "../ship/ship.h"

#include <string>
#include <vector>

class Board {
    public:
        Board(); // Constructor to initialize the board
        std::vector<std::vector<std::string>> getBoard(); // Method to get the board
        void setBoardProperties(std::string, int, int); // Method to set board properties
        void displayBoard(); // Method to display the board
         
        void incrementTotalShips(); // Method to increment total ship count
        int getTotalShips(); // Method to get total ship count

        void addShip(Ship&); // Method to add ship to ship list
        std::vector<Ship> getShipList(); // Method to get list of ships

    private:
        // Player name
        std::string playerName;

        // Board dimensions
        int Rows;
        int Columns;

        // Ship Count
        int totalShips;
        std::vector<Ship> shipList; // Vector to hold ships on the board

        // 2D vectors to represent the board for dynamic sizing
        std::vector<std::vector<std::string>> board;
};

#endif // BOARD_H