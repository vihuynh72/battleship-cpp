#include "board.h"
#include <iostream>

using namespace std;

Board::Board() {
    playerName = "Unnamed Player";
    Rows = 10;
    Columns = 10;
    board = vector<vector<string>>(Rows, vector<string>(Columns, "[ ]")); // "[ ]" represents empty seea
}

void Board::setBoardProperties(string name, int rows, int cols) {
    playerName = name;
    Rows = rows;
    Columns = cols;
    board = vector<vector<string>>(Rows, vector<string>(Columns, "[ ]")); // Initialize board with empty sea
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
