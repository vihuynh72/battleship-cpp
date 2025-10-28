#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/game/include/game.h"
#include "../../../gameplay/mechanics/game/include/game.h"
#include "../include/ingame.h"
#include "../include/ingameHelper.h"

#include <iostream>
#include <string>

using namespace std;

void pvcIngame(Board& player1, Board& player2) {
    pvcGame game(player1, player2);

    while (checkGameOver(player1, player2) == false) {
        game.playerTurn();
        if (checkGameOver(player1, player2) == true) {
            break;
        }
        game.computerTurn();
        printBoardSideBySide(player1, player2);
    }

    Board& winner = checkWinner(player1, player2);
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║                                        ║" << endl;
    cout << "║             ⚔ GAME OVER ⚔              ║" << endl;
    cout << "║                                        ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n┌────────────────────────────────────────┐" << endl;
    cout << "│  🏆 VICTORY: " << winner.getPlayerName();
    // Calculate padding
    int nameLen = winner.getPlayerName().length();
    int padding = 40 - 14 - nameLen - 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "  │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
    cout << "\n⚓ Triumph belongs to Admiral " << winner.getPlayerName() << "!" << endl;
    cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "    Well played, Commander." << endl;
    cout << "    Fleet status of the victor:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    printShipList(winner);
    cout << "\n⚓ Thank you for playing Battleship! ⚓\n" << endl;
}

void playerTurn(Board& player) {
    
}

void attackTurn(Board& player, int row, int col) {

}
