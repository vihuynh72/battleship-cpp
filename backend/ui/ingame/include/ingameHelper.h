#ifndef INGAMEHELPER_H
#define INGAMEHELPER_H

#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

void printBoard(Board&);
void printShipList(Board&);
void printShipInfo(Ship&);

bool checkGameOver(Board&, Board&);

bool validateCoord(std::string, Board&);
std::vector<int> coordToInt(std::string);
void printBoardSideBySide(Board&, Board&, bool hideSecondBoardShips = true);
void printBoardRow(Board&, int, bool, bool hideShips = false);

#endif // INGAMEHELPER_H
