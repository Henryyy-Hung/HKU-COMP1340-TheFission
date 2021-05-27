// File name: main.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To provide central framework of the game and facilitate modularization by allocating functions to other files.

#include "structure.h"						// include the self-defined structures and external libraries

#include "game_status.h"					// include functions to initiate, load and save game status (e.g. time,location,hp,etc.)
#include "interface.h"						// include functions to display user interface ( interface modules )

#include "survival.h"						// include functions to process the data regarding survival part(e.g. hp,sp,hr)
#include "explore.h"						// include functions to process the data regarding explore part(e.g. map,items)
#include "battle.h"						// include functions to process the data regarding battle
#include "story.h"						// include functions to process the data regarding story

// define some frequent output of text interface
string welcome = " Welcome to the world of The Fission !!!";
string new_game = " Enter 'n' to start a new game.";
string load_game = " Enter 'l' to load previous status.";
string invalid_input = " Invalid input. Please enter again.";
string failed = " Manipulation failed. Please enter again.";
string succeed = " Manipulation succeed. Press ENTER to continue.";
string invalid_move = " Encountered with boundary. Please move in another direction.";
string failed_to_move = " Your stamina point becomes ZERO. Please REST to recover it.";


bool operator == (const Point& a, const Point& b)
{
	return ( a.x == b.x && a.y == b.y);
}


void default_page(Profile, int**, Point);					// display status interface and map interface

void default_text(void);							// display text interface with command instruction

