#ifndef SETUP_H
#define SETUP_H

#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <string>
#include <vector>

int dimensionSetup();
std::string playerSetup();
Ship shipSetup(Board&);

#endif // SETUP_H