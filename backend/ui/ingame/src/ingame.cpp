#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/game/include/game.h"
#include "../../../gameplay/mechanics/game/include/game.h"
#include "../include/ingame.h"
#include "../include/ingameHelper.h"

#include <iostream>
#include <string>

using namespace std;

void ingame(Board& player1, Board& player2) {
    pvcGame game(player1, player2);

    while (checkGameOver(player1, player2) == false) {
        game.playerTurn();
        // Print Computer Board after player's turn
        printBoard(player2);
        if (checkGameOver(player1, player2) == true) {
            break;
        }
        game.computerTurn();
        // Print Player Board after computer's turn
        printBoard(player1);
    }
}

void playerTurn(Board& player) {
    
}

void attackTurn(Board& player, int row, int col) {

}