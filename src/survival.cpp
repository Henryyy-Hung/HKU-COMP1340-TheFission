// File name: survival.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold functions regarding survival of the player

#include "survival.h" 					// include self defined structures, external library, and function header of game_status.cpp

const double difficulty = 1;
const double ratio = 15 / difficulty;

// Input: profile of player
// Return: a double value recording the amount of time pass
// Function: update both time and status of player
double update_status(Profile& player)
{
	double time_passed = rand() % 60;
	player.time.change(time_passed);

	if (player.hr.quantity < 100)
		player.hr.change( time_passed / ratio );		// when time passed, increse hunger
	else
		player.hp.change( - time_passed / ratio );		// when time pass and hunger is full, decrease health point
	return time_passed;
}

// Input: profile of player
// Return: void
// Function: update both time and status of player after move
void status_after_move(Profile& player)
{
	double time_passed = update_status(player);
	player.sp.change( - time_passed / ratio );			// decrease stamina point after move
}

// Input: profile of player
// Return: void
// Function: update both time and status of player after rest
void status_after_rest(Profile& player)
{
	double time_passed = update_status(player);
	player.hp.change( time_passed / (ratio * 4.0 / 3.0) );		// increase hp after rest
	player.sp.change( time_passed / ratio );			// increase sp after rest
}

// Input: profile of player
// Return: int
// Function: check whether game is over
int game_over(Profile player)
{
	if (player.hp.quantity == 0)
		return 1;
	else
		return 0;
}

