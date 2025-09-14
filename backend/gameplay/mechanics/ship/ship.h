//Migrate the ship functions from mechanics to here
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include "../board/board.h"
#include "../ship/ship.h"

Board addShipToBoard(Board&, Ship&, int, int, std::string);
Board attackShipOnBoard(Board&, int, int);
bool checkShipSunk(Ship&);

#endif // SHIP_H