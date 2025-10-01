#include "../include/game.h"
#include "../include/gameMode.h"
#include "../../board/include/board.h"
#include "../../mechanics/bot/include/bot.h"

#include <iostream>
#include <string>

Game::Game() : player1Board(nullptr), player2Board(nullptr), isPvP(false), rules(rulesInstance) {
    // Default constructor implementation
}

Game::Game(Board& p1Board, Board& p2Board) : player1Board(p1Board), player2Board(p2Board), isPvP(false), rules(rulesInstance) {
    // Constructor with boards to start a PVC game
}

void pvCGame::playerTurn() {
    Board& playerBoard = getPlayer2Board(); // Player will get player 2's board and interact with it
    int row, col;

    while (true) {
    cout << "Enter coordinates to attack (e.g., A5): ";
    string input;
    cin >> input;

    row = stoi(input.substr(1)) - 1; 
    col = toupper(input[0]) - 'A';

    // Validate input
    if (row < 0 || row >= playerBoard.getRows() || col < 0 || col >= playerBoard.getColumns()) {
        cout << "Invalid coordinates. Please try again." << endl;
        continue;
    }
}

void pvcGame::computerTurn() {
    Board& playerBoard = getPlayer1Board(); // AI will get player 1's board and interact with it

    int row, col;
    row = nextInt(0, playerBoard.getRows() - 1);
    col = nextInt(0, playerBoard.getColumns() - 1);

    // Check if cell is not already attacked
    while (playerBoard.getBoard()[row][col] == "[X]" || playerBoard.getBoard()[row][col] == "[O]") {
        row = nextInt(0, playerBoard.getRows() - 1);
        col = nextInt(0, playerBoard.getColumns() - 1);
    }

    attackShipOnBoard(playerBoard, row, col);
}

    
