#include "board.h"
#include <iostream>
#include <vector>

using namespace std;

// Constructor to initialize the board
Board::Board() {
    playerName = "Unnamed Player";
    Rows = 10;
    Columns = 10;

    totalShips = 0;

    // Initialize a 10x10 board with empty sea
    board = vector<vector<string>>(10, vector<string>(10, "[ ]")); // "[ ]" represents empty sea
}

// Method to get the board
vector<vector<string>> Board::getBoard() {
    return board;
}

// Method to set board properties
void Board::setBoardProperties(string name, int rows, int cols) {
    playerName = name;
    Rows = rows;
    Columns = cols;
    board = vector<vector<string>>(Rows, vector<string>(Columns, "[ ]")); // Initialize board with empty sea
}

void Board::updateBoard(vector<vector<string>> newBoard) {
    board = newBoard;
}

// Method to increment total ship count
void Board::incrementTotalShips() {
    totalShips++;
}

// Method to get total ship count
int Board::getTotalShips() {
    return totalShips;
}

void Board::addShip(Ship &ship) {
    shipList.push_back(ship);
    incrementTotalShips();
}

vector<Ship> Board::getShipList() {
    return shipList;
}

// TODO: Move to UI
void Board::displayBoard() {

    //display 2D vector
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