int main(int argc, char *argv[])
{
	Profile player;								// create a profile for player (record players data)
	initialize(player);							// initialize the profile of player (set default values)

	refresh(100);								// refresh the screen
	status_interface(player);						// display status interface
	logo_interface_fission();               			        // display the logo
	text_interface( format_lines(welcome, new_game, load_game) );		// display the log in page instruction

	while (true)
	{
		char command = input();						// show input interface and return input char

		if ( command == 'n' )						// to start a new game with default Profile
		{
			break;
		}
		else if ( command == 'l' )					// to load game with pre-exist profile
		{
			if ( load(player) == 1 )				// fail to load pre-exist profile
			{
				refresh(100);					// refresh the screen
				status_interface(player);			// display status interface and map interface
				logo_interface_fission();              	        // display the logo
				text_interface( format_lines(failed, new_game, load_game) );
				continue;					// allow user to make another choice
			}
			else
			{
				break;						// load success, enter the game with pre-exist profile
		
			}
		}
		else								// notice user to input again
		{
			refresh(100);						// refresh the screen
			status_interface(player);				// display status interface and map interface
			logo_interface_fission();               	        // display the logo
			text_interface( format_lines(invalid_input, new_game, load_game) );
		}
	}
	
	int map_len = (int) pow(2, 7) ;						// the edge length of a square map (max = 2^31)
	Point location = { (int) pow(2, 6), (int) pow(2, 6)};			// Actual location of player on the map

	int **map = new int *[map_len];						// initialize the dynamic 1D array to store map
	for (int row = 0; row < map_len; row++)
		map[row] = new int [map_len];					// map size = map_len * map_len

	map_generator(map, map_len);						// generate map with random distribution of buildings and events
	for (int i = location.x - 1; i <= location.x + 1; i++)
		for (int j = location.y - 1; j <= location.y + 1; j++)
			map[i][j] = 0;						// set the spawn point to be safe

	Node * story = initialize_story();					// bulld the story line and return the head of divergent linked list
	Point destiny = initialize_destiny(player, story);			// the location that trigger out story

	refresh(100);
	status_interface(player);
	logo_interface_fission();
	text_interface( format_lines(succeed, "", "") );			// notice user that his new/load game success in text interface
	
	bool game = true;							// breaker of game
	bool test = false;
	bool skip = false;							// skipper of round
	int warning_count = 0;							// times of warning for player
	if (argc > 1) test = true;


	while (game)								// refresh the interface whenever command is received
	{
		string temp1 = "", temp2 = "", temp3 = "";			// lines that will be printed in text interface
		char command;

		if (skip == false)
		{
			command = input();					// show input interface and return input char as command
		}
		else if (skip == true)
		{
			skip = false;
		}

		if ( command == 'w' || command == 'a' || command == 's' || command == 'd' )		// movement that trigger out events
		{
			if ( player.sp.quantity != 0 && moved(player, map, location, command) )		// judging and moving (by "moved()" function)
			{
				int event = map[location.x][location.y];				// event that represented by a number
				int randint = rand() % 100 + 1;						// set randint [1,100]
				int x = location.x, y = location.y;					// actual location of  player
				int min = 0, max = map_len - 1;						// the max and min of map location

				// extend map if the character is close to the boundary
				if ( ( max - x <= 20 || x - min <= 20 || max - y <= 20 || y - min <= 20 ) && map_len * 2 < pow(2, 14))
				{
					default_page(player, map, location);
					text_interface(" Loading......");
					
					extend_map(map, map_len, location);
				}

				if ( event == 1 )							// encounter with unknown building
				{
					temp1 = " You encountered with an unknown building.";
					if ( randint > 10 )						// 90 % get nothing
						temp2 = " You have found nothing there.";
					else								// 10 % get random item
					{
						temp2 = " It seems that you have found somthing?";
						temp3 = " Check your bag.";
						player.item[rand() % 9] += 1;
					}
				}
				else if ( event == 2 )							// encounter with water source
				{
					temp1 = " You encountered with a water source.";

					if ( randint > 20 )						// 80 % get radiated water
					{
						player.item[7] += 1;
						temp2 = " You get Radiated Water x 1.";
					}
					else								// 20 % get pure water
					{
						player.item[5] += 1;
						temp2 = " You get Pure Water x 1.";
					}
				}
				else if ( event == 3 )							// encounter with hospital
				{
					temp1 = " You encountered with a hospital.";
					if ( randint > 50 )
						temp2 = " You have found nothing there.";
					else if ( randint > 25 )
					{
						player.item[8] += 1;					// 25 % get iodophor (anti-radiation drug)
						temp2 = " You get Iodophor x 1.";
					}
					else if ( randint > 10 )					// 15 % get adrenaline
					{
						player.item[6] += 1;
						temp2 = " You get Adrenaline x 1.";
					}
					else if ( randint > 3 )						// 7 % get bondage
					{
						player.item[1] += 1;
						temp2 = " You get Bondage x 1.";
					}
					else								// 3 % get unknown potion
					{
						player.item[0] += 1;
						temp2 = " You get Unknown Potion x 1.";
					}
				}
				else if ( event == 4 )							// encounter with food shop
				{
					temp1 = " You encountered with a food shop.";
					if ( randint > 50 )						// 50 % get radiated cake
					{
						player.item[4] += 1;
						temp2 = " You get Radiated Cake x 1.";
					}
					else if ( randint > 20 )					// 30 % get radiated meat
					{
						player.item[3] += 1;
						temp2 = " You get Radiated Meat x 1.";
					}
					else								// 20 % get meat
					{
						player.item[2] += 1;
						temp2 = " You get Meat x 1.";
					}
				}
				else if ( event == 5 && player.attack < 100 )		// encounter with weapon shop
				{
					player.attack++;
					temp1 = " You encountered with a weapon shop.";
					temp2 = " Your attack increase by " + itoa(1,'u') + " and become " + itoa(player.attack, 'u') + ".";
				}
				else if ( (event == 10 || event == 99) && ! test )	// encounter with Monster
				{
					map[location.x][location.y] = 0;		// remove the event from the map after enconter it.
					battle(player, map, location);			// enter the battle interface and manipulte everything there
				}
				else if ( event == 11  && ! test)			// encounter wiht maze
				{
					refresh(100);
					status_interface(player);
					logo_interface_maze();
					string maze_1 = " You have encountered with a maze.";
					string maze_2 = " The exit is on the top right and bottom left corner.";
					string maze_3 = " Press ENTER to continue.";
					text_interface( format_lines( maze_1, maze_2, maze_3) );
					input();
					maze(map,location);				// generate a maze centered at character
				}

				map[location.x][location.y] = 0;			// remove the symbol from map after explored it

				if (! test ) status_after_move(player);			// update the status of character after action

				if ( player.hr.quantity < 100 )				// reset the warning
					warning_count = 0;
				else if ( player.hr.quantity == 100 && warning_count < 3 && event != 10)	
				// warn the player when he is starving at most 3 times
				{
					default_page(player, map, location);
					string warning_1 = " Warning! You are in starving status!";
					string warning_2 = " Please eat something to avoid drop in HP!!!";
					string warning_3 = " Press ENTER to continue.";
					text_interface( format_lines( warning_1, warning_2, warning_3 ) );
					input();
					warning_count++;
				}

			}
			else if ( player.sp.quantity == 0 )				// notice player to rest and recover SP
				temp1 = failed_to_move;
			else
				temp1 = invalid_move;					// notice player there is a wall and cannot pass it
		}
		else if ( command == 'r' )						// rest that recover SP
		{
			status_after_rest(player);					// update the status of player
			temp1 = " You haved rested and recover a bit of HP and SP.";
			temp2 = " Press ENTER to continue.";
		}
		else if ( command == 'b' )						// turn into bag page and allow using of items
		{
			bag_manipulation(player, 'e');					// enter bag page with explore mode (can use multiple items)
		}
		else if ( command == 'm' )						// show the manual page of the game
		{
			refresh(100);							// refresh the terminal
			status_interface(player);					// show status interface (time, hp, sp, hr)
			manual_interface();						// show manual page
			text_interface(" Press ENTER to continue.");
			input();							// don't receive any command after manual page
		}
		else if ( command == 'z' )						// save the game
		{
			if ( save(player) == 1 )					// judging whether the save is succeed
				temp1 = failed;						// notice player the save failed
			else
				temp1 = succeed;					// notice player the save success
		}
		else if ( command == 'n' )						// show the location, destiny, direction and distance
		{
			refresh(100);
			default_page(player, map, location);
			navigator_interface(player, destiny);
			input();
		}
		else if ( command == 'l' )
		{
			int monster = 0;

			for (int i = location.x - 1; i <= location.x + 1; i++)
			{
				for (int j = location.y - 1; j <= location.y + 1; j++)
				{
					if ( map[i][j] == 10 || map[i][j] == 99)
					{
						monster++;
						map[i][j] = 99;
					}
				}
			}

			string line_1 = " There are " + itoa(monster, 'u') + " monster is found around 3 x 3 grids.";
			string line_2 = " Safe area has been labelled.";
			string line_3 = " Press ENTER to continue.";

			refresh(100);
			default_page(player, map, location);
			text_interface( format_lines( line_1, line_2, line_3) );
			input();	
		}
		else if ( command == '!' )						// quit the game (end the while loop)
		{
			game = false;
			temp1 = " Quit Successfully";					// notice user the game is quited
		}

		for (int i = -1; i <= 1; i++)						// search whether there is story around the player (3 x 3)
		{
			for (int j = -1; j <= 1; j++)
			{
				Point temp = player.location;
				temp.change(i, j);
				if (temp == destiny)					// check the triggering position
				{
					int value = display_story(player, story);	// check the existance of story.txt and play story
					if (value == 1)
					{
						temp1 = " Please download the story.txt. ";
					}
					else if (value == 0)
					{
						skip = true;
					}
					else if (value == 2)
					{
						skip = false;
					}
					destiny = initialize_destiny(player, story);	// update destiny
				}
			}
		}

		if ( game_over(player) )						// check the remaining amount of blood
		{
			refresh(100);							// if yes, print out loss logo and quit the game
			status_interface(player);
			logo_interface_loss();
			text_interface( format_lines(" Your Health Point drops to ZERO.", " Game Over.", " Press ENTER to continue.") );
			input();

			refresh(100);
			status_interface(player);
			logo_interface_loss();
			text_interface( format_lines(" 1. Load from Save.", " 2. New Game.", " 3. Exit Game") );
			char choice = input();

			bool loop = true;

			while (loop)
			{
				string line_1 = "", line_2 = "", line_3 = "";

				if (choice == '3')
				{
					game = false;
					refresh(100);
					break;
				}
				else if (choice == '2')
				{
					game = true;
					loop = false;
					initialize(player);
					destiny = initialize_destiny(player, story);			// the location that trigger out story
					line_1 = " Initialize success.";
					line_2 = " Press ENTER to continue.";
				}
				else if (choice == '1')
				{
					if (load(player) == 1)
					{
						loop = true;
						line_1 = " Fail to load.";
						line_2 = " Press ENTER to make another command.";
					}
					else
					{
						loop = false;
						line_1 = " Load success.";
						line_2 = " Press ENTER to continue.";
					}
				}
				else
				{
					loop = true;
					line_1 = " 1. Load from Save.";
					line_2 = " 2. New Game.";
					line_3 = " 3. Exit Game.";
				}
				{
					refresh(100);
					status_interface(player);
					logo_interface_loss();
					text_interface(format_lines(line_1, line_2, line_3));
					if (loop) choice = input();
				}
			}
		}
		else
		{
			default_page(player, map, location);				// print the status interface and map interface
			if ( temp1 != "" || temp2 != "" || temp3 != "" )
				text_interface( format_lines(temp1, temp2, temp3) );	// print the text interface with specified content
			else
				default_text();						// print the default text interface
		}
	}

	for (int column = 0; column < map_len; column++)				// release memory occupied by the 2D array "map"
		delete[] map[column];

	delete[] map;

	return 0;
}

// Input data: profile of player, map, actual location
// Return data: void
// Function: refresh the screen and print interface(status + map) on the screen
// Meaning: save time
void default_page(Profile player, int **map, Point location)
{
	refresh(100);
	status_interface(player);
	map_interface(map, location);
}

// Input data: void
// Return data: void
// Function: print the text interface with command instruction
// Meaning: more clear present in main function
void default_text(void)
{
	string line_1 = " Command list:";
	string line_2 = format_grids( " Move: W A S D", " Rest:   R", "Bag:  B", "Navigator: N");
	string line_3 = format_grids( " Detect: L"    , " Manual: M", "Save: Z", "Quit: !");
	string output = format_lines(line_1, line_2, line_3);
	text_interface(output);
}

