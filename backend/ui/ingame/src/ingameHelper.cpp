#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printBoard(Board& board) {
    cout << "\n" << endl;
    cout << board.getPlayerName() << "'s Board: " << endl;
    cout << "  ";
    for (int j = 0; j < board.getColumns(); j++) {
        cout << "  " << static_cast<char>('A' + j) << " ";
    }
    cout << endl;

    for (int i = 0; i < board.getRows(); i++) {
        cout << " "  << i + 1 << " ";
        for (int j = 0; j < board.getColumns(); j++) {
            cout << board.getBoard()[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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

void printCommentary() {
    
}

