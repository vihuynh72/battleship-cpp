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
        cout << "Lock in bombardment coordinates (e.g., A5): ";
        string input;
        cin >> input;

        if (input == "show") {
            playerBoard.setHideShips(false);
            cout << "Cheat mode engaged: enemy silhouettes illuminated!" << endl;
            printBoardSideBySide(getPlayer1Board(), playerBoard);
            continue;
        }

        if (input == "hide") {
            playerBoard.setHideShips(true);
            cout << "Fog of war restored. Enemy fleet cloaked once more." << endl;
            printBoardSideBySide(getPlayer1Board(), playerBoard);
            continue;
        }

        if (input == "kill") {
            cout << "🚨 DEBUG MODE: Orbital strike authorized! Annihilating enemy fleet..." << endl;
            // Sink all enemy ships instantly
            for (Ship& ship : playerBoard.getShipList()) {
                while (!ship.checkIsSunk()) {
                    ship.incrementHitCount();
                }
            }
            cout << "⚡ All enemy vessels destroyed! Victory is yours!" << endl;
            // Mark all ship cells as hit on the board
            for (int i = 0; i < playerBoard.getRows(); i++) {
                for (int j = 0; j < playerBoard.getColumns(); j++) {
                    string cell = playerBoard.getBoard()[i][j];
                    if (cell != "[ ]" && cell != "[X]" && cell != "[O]") {
                        playerBoard.getBoard()[i][j] = "[X]";
                    }
                }
            }
            printBoardSideBySide(getPlayer1Board(), playerBoard);
            return; // End turn immediately
        }

        vector<int> coord = coordToInt(input);
        row = coord[0];
        col = coord[1];

        // Validate input
        if (row < 0 || row >= playerBoard.getRows() || col < 0 || col >= playerBoard.getColumns()) {
            cout << "Those coordinates fall outside our radar range. Try again." << endl;
            continue;
        }

        // Check if already attacked
        string cellContent = playerBoard.getBoard()[row][col];
        if (cellContent == "[X]" || cellContent == "[O]") {
            cout << "We've already shelled those waters. Choose a fresh target." << endl;
            continue;
        }

        // Attack and break out of loop
        attackShipOnBoard(playerBoard, row, col);
        cout << "Impact confirmed at sector " << static_cast<char>('A' + col) << (row + 1) << "!" << endl;
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
    cout << "Enemy AI unleashes fire upon sector " << static_cast<char>('A' + col) << (row + 1) << "!" << endl;
}


