// File name: survival.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold functions regarding survival of the player

#include "survival.h" 					// include self defined structures, external library, and function header of game_status.cpp

const double difficulty = 50.0 / 100.0;			// 100% difficulty means Hr can only support the activity of 1 day

// Input: profile of player
// Return: a double value recording the amount of time pass
// Function: update both time and status of player
double update_status(Profile& player)
{
	double time_passed = rand() % 60;

	player.time.change(time_passed);

	double value = (time_passed / 15.0) * difficulty;

	switch ( player.hr.quantity < 100 )
	{
		case true:
			player.hr.change( value );
			break;
		case false:
			player.hp.change( - value * 2.0 );
			break;
	}

	return value;
}

// Input: profile of player
// Return: void
// Function: update both time and status of player after move
void status_after_move(Profile& player)
{
	double value = update_status(player);

	player.sp.change( - value * 3.0 );					// decrease stamina point after move
}

// Input: profile of player
// Return: void
// Function: update both time and status of player after rest
void status_after_rest(Profile& player)
{
	double value = update_status(player);

	player.hp.change( value * 0.5 );					// increase hp after rest
	player.sp.change( value * 1.5 );					// increase sp after rest
}

// Input: profile of player
// Return: int
// Function: check whether game is over
int game_over(Profile player)
{
	switch (player.hp.quantity == 0)
	{
		case true:
			return 1;
		case false:
			return 0;
	}
}

