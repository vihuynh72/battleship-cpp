//Migrate the ship functions from mechanics to here
#ifndef MECHANICS_SHIP_H
#define MECHANICS_SHIP_H

#include <string>
#include "../../board/board.h"
#include "../../ship/ship.h"

void addShipToBoard(Board&, Ship&, int, int, std::string);
void attackShipOnBoard(Board&, int, int);
bool checkShipSunk(Ship&);

#endif // MECHANICS_SHIP_H