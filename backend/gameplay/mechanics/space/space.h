#ifndef SPACE_H
#define  SPACE_H

#include <string>
#include "../board/board.h"
#include "../ship/ship.h"

bool checkEmptyCell(std::string);
bool checkOutOfBounds(Board&, int, int);
bool checkAvailableSpace(Board&, Ship&, int, int, std::string);
  
#endif // SPACE_H