#include "../include/pregame.h"
#include "../include/pregameHelper.h"
#include "../../ingame/include/startgame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/bot/include/bot.h"
#include "../../../gameplay/mechanics/ship/include/ship.h"
#include "../../ingame/include/ingameHelper.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;


void displayHome() {
    cout << "========================================" << endl;
    cout << "   Welcome to the Ultimate Battleship  " << endl;
    cout << "========================================" << endl;
    cout << "1. vs Computer" << endl;
    cout << "2. vs Human" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            personVsComputer();
            break;
        case 2:
            // TODO: Implement human vs human mode
            cout << "Human vs Human mode is under development. Please try again later." << endl;
            displayHome();
            break;
        case 3:
            cout << "Exiting game. Thank you for playing!" << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayHome();
    }
}


void displaySetup() {
    cout << "========================================" << endl;
    cout << "               Game Setup               " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Set up board dimensions\n" << endl;
    
    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];
    
    cout << "----------------------------------------" << endl;
    cout << "2. Set up player names\n" << endl;
    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "----------------------------------------" << endl;
    cout << "3. Set up ships for each player" << endl;
    cout << "\nEach person will have 5 ships of varying sizes." << endl;
    cout << "Placing ships for " << player1 << "\n" << endl;
    
    placeShip(player1Board, rows, cols);

    cout << "Placing ships for " << player2 << "\n" << endl;
    randomizeShipOnBoard(player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void personVsComputer() {
    cout << "========================================" << endl;
    cout << "            Person vs Computer          " << endl;
    cout << "========================================" << endl;
    cout << "1. Quick Game" << endl;
    cout << "2. Setup Game" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "Please select an option (1-3): ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            pvcQuickGame();
            break;
        case 2:
            displaySetup();
            break;
        case 3:
            displayHome();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            personVsComputer();
    }
}

void pvcQuickGame() {
    cout << "========================================" << endl;
    cout << "               Quick Game               \n" << endl;

    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);
    
    cout << "----------------------------------------" << endl;
    cout << "Do you want to place your ships manually? (y/n): ";
    string choice;
    cin >> choice;

    if (choice == "y") {
        vector<Ship> defaultShips = getDefaultShips();
        // get coordinate and place each ship
        for (Ship& ship : defaultShips) {
            cout << "Placing ship: " << ship.getName() << " (Length: " << ship.getLength() << ")\n" << endl;

            string direction = directionSetup();
            ship.setShipProperties(ship.getName(), direction, ship.getLength());

            vector<int> shipCoord = coordinateSetup(player1Board, ship);
            int ship_y_coord = shipCoord[0];
            int ship_x_coord = shipCoord[1];

            addShipToBoard(player1Board, ship, ship_y_coord, ship_x_coord, ship.getDirection());
            printBoard(player1Board);
            cout << "Ship placed successfully!" << endl;
        }
        
    } else {
        randomizeShipOnBoard(player1Board);
    }
    randomizeShipOnBoard(player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void promptBeginGame(Board& player1Board, Board& player2Board, bool isPvC) {
    cout << "========================================" << endl;
    cout << "Setup complete! Do you want to start the game? (y/n)" << endl;
    
    string choice;
    cin >> choice;
    if (choice == "y") {
        if (isPvC) {
            startPvcGame(player1Board, player2Board);
        } else {
            startPvPGame(player1Board, player2Board);
        }
    } else {
        displayHome();
    }
}