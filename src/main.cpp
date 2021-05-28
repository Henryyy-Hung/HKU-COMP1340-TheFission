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

bool operator == (const Point& a, const Point& b)
{
	return ( a.x == b.x && a.y == b.y);
}


void default_page(Profile, int**, Point);					// display status interface and map interface

void default_text(void);							// display text interface with command instruction

void log_in_page(Profile &);

bool restart(Profile &);

int main(int argc, char *argv[])
{
	Profile player;								// create a profile for player (record players data)
	initialize(player);							// initialize the profile of player (set default values)
	log_in_page(player);							// initialize the profile of player according to his command

	int map_len = (int) pow(2, 7) ;						// the edge length of a square map (max = 2^31)
	Point location = { (int) pow(2, 6), (int) pow(2, 6)};			// Actual location of player on the map

	int **map = new int *[map_len];						// initialize the dynamic 1D array to store map
	for (int row = 0; row < map_len; row++)
		map[row] = new int [map_len];					// map size = map_len * map_len

	map_generator(map, map_len);						// generate map with random distribution of buildings and events
	for (int i = location.x - 2; i <= location.x + 2; i++)
		for (int j = location.y - 2; j <= location.y + 2; j++)
			if ( map[i][j] >= 10 )
				map[i][j] = 0;					// set the spawn point to be safe

	Node * story = initialize_story();					// bulld the story line and return the head of divergent linked list
	Point destiny = initialize_destiny(player, story);			// the location that trigger out story

	bool skip = true;
	int warning_count = 0;							// times of warning for player

	bool hold = true;
	char command;
	string lines[3];

	while (true)								// refresh the interface whenever command is received
	{
		if ( hold == false || (game_over(player) && !restart(player)) )
		{
			lines[0] = " Quit sucessfully.";
			lines[1] = "";
			lines[2] = "";
			refresh(100);
			status_interface(player);
			black_screen();
			text_interface(format_lines(lines[0], lines[1], lines[2]));
			break;
		}
		else if ( lines[0].empty() && lines[1].empty() && lines[2].empty() )
		{
			default_page(player, map, location);
			default_text();
		}
		else if ( !skip )
		{
			default_page(player, map, location);
			text_interface(format_lines(lines[0], lines[1], lines[2]));
		}

		if ( !skip )
		{
			command = input();
		}
		else
		{
			command = '\0';
			skip = false;
		}

		{
			destiny = initialize_destiny(player, story);
			lines[0] = "";
			lines[1] = "";
			lines[2] = "";
		}
		
		switch ( command )
		{
			case '!':
				hold = false;
				break;

			case 'z':
				switch ( save(player) )
				{
					case 0:
						lines[0] = " Game saved.";
						lines[1] = " Press ENTER to continue.";
						break;
					case 1:
						lines[0] = " Save failed.";
						lines[1] = " Press ENTER to continue.";
						break;
				}
				break;

			case 'm':
				refresh(100);							
				status_interface(player);					
				manual_interface();						
				text_interface(" Press ENTER to continue.");
				input();
				break;

			case 'l':
				detect(player, map, location);
				break;

			case 'n':
				refresh(100);
				default_page(player, map, location);
				navigator_interface(player, destiny);
				input();
				break;

			case 'b':
				bag_manipulation(player, 'e');
				break;

			case 'r':
				status_after_rest(player);
				lines[0] = " You haved rested and recover a bit of HP and SP.";
				lines[1] = " Press ENTER to continue.";
				break;

			case 'w': case 'a': case 's': case 'd':
				if ( player.sp.quantity == 0 )
				{
					lines[0] = " Yours SP become 0.";
					lines[1] = " Please rest to recover SP.";
					lines[2] = " Press ENTER to continue.";
				}
				else if ( ! moved(player, map, location, command) )
				{
					lines[0] = " Encountered with boundary.";
					lines[1] = " Please move in another direction.";
					lines[2] = " Press ENTER to continue.";
				}
				else
				{
					int x = location.x, y = location.y;
					int event = map[x][y];
					int randint = rand() % 100 + 1;
					int min = 0, max = map_len - 1;

					status_after_move(player);
					map[x][y] = 0;

					if ( ( max - x <= 20 || x - min <= 20 || max - y <= 20 || y - min <= 20 ) && map_len * 2 < pow(2, 31))
					{
						extend_map(map, map_len, location);
					}

					switch ( event )
					{
						case 1:
							lines[0] = " You encountered with an Unkonwn Building.";
							if ( randint <= 10 )
							{
								player.item[rand() % 9]++;
								lines[1] = " It seems that you have found something?";
								lines[2] = " Check your bag.";
							}
							else
							{
								lines[1] = " Your have found nothing there.";
							}
							break;
						
						case 2:
							lines[0] = " You encountered with a water source.";
							if ( randint <= 33 )
							{
								player.item[5]++;
								lines[1] = " You got Pure Water x 1.";
							}
							else
							{
								player.item[7]++;
								lines[1] = " You got Radiated Water x 1.";
							}
							break;
						case 3:
							lines[0] = " You encountered with a hospital.";
							if ( randint > 50 )
							{
								lines[0] = " You have found nothing there.";
							}
							else if ( randint > 25 )
							{
								player.item[8]++;				
								lines[1] = " You got Iodophor x 1.";
							}
							else if ( randint > 10 )				
							{
								player.item[6]++;
								lines[1] = " You got Adrenaline x 1.";
							}
							else if ( randint > 3 )					
							{
								player.item[1]++;
								lines[1] = " You got Bondage x 1.";
							}
							else								
							{
								player.item[0]++;
								lines[1] = " You got Unknown Potion x 1.";
							}
							break;
						case 4:
							lines[0] = " You encountered with a food shop.";
							if ( randint > 50 )						
							{
								player.item[4]++;
								lines[1] = " You got Radiated Cake x 1.";
							}
							else if ( randint > 20 )					
							{
								player.item[3]++;
								lines[1] = " You got Radiated Meat x 1.";
							}
							else						
							{
								player.item[2]++;
								lines[1] = " You got Meat x 1.";
							}
							break;
						case 5:
							player.attack++;
							lines[0]  = " You encountered with a weapon shop.";
							lines[1]  = " Your attack become " + itoa(player.attack, 'u') + " + 1.";
							break;
						case 10: case 99:
							battle(player, map, location);
							break;
						case 11:
							refresh(100);
							status_interface(player);
							logo_interface_maze();
							string maze_1 = " You have encountered with a maze.";
							string maze_2 = " The exit is on the top right and bottom left corner.";
							string maze_3 = " Press ENTER to continue.";
							text_interface( format_lines( maze_1, maze_2, maze_3) );
							input();
							maze(map,location);
							break;
					}
				}

			default:
				if ( player.hr.quantity < 100 )
				{
					warning_count = 0;
				}
				else if ( player.hr.quantity == 100 && warning_count < 3 )	
				{
					string warning[3];
					default_page(player, map, location);
					warning[0] = " Starving !!!";
					warning[1] = " Please eat something to avoid drop in HP!!!";
					warning[2] = " Press ENTER to continue.";
					text_interface( format_lines( warning[0], warning[1], warning[2] ) );
					input();
					warning_count++;
				}
				break;
		}

		for (int i = -1; i <= 1; i++)						// search whether there is story around the player (3 x 3)
			for (int j = -1; j <= 1; j++)
			{
				Point temp = player.location;
				temp.change(i, j);
				if (temp == destiny)					// check the triggering position
				{
					int value = display_story(player, story);	// check the existance of story.txt and play story
					if (value == 1)
					{
						lines[0] = " Please download the story.txt. ";
						lines[1] = "";
						lines[2] = "";
					}
					else if (value == 0)
					{
						skip = true;
					}
				}
			}
	}

	for (int column = 0; column < map_len; column++)				// release memory occupied by the 2D array "map"
		delete[] map[column];

	delete[] map;

	return 0;
}

