#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/game/include/game.h"
#include "../../../gameplay/mechanics/game/include/game.h"
#include "../include/ingame.h"
#include "../include/ingameHelper.h"
#include "../../common/include/uiTheme.h"

#include <iostream>
#include <string>

using namespace std;
using namespace ui::theme;

void ingame(Board& player1, Board& player2) {
    pvcGame game(player1, player2);

    printBoardSideBySide(player1, player2);

    while (checkGameOver(player1, player2) == false) {
        cout << accent("\nCommander, plot your strike coordinates!") << endl;
        game.playerTurn();
        printBoardSideBySide(player1, player2);
        if (checkGameOver(player1, player2) == true) {
            break;
        }
        cout << warning("Enemy fleet is retaliating...") << endl;
        game.computerTurn();
        printBoardSideBySide(player1, player2);
    }

    Board& winner = checkWinner(player1, player2);
    cout << endl;
    printVictoryBanner(winner.getPlayerName());
    cout << success("The seas belong to " + winner.getPlayerName() + "!\n") << endl;
    cout << accent("Flagship Status Report:") << endl;
    printShipList(winner);
    cout << muted("Thank you for playing Battleship Commander!") << endl;
}

void playerTurn(Board& player) {

}

void attackTurn(Board& player, int row, int col) {

}