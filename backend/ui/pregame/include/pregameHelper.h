#ifndef PREGAME_HELPER_H
#define PREGAME_HELPER_H

#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <string>
#include <vector>

std::vector<int> dimensionSetup();
std::vector<std::string> playerSetup(bool);
Ship shipSetup(Board&);

std::string directionSetup();
int lengthSetup();
std::vector<int> coordinateSetup(Board&, Ship&);

void placeShip(Board&, int, int);

#endif // PREGAME_HELPER_H