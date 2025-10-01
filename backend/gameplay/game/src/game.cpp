#include "../include/game.h"
#include "../include/gameMode.h"
#include "../../board/include/board.h"
#include "../../mechanics/bot/include/bot.h"
#include "../../mechanics/ship/include/ship.h"
#include "../../../../ui/ingame/include/ingameHelper.h"

#include <iostream>
#include <string>

using namespace std;

// Create a default GameMode instance
GameMode defaultGameMode;

Game::Game(Board& p1Board, Board& p2Board) : player1Board(p1Board), player2Board(p2Board), isPvP(false), rules(defaultGameMode) {
    // Constructor with boards to start a PVC game
}

Game::Game(Board& p1Board, Board& p2Board, bool pvp) : player1Board(p1Board), player2Board(p2Board), isPvP(pvp), rules(defaultGameMode) {
    // Constructor with boards and PvP flag
}

void pvcGame::playerTurn() {
    Board& playerBoard = getPlayer2Board(); // Player will get player 2's board and interact with it
    int row, col;

    while (true) {
        cout << "Enter coordinates to attack (e.g., A5): ";
        string input;
        cin >> input;
        
        vector<int> coord = coordToInt(input);
        row = coord[1];
        col = coord[0];

        // Validate input
        if (row < 0 || row >= playerBoard.getRows() || col < 0 || col >= playerBoard.getColumns()) {
            cout << "Invalid coordinates. Please try again." << endl;
            continue;
        }

        // Check if already attacked
        string cellContent = playerBoard.getBoard()[row][col];
        if (cellContent == "[X]" || cellContent == "[O]") {
            cout << "Already attacked this position. Try again." << endl;
            continue;
        }

        // Attack and break out of loop
        attackShipOnBoard(playerBoard, row, col);
        cout << "You attacked position " << static_cast<char>('A' + col) << (row + 1) << endl;
        break;
    }
}

void pvcGame::computerTurn() {
    Board& playerBoard = getPlayer1Board(); // AI will get player 1's board and interact with it

    int row, col;
    row = nextInt(0, playerBoard.getRows() - 1);
    col = nextInt(0, playerBoard.getColumns() - 1);

    // Check if cell is not already attacked
    while (playerBoard.getBoard()[row][col] == "[X]" || playerBoard.getBoard()[row][col] == "[O]") {
        row = nextInt(0, playerBoard.getRows() - 1);
        col = nextInt(0, playerBoard.getColumns() - 1);
    }

    attackShipOnBoard(playerBoard, row, col);
    cout << "Computer attacked position " << static_cast<char>('A' + col) << (row + 1) << endl;
}

    
