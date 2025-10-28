#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printBoard(Board& board) {
    cout << "\n" << endl;
    cout << "~~~~~~~~~~~~~~~ SEA CHART ~~~~~~~~~~~~~~~" << endl;
    cout << "Command: " << board.getPlayerName() << endl;
    cout << "Legend: ~ waves | O ship | X hit | * miss" << endl;
    cout << "------------------------------------------" << endl;
    cout << board.getPlayerName() << "'s Board:" << endl;
    // i want to print it like a chessboard with numbers on top and side
    cout << "  ";
    for (int j = 0; j < board.getColumns(); j++) {
        cout << "  " << j << " ";
    }
    cout << endl;

    for (int i = 0; i < board.getRows(); i++) {
        cout << " "  << i << " ";
        for (int j = 0; j < board.getColumns(); j++) {
            cout << board.getBoard()[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "Plot your strikes wisely, Admiral " << board.getPlayerName() << "!" << endl;
}

void printShipList(Board& board) {
    cout << "\nFleet Roster for Admiral " << board.getPlayerName() << ":" << endl;
    cout << "----------------------------------------" << endl;
    for (Ship& ship : board.getShipList()) {
        cout << "------------------------" << endl;
        printShipInfo(ship);
        cout << "------------------------" << endl;
    }
    cout << "Review complete. Maintain readiness!" << endl;
}

void printShipInfo(Ship& ship) {
    cout << "Ship Name : " << ship.getName() << endl;
    cout << "Hull Integrity : " << ship.getLength() - ship.getHitCount() << " / " << ship.getLength() << endl;
    cout << "Status : " << (ship.checkIsSunk() ? "SUNK - WRECKAGE DRIFTING" : "ACTIVE - READY TO FIRE") << endl;
}

void printCommentary() {

}

