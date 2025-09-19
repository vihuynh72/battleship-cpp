#include "../include/bot.h"
#include "../../board/include/board.h"
#include "../../ship/include/ship.h"
#include "../../space/include/space.h"
#include "../../../ui/ingame/include/ingameHelper.h"

#include <random>

using namespace std;

void randomizeShipOnBoard(Board& botBoard) {    // Randomly place 5 ships of varying sizes on the board
    for (int i = 0; i < 5; ++i) {
        Ship ship;
        string ShipName = to_string(i + 1);
        int ShipLength = nextInt(2, 5);
        string direction = (nextInt(0, 1) == 0) ? "horizontal" : "vertical";

        ship.setShipProperties(ShipName, direction, ShipLength);
        bool placed = false;

        while (!placed) {
        int row = nextInt(0, botBoard.getRows() - 1);
        int col = nextInt(0, botBoard.getColumns() - 1);
        if (checkAvailableSpace(botBoard, ship, row, col, direction)) {
            addShipToBoard(botBoard, ship, row, col, direction);
            placed = true;
          }
      }
    }
    printBoard(botBoard);
}

int nextInt(int lo, int hi) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(rng);
}

                                                                                    
                                                                                                                                        