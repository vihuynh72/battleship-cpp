#ifndef MECHANICS_SPACE_H
#define MECHANICS_SPACE_H

#include <string>
#include "../../board/board.h"
#include "../../ship/ship.h"

bool checkEmptyCell(std::string);
bool checkOutOfBounds(Board&, int, int);
bool checkAvailableSpace(Board&, Ship&, int, int, std::string);

#endif // MECHANICS_SPACE_H