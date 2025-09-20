//Migrate the ship functions from mechanics to here
#ifndef MECHANICS_SHIP_H
#define MECHANICS_SHIP_H

#include <string>
#include "../../../board/include/board.h"
#include "../../../ship/include/ship.h"

void addShipToBoard(Board&, Ship&, int, int, std::string);
void attackShipOnBoard(Board&, int, int);
bool checkShipSunk(Ship&);
std::vector<Ship> getDefaultShips();

#endif // MECHANICS_SHIP_H