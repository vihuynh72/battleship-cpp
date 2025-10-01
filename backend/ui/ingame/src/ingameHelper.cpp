#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"
#include "../../pregame/include/pregameHelper.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printBoard(Board& board) {
    cout << endl;
    cout << board.getPlayerName() << "'s Board: " << endl;
    cout << "   ";
    for (int j = 0; j < board.getColumns(); j++) {
        cout << "  " << static_cast<char>('A' + j) << " ";
    }
    cout << endl;

    for (int i = 0; i < board.getRows(); i++) {
        if (i < 9) {
            cout << i + 1 << "   ";
        } else {
            cout << i + 1 << "  ";
        }

        for (int j = 0; j < board.getColumns(); j++) {
            cout << board.getBoard()[i][j] << " ";
        }
        cout << endl;
    }
}

void printShipList(Board& board) {
    cout << board.getPlayerName() << "'s Ships: " << endl;
    for (Ship& ship : board.getShipList()) {
        cout << "------------------------" << endl;
        printShipInfo(ship);
        cout << "------------------------" << endl;
    }
}

void printShipInfo(Ship& ship) {
    cout << "Ship Name: " << ship.getName() << endl;
    cout << "Health: " << ship.getLength() - ship.getHitCount() << endl;
    cout << "Status: " << (ship.checkIsSunk() ? "Sunk" : "Not Sunk") << endl;
}

bool validateCoord(string coord, Board& board) {

    if (coord.length() < 2 || 
        coord.length() > 3 ||
        !isalpha(coord[0]) || 
        !isdigit(coord[1]) || 
        (coord.length() == 3 && !isdigit(coord[2]))) {
        cout << "Invalid format. Please use the format LetterNumber (e.g., A5).\n" << endl;
        return false;
    }
    
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;
    
    if (checkOutOfBounds(board, row, col) || !checkEmptyCell(board.getBoard()[row][col])) {
        cout << "Invalid coordinates. Please try again.\n" << endl;
        return false;
    }
    return true;
}

vector<int> coordToInt(string coord) {
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;  // Convert to 0-indexed (subtract 1, not add 1)
    return {row, col};
}