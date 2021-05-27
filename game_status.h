// File name: game_status.h
// Author: Hung Ka Hing
// UID: 3035782750
// Description: Hold the function header of game_status.cpp and provide self defined structure and external libraries to game_status.cpp

#ifndef GAME_STATUS_H
#define GAME_STATUS_H

#include "structure.h"			// include self defined structure and external libraries

void initialize(Profile&);

int load(Profile&);

int save(Profile);

#endif

