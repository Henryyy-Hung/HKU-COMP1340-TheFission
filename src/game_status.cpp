// File name: game_status.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold functions regarding initilize the game, load the game, and save the game. And to facilitate modularization.

#include "game_status.h"				// include self defined structures, external library, and function header of game_status.cpp

// Input: profile of player
// Return: void
// Function: to initilize the profile fo player and set all values to be default value
void initialize(Profile& player)
{
	player.time.set(9,0);				// set up values in profile of player
	player.location.set(0,0);
	player.hp.set(100);
	player.sp.set(100);
	player.hr.set(0);
	player.destiny = 1000;	
	player.attack = 15;
	for (int i = 0; i < 10; i++)
		player.item[i] = 3;			// set all the item's quantity to be 3
}

// Input: profile of player
// Return: 0 or 1 which indicate manipulation success or failed respectively
// Function: to load pre-exist player profile from external file and return its validity
int load(Profile& player)
{
	ifstream fin;
	fin.open("profile.txt");			// open file called profile.txt

	if (fin.fail())
		return 1;				// indicate failed to load
	else
	{
		fin >> player.time.hour			// load up time from external file
			>> player.time.min;

		fin >> player.location.x		// load the location
			>> player.location.y;

		fin >> player.hp.quantity 		// load status
			>> player.sp.quantity 
			>> player.hr.quantity;

		fin >> player.destiny;			// load destiny

		fin >> player.attack;			// load attack point

		for (int i = 0; i < 10; i++)
			fin >> player.item[i];		// load quantity of items

		fin.close();				// close file

		return 0;				// indicate load succeed
	}
}

// Input: profile of player
// Output: 0 or 1 which indicate manipulation succeed or failed repectively
// Function: to save the game status in external file and indicate validity of saving
int save(Profile player)
{
	ofstream fout;
	fout.open("profile.txt");

	if (fout.fail())
		return 1;				// indicates fail to save
	else						// save player's data just as above functions
	{
		fout << player.time.hour << " " << player.time.min << endl;

		fout << player.location.x << " " << player.location.y << endl;

		fout << player.hp.quantity << " "
			<< player.sp.quantity << " "
			<< player.hr.quantity << endl;

		fout << player.destiny << endl;

		fout << player.attack << endl;

		for (int i = 0; i < 10; i++)
			fout << player.item[i] << " ";

		fout << endl;

		fout.close();				// close file

		return 0;				// indicate savng succeed
	}
}

