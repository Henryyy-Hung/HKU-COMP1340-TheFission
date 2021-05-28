// File name: explore.h
// Author: Hung Ka Hing
// UID: 3035782750
// Description: Hold the function header of explore.cpp and provide self defined structure and external libraries to explore.cpp

#ifndef EXPLORE_H
#define EXPLORE_H

#include "structure.h"			// include self defined structure and external libraries

void map_generator(int**, int);

void extend_map(int** &, int&, Point&);

void maze(int**, Point);

bool moved(Profile&, int**, Point&, char);

bool bag_manipulation(Profile&, char);

void detect(Profile, int**, Point);

#endif