// Input data: profile of player, map, actual location
// Function: refresh the screen and print interface(status + map) on the screen
void default_page(Profile player, int **map, Point location)
{
	refresh(100);
	status_interface(player);
	map_interface(map, location);
}

// Function: print the text interface with command instruction
void default_text(void)
{
	string lines[3];
	lines[0] = " Command list:";
	lines[1] = format_grids( " Move: W A S D", " Rest:   R", "Bag:  B", "Navigator: N");
	lines[2] = format_grids( " Detect: L"    , " Manual: M", "Save: Z", "Quit: !");
	
	text_interface( format_lines(lines[0], lines[1], lines[2]) );
}

void log_in_page(Profile & player)
{
	string lines[3];
	lines[0] = " Welcome to the world of The Fission !";
	lines[1] = " Press 'n' to start a new game.";
	lines[2] = " Press 'l' to load previous profile.";

	bool hold = true;

	while (true)
	{
		refresh(100);
		status_interface(player);
		logo_interface_fission();
		text_interface(format_lines(lines[0], lines[1], lines[2]));
		char command = input();	

		if ( ! hold )
		{
			break;
		}
		else if ( command == 'n' )				
		{
			hold = false;
			lines[0] = " Manipulation sucess.";
			lines[1] = " A new game is initialized.";
			lines[2] = " Press ENTER to continue.";
		}
		else if ( command == 'l' && load(player) == 0 )	
		{
			hold = false;
			lines[0] = " Load sucess.";
			lines[1] = " The game will start from previous status.";
			lines[2] = " Press ENTER to continue.";
		}
		else if ( command == 'l' )
		{
			lines[0] = " Load failed.";
		}
		else
		{
			lines[0] = " Invalid input, please enter again.";
		}

	}
}

bool restart(Profile & player)
{
	string lines[3];
	lines[0] = " 1. New game.";
	lines[1] = " 2. Load from save.";
	lines[2] = " 3. Exit game.";

	bool restart = true;
	bool hold = true;

	while (true)
	{
		refresh(100);
		status_interface(player);
		logo_interface_loss();
		text_interface( format_lines(lines[0], lines[1], lines[2]) );
		char command = input();

		if ( ! hold )
		{
			break;
		}
		else if ( command == '3' )
		{
			return false;
		}
		else if ( command == '2' && load(player) == 0 )
		{
			hold = false;
			lines[0] = " Load success.";
			lines[1] = " Press ENTER to continue.";
			lines[2] = "";
		}
		else if ( command == '2' )
		{
			lines[0] = " Load failed.";
			lines[1] = " Press ENTER to make another command.";
			lines[2] = "";
		}
		else if ( command == '1' )
		{
			hold = false;
			initialize(player);
			lines[0] = " A new game is ready.";
			lines[1] = " Press ENTER to continue.";
			lines[2] = "";
		}
		else
		{
			lines[0] = " 1. New game.";
			lines[1] = " 2. Load from save.";
			lines[2] = " 3. Exit game.";
		}
	}
	
	return true;
}
