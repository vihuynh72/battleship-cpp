#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../include/ingame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>

using namespace std;

void startPvcGame(Board& player1, Board& player2) {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║                                        ║" << endl;
    cout << "║          ⚔ BATTLE STATIONS ⚔           ║" << endl;
    cout << "║                                        ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
     cout << "\n┌────────────────────────────────────────────────┐" << endl;
    cout << "│ Engaging " << player1.getPlayerName() << " and " << player2.getPlayerName() << " in naval combat!  │" << endl;
    cout << "└────────────────────────────────────────────────┘" << endl;
    cout << "\n💡 TIP: Type \"show\" to reveal enemy fleet" << endl;
    cout << "💡 TIP: Type \"hide\" to restore fog of war" << endl;
    cout << "💡 TIP: Type \"kill\" to instantly win (debug)" << endl;
    cout << "\n⚓ All hands to action stations!\n" << endl;
    printBoardSideBySide(player1, player2);
    pvcIngame(player1, player2);
}


void startPvPGame(Board& player1, Board& player2) {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║                                        ║" << endl;
    cout << "║          ⚔ BATTLE STATIONS ⚔           ║" << endl;
    cout << "║                                        ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
     cout << "\n┌────────────────────────────────────────────────┐" << endl;
    cout << "│ Engaging " << player1.getPlayerName() << " and " << player2.getPlayerName() << " in naval combat!  │" << endl;
    cout << "└────────────────────────────────────────────────┘" << endl;
    cout << "\n💡 TIP: Type \"show\" to reveal enemy fleet" << endl;
    cout << "💡 TIP: Type \"hide\" to restore fog of war" << endl;
    cout << "\n⚓ All hands to action stations!\n" << endl;
    printBoardSideBySide(player1, player2);
    pvcIngame(player1, player2);
}