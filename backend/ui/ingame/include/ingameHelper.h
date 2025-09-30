#ifndef INGAMEHELPER_H
#define INGAMEHELPER_H

#include "../../../gameplay/board/include/board.h"

void printBoard(Board&);
void printShipList(Board&);
void printShipInfo(Ship&);

bool checkGameOver(Board&, Board&);

bool validateCoord();

#endif // INGAMEHELPER_H