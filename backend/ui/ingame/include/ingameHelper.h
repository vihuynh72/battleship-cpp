#ifndef INGAMEHELPER_H
#define INGAMEHELPER_H

#include "../../../gameplay/board/include/board.h"

void printBoard(Board&);
void printShipList(Board&);
void printShipInfo(Ship&);

bool checkGameOver(Board&, Board&);

bool validateCoord(std::string, Board&);
std::vector<int> coordToInt(std::string);
void printBoardSideBySide(Board&, Board&);
void printBoardRow(Board&, int, bool);

#endif // INGAMEHELPER_H