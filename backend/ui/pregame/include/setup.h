#ifndef SETUP_H
#define SETUP_H

#include "../../gameplay/board/board.h"
#include "../../gameplay/ship/ship.h"

#include <string>
#include <vector>

int dimensionSetup();
std::string playerSetup();
Ship shipSetup(Board&);

#endif // SETUP_H