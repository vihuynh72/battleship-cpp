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
    cout << endl;
    cout << "========================================" << endl;
    cout << "        NAVAL STRIKE COMMAND HUB        " << endl;
    cout << "========================================" << endl;
    cout << "Chart your course:" << endl;
    cout << "  1. Engage the Computer Fleet" << endl;
    cout << "  2. Challenge a Human Admiral" << endl;
    cout << "  3. Stand Down and Exit" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter a command (1-3) to continue: ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            personVsComputer();
            break;
        case 2:
            cout << "Human vs Human mode is under development. Please try again later." << endl;
            displayHome();
            break;
        case 3:
            cout << "Exiting game. Fair winds and following seas, Admiral." << endl;
            exit(0);
            break;
        default:
            cout << "Unrecognized command. Please select a valid option." << endl;
            displayHome();
    }
}


void displaySetup() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "              CAMPAIGN SETUP            " << endl;
    cout << "========================================" << endl;
    cout << "Step 1: Configure the battlefield dimensions." << endl;
    cout << "   - Choose the height (rows) and width (columns) for the grid." << endl;
    cout << "   - Larger seas provide more room for tactics." << endl;
    cout << "----------------------------------------" << endl;

    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];

    cout << "----------------------------------------" << endl;
    cout << "Step 2: Commission your captains." << endl;
    cout << "   - Enter the callsigns for each fleet commander." << endl;
    cout << "   - These names will be displayed on tactical readouts." << endl;
    cout << endl;
    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "----------------------------------------" << endl;
    cout << "Step 3: Deploy your fleet." << endl;
    cout << "   - Each admiral commands 5 ships of varied lengths." << endl;
    cout << "   - Position each vessel carefully to maximize coverage." << endl;
    cout << endl;
    cout << "Placing ships for " << player1 << "..." << endl;

    placeShip(player1Board, rows, cols);

    cout << "Placing ships for " << player2 << "..." << endl;
    randomizeShipOnBoard(player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void personVsComputer() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "           COMPUTER ENGAGEMENT          " << endl;
    cout << "========================================" << endl;
    cout << "Choose your briefing:" << endl;
    cout << "  1. Quick Battle (standard 10x10 grid)" << endl;
    cout << "  2. Custom Scenario (full setup)" << endl;
    cout << "  3. Return to Command Hub" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Select an option (1-3): ";
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
            cout << "Unrecognized command. Please select a valid option." << endl;
            personVsComputer();
    }
}

void pvcQuickGame() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "               QUICK BATTLE             " << endl;
    cout << "========================================" << endl;
    cout << "Standard engagement parameters loaded." << endl;
    cout << "- Grid Size: 10 x 10" << endl;
    cout << "- Fleet: 5 classic vessels" << endl;
    cout << "----------------------------------------" << endl;

    string player1 = "Player";
    string player2 = "Computer";

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);

    cout << "Would you like to deploy your ships manually? (y/n): ";
    string choice;
    cin >> choice;

    if (choice == "y") {
        vector<Ship> defaultShips = getDefaultShips();
        for (Ship& ship : defaultShips) {
            cout << endl;
            cout << "Deploying: " << ship.getName() << " (Length " << ship.getLength() << ")" << endl;
            cout << "Choose orientation (horizontal/vertical) and starting coordinate." << endl;

            string direction = directionSetup();
            ship.setShipProperties(ship.getName(), direction, ship.getLength());

            vector<int> shipCoord = coordinateSetup(player1Board, ship);
            int ship_y_coord = shipCoord[0];
            int ship_x_coord = shipCoord[1];

            addShipToBoard(player1Board, ship, ship_y_coord, ship_x_coord, ship.getDirection());
            printBoard(player1Board);
            cout << "Ship successfully stationed." << endl;
        }

    } else {
        randomizeShipOnBoard(player1Board);
        cout << "Automated deployment complete." << endl;
    }
    randomizeShipOnBoard(player2Board);
    cout << "Enemy fleet has assumed formation." << endl;

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