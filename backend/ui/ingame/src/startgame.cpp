#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../include/ingame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../common/include/uiTheme.h"

#include <iostream>
#include <string>

using namespace std;
using namespace ui::theme;

void startPvcGame(Board& player1, Board& player2) {
    clearScreen();
    printDivider('=', 60);
    cout << accent("             Battle Stations: PvC Engage             ") << endl;
    printDivider('=', 60);
    cout << success("Admiral ") << success(player1.getPlayerName())
         << accent(" vs AI Fleet Commander ") << warning(player2.getPlayerName()) << endl;
    cout << muted("Synchronizing targeting systems...") << endl;
    loadingPulse("Synchronizing targeting systems");
    cout << success("Systems green. Commence assault!\n") << endl;

    ingame(player1, player2);
}

void startPvPGame(Board& player1, Board& player2) {
    clearScreen();
    printDivider('=', 60);
    cout << accent("             Battle Stations: PvP Engage             ") << endl;
    printDivider('=', 60);
    cout << success("Admiral ") << success(player1.getPlayerName())
         << accent(" vs Admiral ") << success(player2.getPlayerName()) << endl;
    cout << muted("Both fleets ready. May the best strategist prevail!\n") << endl;

    ingame(player1, player2);
}
