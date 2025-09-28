#include "../include/game.h"
#include "../include/gameMode.h"
#include "../../board/include/board.h"
#include "../../mechanics/bot/include/bot.h"

Game::Game() : player1Board(nullptr), player2Board(nullptr), isPvP(false), rules(*(new GameMode())) {
    // Default constructor implementation
}

Game::Game(Board& p1Board, Board& p2Board) : player1Board(p1Board), player2Board(p2Board), isPvP(false), rules(*(new GameMode())) {
    // Constructor with boards to start a PVC game
}

void pvcGame::computerTurn() {
    Board& playerBoard = getPlayer1Board(); // AI will get player 1's board and interact with it

    int row, col;
    row = nextInt(0, playerBoard.getRows() - 1);
    col = nextInt(0, playerBoard.getColumns() - 1);

    // Check if cell is not already attacked
    while (playerBoard.getBoard()[row][col] == "[X]" || playerBoard.getBoard()[row][col] == "[.]") {
        row = nextInt(0, playerBoard.getRows() - 1);
        col = nextInt(0, playerBoard.getColumns() - 1);
    }

    attackShipOnBoard(playerBoard, row, col);
}

    
