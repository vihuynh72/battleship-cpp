#include "../include/pregame.h"
#include "../include/setup.h"
#include "../../ingame/include/startgame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void displayHome() {
    cout << "========================================" << endl;
    cout << "        ⚓  BATTLESHIP COMMAND  ⚓        " << endl;
    cout << "========================================" << endl;
    cout << "   A calm sea lies ahead... for now.    " << endl;
    cout << " Chart your course and ready the fleet! " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Quick Start  - Launch into action" << endl;
    cout << "2. Setup Game   - Customize your war" << endl;
    cout << "3. Exit         - Return to port" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Please enter your command (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1: // Implement default setting here
            // startGame(player1Board, player2Board);
            break;
        case 2:
            displaySetup();
            break;
        case 3:
            cout << "Standing down. May your next voyage be legendary!" << endl;
            exit(0);
            break;
        default:
            cout << "That command drifted off course. Try again, captain!" << endl;
            displayHome();
    }
}


void displaySetup() {
    cout << "========================================" << endl;
    cout << "            MISSION CONTROL             " << endl;
    cout << "========================================" << endl;
    cout << "          Configure Your Fleet          " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Set up board dimensions" << endl;
    cout << "   Draft a battlefield large enough for glory." << endl;
    cout << "Number of Rows (min 5, max 26): ";

    int rows = dimensionSetup();

    cout << "Number of Columns (min 5, max 26): ";

    int cols = dimensionSetup();

    cout << "----------------------------------------" << endl;
    cout << "2. Set up player names" << endl;
    cout << "   Give each admiral a call sign worthy of legend." << endl;
    cout << "Enter Player 1 Name: ";

    string player1 = playerSetup();

    cout << "Enter Player 2 Name: ";

    string player2 = playerSetup();

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);

    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "----------------------------------------" << endl;
    cout << "3. Set up ships for each player" << endl;
    cout << "   Deploy five vessels with strategic precision." << endl;
    cout << "\nHarbor master is ready for " << player1 << "!" << endl;

    placeShip(player1Board, rows, cols);
    placeShip(player2Board, rows, cols);

    cout << "========================================" << endl;

    cout << "Setup complete! Hoist the flags and prepare for battle.\n";
    cout << "Shall we set sail now? (yes/no)" << endl;

    string choice;
    cin >> choice;
    if (choice == "yes") {
        startGame(player1Board, player2Board);
    } else {
        displayHome();
    }
  }