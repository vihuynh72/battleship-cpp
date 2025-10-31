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

// ANSI color codes
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";
const string RESET = "\033[0m";

void displayHome() {
    cout << "\n";
    cout << CYAN << BOLD << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║" << RESET << "                                        " << CYAN << "║" << RESET << endl;
    cout << CYAN << "║" << RESET << "      " << CYAN << "⚓" << RESET << " COMMAND BRIDGE TERMINAL " << CYAN << "⚓" << RESET << "     " << CYAN << "║" << RESET << endl;
    cout << CYAN << "║" << RESET << "                                        " << CYAN << "║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    cout << "\n";
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│  [1] ⚔  Engage the AI Armada           │" << endl;
    cout << "│  [2] ⚔  Challenge Another Captain      │" << endl;
    cout << "│  [3] ⚔  Stand Down                     │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
    cout << "\n>>> Choose your mission (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            personVsComputer();
            break;
        case 2:
            // TODO: Implement human vs human mode
            cout << "\n⚠  Two-player skirmishes are still being charted." << endl;
            cout << "   Check back after the next briefing.\n" << endl;
            displayHome();
            break;
        case 3:
            cout << "\n⚓ Powering down tactical console." << endl;
            cout << "   Fair winds and following seas!\n" << endl;
            exit(0);
            break;
        default:
            cout << "\n❌ That selection drifted off course. Try plotting it again.\n" << endl;
            displayHome();
    }
}


void displaySetup() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║        ⚓ STRATEGY BRIEFING ⚓         ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n┌─ MISSION PARAMETERS ─────────────────┐" << endl;
    cout << "│ Step 1: Configure battlefield grid   │" << endl;
    cout << "└──────────────────────────────────────┘\n" << endl;
    
    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];
    
    cout << "\n┌─ OFFICER REGISTRATION ───────────────┐" << endl;
    cout << "│ Step 2: Identify commanding officers │" << endl;
    cout << "└──────────────────────────────────────┘\n" << endl;
    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "\n┌─ FLEET DEPLOYMENT ───────────────────┐" << endl;
    cout << "│ Step 3: Position your naval armada   │" << endl;
    cout << "└───────────────────────────────────────┘" << endl;
    cout << "\n⚓ Each admiral commands 5 vessels of varying tonnage." << endl;
    cout << "⚓ Position them wisely across your tactical grid.\n" << endl;
    
    cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << ">>> Plotting courses for " << player1 << " <<<" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << endl;
    
    placeShip(player1Board, rows, cols);

    cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << ">>> Plotting courses for " << player2 << " <<<" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << endl;
    randomizeShipOnBoard(player2Board);

    player2Board.setHideShips(true);

    promptBeginGame(player1Board, player2Board, true);
}

void personVsComputer() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║       ⚓ PERSON VS COMPUTER ⚓         ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n┌────────────────────────────────────────┐" << endl;
    cout << "│  [1] ⚡ Immediate Engagement           │" << endl;
    cout << "│  [2] ⚙  Custom Battle Plan             │" << endl;
    cout << "│  [3] ⬅  Return to Command Bridge       │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
    cout << "\n>>> Select your directive (1-3): ";
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
            cout << "\n❌ Command unclear. Please issue a valid order.\n" << endl;
            personVsComputer();
    }
}

void pvcQuickGame() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║        ⚡ QUICK DEPLOYMENT ⚡          ║" << endl;
    cout << "╚════════════════════════════════════════╝\n" << endl;

    string player1 = "Player";
    string player2 = "Computer";

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);
    
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << ">>> Do you want to place your fleet manually? (y/n): ";
    string choice;
    cin >> choice;

    if (choice == "y") {
        cout << "\n┌─ MANUAL DEPLOYMENT ──────────────────┐" << endl;
        cout << "│ Prepare to position your armada...   │" << endl;
        cout << "└──────────────────────────────────────┘\n" << endl;
        
        vector<Ship> defaultShips = getDefaultShips();
        // get coordinate and place each ship
        int shipNum = 1;
        for (Ship& ship : defaultShips) {
            cout << "\n┌──────────────────────────────────────┐" << endl;
            cout << "│  ⚓ Deploying Vessel " << shipNum << " of 5          │" << endl;
            cout << "└──────────────────────────────────────┘" << endl;
            cout << "   Ship: " << ship.getName() << " (Length: " << ship.getLength() << ")\n" << endl;

            string direction = directionSetup();
            ship.setShipProperties(ship.getName(), direction, ship.getLength());

            vector<int> shipCoord = coordinateSetup(player1Board, ship);
            int ship_y_coord = shipCoord[0];
            int ship_x_coord = shipCoord[1];

            addShipToBoard(player1Board, ship, ship_y_coord, ship_x_coord, ship.getDirection());
            printBoard(player1Board);
            cout << "\n✓ Ship anchored successfully!\n" << endl;
            shipNum++;
        }

    } else {
        cout << "\n⚡ Auto-deploying fleet to strategic positions...\n" << endl;
        randomizeShipOnBoard(player1Board);
    }
    
    cout << "⚡ Deploying enemy AI fleet...\n" << endl;
    randomizeShipOnBoard(player2Board);

    player2Board.setHideShips(true);

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
