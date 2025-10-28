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
    cout << "\n========================================" << endl;
    cout << "|      ULTIMATE BATTLESHIP COMMAND     |" << endl;
    cout << "========================================" << endl;
    cout << "| Chart a course for naval supremacy!  |" << endl;
    cout << "| Choose how you'd like to engage the  |" << endl;
    cout << "| enemy fleet and press Enter to begin.|" << endl;
    cout << "----------------------------------------" << endl;
    cout << " 1) Skirmish vs Computer" << endl;
    cout << " 2) Duel vs Human (coming soon)" << endl;
    cout << " 3) Secure Harbor (Exit)" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter a command number and press Enter: ";

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
            cout << "Invalid command received. Please enter 1, 2, or 3." << endl;
            displayHome();
    }
}


void displaySetup() {
    cout << "\n========================================" << endl;
    cout << "|           CAMPAIGN SETUP             |" << endl;
    cout << "========================================" << endl;
    cout << "Follow the steps below to prepare both fleets before battle." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Step 1: Define the battlefield dimensions." << endl;
    cout << "         Choose the number of rows and columns for your ocean grid.\n" << endl;

    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];

    cout << "----------------------------------------" << endl;
    cout << "Step 2: Identify your captains." << endl;
    cout << "         Provide call signs for both commanders.\n" << endl;
    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "----------------------------------------" << endl;
    cout << "Step 3: Deploy the fleet." << endl;
    cout << "         Each commander receives five ships of varying sizes." << endl;
    cout << "         Arrange them carefully to outwit your opponent." << endl;
    cout << "\nDeploying ships for Captain " << player1 << "...\n" << endl;

    placeShip(player1Board, rows, cols);

    cout << "Automated deployment engaged for Captain " << player2 << ".\n" << endl;
    randomizeShipOnBoard(player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void personVsComputer() {
    cout << "\n========================================" << endl;
    cout << "|        BATTLE MODE SELECTION         |" << endl;
    cout << "========================================" << endl;
    cout << "Select how you would like to engage the computer-controlled fleet." << endl;
    cout << "----------------------------------------" << endl;
    cout << " 1) Quick Game   - Instant action with standard rules." << endl;
    cout << " 2) Custom Setup - Tailor the battlefield before the clash." << endl;
    cout << " 3) Main Menu    - Return to command headquarters." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter a command number and press Enter: ";
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
            cout << "Invalid command received. Please enter 1, 2, or 3." << endl;
            personVsComputer();
    }
}

void pvcQuickGame() {
    cout << "\n========================================" << endl;
    cout << "|             QUICK ENGAGEMENT          |" << endl;
    cout << "========================================" << endl;
    cout << "Standard 10x10 grid. Five classic vessels per fleet." << endl;
    cout << "You'll face the computer in a tactical duel to sink every ship." << endl;
    cout << "----------------------------------------\n" << endl;

    string player1 = "Player";
    string player2 = "Computer";

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);
    
    cout << "----------------------------------------" << endl;
    cout << "Would you like to manually position your ships?" << endl;
    cout << "Enter 'y' to place each vessel, or 'n' for an automated deployment." << endl;
    cout << "Selection: ";
    string choice;
    cin >> choice;

    if (choice == "y") {
        vector<Ship> defaultShips = getDefaultShips();
        // get coordinate and place each ship
        for (Ship& ship : defaultShips) {
            cout << "\nPreparing to deploy the " << ship.getName()
                 << " (Length: " << ship.getLength() << ")." << endl;
            cout << "Choose an orientation and starting coordinate to launch the vessel." << endl;

            string direction = directionSetup();
            ship.setShipProperties(ship.getName(), direction, ship.getLength());

            vector<int> shipCoord = coordinateSetup(player1Board, ship);
            int ship_y_coord = shipCoord[0];
            int ship_x_coord = shipCoord[1];

            addShipToBoard(player1Board, ship, ship_y_coord, ship_x_coord, ship.getDirection());
            printBoard(player1Board);
            cout << "Deployment confirmed!" << endl;
        }

    } else {
        randomizeShipOnBoard(player1Board);
    }
    randomizeShipOnBoard(player2Board);

    printBoardSideBySide(player1Board, player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void promptBeginGame(Board& player1Board, Board& player2Board, bool isPvC) {
    if (isPvC) {
        startPvcGame(player1Board, player2Board);
    } else {
        startPvPGame(player1Board, player2Board);
    }
}