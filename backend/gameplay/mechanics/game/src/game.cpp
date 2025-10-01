#include "../include/game.h"
#include "../../../board/include/board.h"
#include "../../mechanics/board/include/board.h"
#include <stdexcept>

bool checkGameOver(Board& player1Board, Board& player2Board) {
    return checkAllShipsSunk(player1Board) || checkAllShipsSunk(player2Board);
}

Board& checkWinner(Board& player1Board, Board& player2Board) {
    if (checkAllShipsSunk(player1Board)) {
        return player2Board; // Player 2 wins
    } else if (checkAllShipsSunk(player2Board)) {
        return player1Board; // Player 1 wins
    }
    throw std::runtime_error("No winner yet, the game is still ongoing.");
}
