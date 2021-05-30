// File name: battle.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold functions regarding battle (i.e. battlefield generation, enemy generation, user manipulation, etc)

#include "battle.h"			// include self defined structures, external library, and function header of battle.cpp

#include "interface.h"
#include "survival.h"
#include "explore.h"

const int BATTLEFIELD_WIDTH = 5;					// vertical width of battlefield; the horizontal width is vertical width + 2

// Input: a dynamic 2D int array map, a point location of player, and a temp map to memory the original status of map
// Return: void
// Function: copy the content in battlefiel of original map to temp map
void battlefield_memory(int **map, Point location, int **temp_map)
{
	int x = location.x - 4;						// x and y origin of 9 x 7 wall around battlefield
	int y = location.y - 3;

	for (int i = 0; i < BATTLEFIELD_WIDTH + 4; i++)			// copy 9 x 7 battle field to temp map
		for (int j = 0; j < BATTLEFIELD_WIDTH + 2; j++)
			temp_map[i][j] = map[x + i][y + j];
}

// Input: a dynamic 2D int array map, a point location of player, and temp map that remembering original state of battlefield
// Return: void
// Function: recover the battlefield to the state before battle start (i.e. remove the wall, recover events)
void battlefield_recovery(int **map, Point location, int **temp_map)
{
	int x = location.x - 4;						// x and y origin of 9 x 7 wall around battlefield
	int y = location.y - 3;

	for (int i = 0; i < BATTLEFIELD_WIDTH + 4; i++)			// copy 9 x 7 element of temp map to world map
		for (int j = 0; j < BATTLEFIELD_WIDTH + 2; j++)
		{
			int temp = temp_map[i][j];
			if ( temp == 10 || temp == 99 )			// advoid player encounter monster within the battle field range after battle
				map[x + i][y + j] = 0;			// note: 10 representing battle event
			else
				map[x + i][y + j] = temp;
		}
}

// Input: a dynamic 2D int array map, point location of player
// Return: void
// Function: generate a 7 x 5 empty battle field surrounded by 9 x 7 wall centered at player's location
void battlefield_generator(int **map, Point location)
{
	int x = location.x - 4;						// x and y origin of 9 x 7 wall around battlefield
	int y = location.y - 3;

	for (int i = x; i < x + BATTLEFIELD_WIDTH + 4; i++)		// generate wall at 9 x 7 grid centered player's location;
		for (int j = y; j < y + BATTLEFIELD_WIDTH + 2; j++)
		{
			if ( i == x || i == x + BATTLEFIELD_WIDTH + 3 || j == y || j == y + BATTLEFIELD_WIDTH + 1 )
				map[i][j] = 999;			// generate walls
			else
				map[i][j] = 0;				// clear other buildings and events in battlefield
		}
}

// Input: a dynamic 1D Monster array storing monster, size of array, int of increase in size
// Return: void
// Function: extend the monster array by increase_size and update the size
void extend_array(Monster* &array, int &size, int increase_size)
{
	Monster *new_array = new Monster [size + increase_size];	// decalre a new dynamic array

	for (int i = 0; i < size; i++)
		new_array[i] = array[i];				// copy content of original array to new array

	size += increase_size;						// record the increased size

	delete[] array;							// release the memory allocated to original array

	array = new_array;						// point array to new array
}

// Input: a monster, a 2D dynamic int array map, a point location of player
// Return: void
// Function: to allocate location for a monster within the empty grid of battlefield randomly and label the monster on the map
void monster_allocation(Monster &monster, int** map, Point player_location)
{
	int x = player_location.x - 3;					// x and y origin of 7 x 5 battlefield (34 grid available for allocation
	int y = player_location.y - 2;

	int randint = rand() % 24;					// randint [0,23] -> position will be allocated in loop (int) randint
	int loop = 0;
	bool hold = true;

	for (int i = 0; i < BATTLEFIELD_WIDTH + 2 && hold; i++)		// iterate through all available locations
	{
		for (int j = 0; j < BATTLEFIELD_WIDTH && hold ; j++)	// v find available location
		{
			if ( (x + i != player_location.x) && (y + j != player_location.y) && (map[x + i][y + j] == 0) )
			{
				if ( loop >= randint )			// when loop no. greater than randint, allocate location
				{
					monster.location.set(x + i, y + j);
					map[monster.location.x][monster.location.y] = (monster.hp.quantity + 100);
					hold = false;
				}
			}
			loop++;
		}
	}
}

// Input: a dynamic 1D monster array monsters, number of monster in array, a dynamic 2D int array map, a point location of player
// Return: void
// Function: generate random number [1,10] of monster and initiate them(i.e. set their hp, atk, location)
void monster_generator(Monster* &monsters, int &monster_num, int** &map, Point location)
{
	for (int i = 0; i < 10; i++)					// generate multiple monsters
	{
		monsters[i].hp.quantity = rand() % 70 + 30;		// hp of monster should between [30,99]
		monsters[i].attack = rand() % 31 + 10;			// ATK of monster should between [10,40]
		monster_allocation(monsters[i], map, location);		// allocate location of monster on map

		if ( rand() % 100 < 45 || i == 9)			// chance of generating one more monster decrease exponentially
			break;

		extend_array(monsters, monster_num, 1);			// if available, extend the monster array by 1
	}
}

// Input: two point type
// Return: a double show distance between 2 point
// Function: calc distance between 2 point
double distance_between(Point point_1, Point point_2)
{
	return sqrt( pow(point_1.x - point_2.x, 2) + pow(point_1.y - point_2.y, 2) );
}

// Input: a move command, a monster type, a point location of player, a 2D dynamic int array map
// Return: bool type indicating whether the moving is valid or not
// Function: move the monster while re-lable them on the map and indicate the validity of the movment
bool monster_moved(char command, Monster &monster, Point player, int** map)
{
	int x = 0, y = 0;
	int mx = monster.location.x, my = monster.location.y;

	switch ( command )
	{
		case 'w':
			y += 1;
			break;
		case 's':
			y -= 1;
			break;
		case 'a':
			x -= 1;
			break;
		case 'd':
			x += 1;
			break;
	}

	switch ( map[mx+x][my+y] < 100 && ( mx + x != player.x || my + y != player.y) )
	{
		case true:
			map[monster.location.x][monster.location.y] = 0;				// label the original location on map as empty
			monster.location.change(x,y);							// change monster's location
			map[monster.location.x][monster.location.y] = (100 + monster.hp.quantity);	// label the new location as monster's hp
			return true;
		case false:
			return false;
	}
}

// Input; a monter, the profle of player, a point location of player
// Return: attack the monster has made on the player
// Function: allow monster to make damage on player's hp
int monster_attack(Monster monster, Profile &player, Point player_location)
{
	double distance = distance_between(monster.location, player_location);			// calc distance between monster and player
	int atk = (int) ( monster.attack / pow(distance, 2) );					// calc valid attack by formula
	atk *= (rand() % 125 + 75 ) / 100.0;

	if ( atk != 0 )
	{
		player.hp.change( -atk );							// modify player's hp
		return atk;
	}
	else
		return 0;
}

// Input: a monster profile, and the location of player
// Return: a char that symbolize behavior of monster (command)
// Function: search for the path to approch player
char chase_player(Monster monster, Point player)
{
	double distance = distance_between(monster.location, player);

	Point temp = monster.location;
	temp.change(0,1);
	if ( distance_between(temp, player) < distance )
		return 'w';
	
	temp = monster.location;
	temp.change(-1,0);
	if ( distance_between(temp, player) < distance )
		return 'a';

	temp = monster.location;
	temp.change(0,-1);
	if ( distance_between(temp, player) < distance )
		return 's';

	temp = monster.location;
	temp.change(1,0);
	if ( distance_between(temp, player) < distance )
		return 'd';

	return 'k';
}

bool victory(Monster * monsters, int monster_num)
{
	int dead_monster = 0;

	for (int i = 0; i < monster_num; i++)
	{
		if ( monsters[i].hp.quantity == 0)
		{
			dead_monster++;
		}
	}

	return dead_monster == monster_num;
}

int generate_trophy(int monster_num)
{
	int trophy = monster_num;

	for (int i = 0; i < monster_num; i++)
	{
		if ( (rand() % 100) > (33 + pow(monster_num, 3)) )
			break;
		else
			trophy++;
	}
	
	return trophy;
}


// Input: a profile of player, a dynamic 2D array map, a poitn location of player
// Return: void
// Function: to refresh, print status interface and map interface.
void default_page_battle(Profile player, int **map, Point location)
{
	refresh(100);
	status_interface(player);
	map_interface(map, location);
}

// Input: round number
// Return: void
// Function: show the instruction page of command and current round to user
void default_text_battle(int round)
{
	string lines[3];

	lines[0] = format_grids(" Command list:", "", "", " Your round: " + itoa(round + 1, 'u') + "/2" );
	lines[1] = format_grids(" Move: W A S D", "", " Attack: K", "");
	lines[2] = format_grids(" Bag: B", "", " Escape: E", "");

	text_interface( format_lines( lines[0], lines[1], lines[2]) );
}

// Input: profile of player, a dynamic 2D int array map, a point location of player
// Return: void
// Function: provide battle interface to user and integrate all the battle-related functions
void battle(Profile & player, int** map, Point & location)
{
	Point original_location = location;				// memory the original location

	int **temp_map = new int *[BATTLEFIELD_WIDTH + 4];		// declare a dynamic 2D array temp map to store map covered by battlefield
	for (int i = 0; i < BATTLEFIELD_WIDTH + 4; i++)
		temp_map[i] = new int [BATTLEFIELD_WIDTH + 2];

	battlefield_memory(map, original_location, temp_map);		// copy the buildings and events in main map to temp map
	battlefield_generator(map, original_location);			// generate battle field which cover the main map

	int monster_num = 1;						// number of monsters
	Monster *monsters = new Monster [monster_num];			// declare a dynamic array to store data of monsters
	monster_generator(monsters, monster_num, map, location);	// set number and attributes of monsters and store them in monster array

	int round = 0;
	bool escaped = false;
	char command;
	string lines[3];

	lines[0] = " You have encountered with Monsters !";
	lines[1] = " Game has been saved.";
	lines[2] = ENTER;

	while ( command != '\n' )
	{
		refresh(100);
		status_interface(player);
		logo_interface_fight();
		text_interface( format_lines(lines[0], lines[1], lines[2]) );
		command = input();
	}

	lines[0].clear();
	lines[1].clear();
	lines[2].clear();
 
	while (true)
	{
		if ( victory(monsters, monster_num) )
		{
			int trophy = generate_trophy(monster_num);
			player.item[2] += trophy;

			lines[0] = " You have killed " + itoa(monster_num,'u') + " monsters, and get meat x " + itoa(trophy,'u') + ".";
			lines[1] = " Now, you know where the meat comes from.";
			lines[2] = " The meat taste delicious right? They were once a man......";
	
			refresh(100);
			status_interface(player);
			logo_interface_win();
			text_interface(format_lines(lines[0], lines[1], lines[2]));
			input();

			break;
		}
		else if ( game_over(player) )
		{
			lines[0] = " Your HP drops to 0.";
			lines[1] = " Game over.";
			lines[2] = ANY_KEY;
			
			refresh(100);
			status_interface(player);
			logo_interface_loss();
			text_interface(format_lines(lines[0], lines[1], lines[2]));
			input();

			break;
		}
		else if ( escaped )
		{
			refresh(100);
			default_page_battle(player, map, location);
			text_interface(format_lines(lines[0], lines[1], lines[2]));
			input();

			break;
		}
		else if ( lines[0].empty() && lines[1].empty() && lines[2].empty() && round < 2)
		{
			refresh(100);
			default_page_battle(player, map, location);
			default_text_battle(round);
			command = input();
		}
		else if ( ! lines[0].empty() || ! lines[1].empty() || ! lines[2].empty() )
		{
			refresh(100);
			default_page_battle(player, map, location);
			text_interface(format_lines(lines[0], lines[1], lines[2]));
			input();
			command = '\0';
		}
		else
		{
			command = '\0';
		}
		
		{
			lines[0].clear();
			lines[1].clear();
			lines[2].clear();
		}

		switch ( command )
		{
			case 'w': case 'a': case 's': case 'd':
			{
				if ( player.sp.quantity == 0 )
				{
					lines[0] = " Yours SP become 0.";
					lines[1] = " Please use items to recover SP.";
					lines[2] = ANY_KEY;
				}
				else if ( ! moved(player, map, location, command) )
				{
					lines[0] = " Invalid move";
					lines[1] = " Please move in another direction.";
					lines[2] = ANY_KEY;
				}
				else
				{
					round++;

					status_after_move(player);
					lines[0] = " You have moved 1 grid.";
					lines[1] = ANY_KEY;
				}
				break;
			}
			case 'b':
			{
				if ( bag_manipulation(player, 'b') )
				{
					round++;
				}
				break;
			}
			case 'e':
			{
				round++;

				if ( (rand() % 100 > 50 ) )
				{
					escaped = true;
					lines[0] = " Escape suceed !";
					lines[1] = ANY_KEY;
				}
				else
				{
					lines[0] = " Escape failed !";
					lines[1] = ANY_KEY;
				}
				break;
			}
			case 'k':
			{
				round++;

				int valid_attack = 0;							// no. of non-zero attack on monster

				for (int i = 0; i < monster_num; i++)					// iterate through monster
				{
					int atk = (int)  player.attack / pow(distance_between(location, monsters[i].location), 2);
					atk *= (rand() % 125 + 75 ) / 100.0;

					if ( monsters[i].hp.quantity > 0 && atk > 0 )			// check valid attack
					{
						// original hp of monster
						string original_hp = itoa(monsters[i].hp.quantity, 'u');

						// calc the relative location of monster
						int x = monsters[i].location.x  - (original_location.x - 3) + 1;
						int y = monsters[i].location.y  - (original_location.y - 2) + 1;
						string relative_location = "[" + itoa(x,'u') + "," + itoa(y,'u') + "]";

						// refresh the status and symbol of monster on map
						monsters[i].hp.change(-atk);

						// update the map
						if ( monsters[i].hp.quantity == 0 )
							map[monsters[i].location.x][monsters[i].location.y] = 0;
						else
							map[monsters[i].location.x][monsters[i].location.y] = monsters[i].hp.quantity + 100;
					
						string final_hp = itoa(monsters[i].hp.quantity, 'u');

						lines[0] = " You have made " + itoa(atk, 'u') + " unit of damage on monster " + itoa(i+1, 'u');
						lines[0] += " at " + relative_location;
						lines[1]  = " The Health Point of monster drops from " + original_hp + " to " + final_hp + ".";
						lines[2]  = ANY_KEY;

						refresh(100);
						default_page_battle(player, map, location);
						text_interface( format_lines(lines[0], lines[1], lines[2]) );
						input();
	
						valid_attack++;
					}
				}
				if ( ! valid_attack )
				{
					lines[0] = " You are too far waya from enemy.";
					lines[1] = " All attack failed.";
					lines[2] = ANY_KEY;
				}				
				else
				{
					lines[0].clear();
					lines[1].clear();
					lines[2].clear();
				}
				break;
			}
		}

		if (round == 2)
		{
			round++;
			continue;
		}

		if ( round == 3)
		{
			for (int i = 0; i < monster_num; i++)
			{
				for (int j = 0; j < 2 && monsters[i].hp.quantity > 0; j++)
				{
					if (player.hp.quantity == 0)
						break;

					int x = monsters[i].location.x  - (original_location.x - 3) + 1;
					int y = monsters[i].location.y  - (original_location.y - 2) + 1;
					string relative_location = "[" + itoa(x,'u') + "," + itoa(y,'u') + "]";

					string column[4];
					column[0] = " Monster: " + itoa(i + 1, 'u');
					column[1] = " ATK: " + itoa(monsters[i].attack, 'u');
					column[2] = " Location: " + relative_location;
					column[3] = "    Round: (" + itoa(j+1, 'u') + "/2)";

					lines[0] = format_grids(column[0], column[1], column[2], column[3]);

					char command = '\0';

					{
						if ( distance_between(monsters[i].location, location) > 2 )
						{
							command = chase_player(monsters[i], location);
						}
						else if ( rand() % 3 > 1 )
						{
							command = chase_player(monsters[i], location);
						}
						else
						{
							command = 'k';
						}
						if ( ! monster_moved(command, monsters[i], location, map) )
						{
							command = 'k';
						}
					}

					switch ( command )
					{
						case 'w': case 'a': case 's': case 'd':
						{
							int x_1 = monsters[i].location.x  - (original_location.x - 3) + 1;
							int y_1 = monsters[i].location.y  - (original_location.y - 2) + 1;
							string relative_location_1 = "[" + itoa(x_1,'u') + "," + itoa(y_1,'u') + "]";

							lines[1] = " Moved form " + relative_location + " to " + relative_location_1 + ".";
							lines[2] = ANY_KEY;

							default_page_battle(player, map, location);
							text_interface( format_lines(lines[0], lines[1], lines[2]) );
							input();
							break;
						}

						case 'k':
						{
							int damage_on_player = monster_attack(monsters[i], player, location);

							lines[1] = " Make " + itoa(damage_on_player,'u') + " point of damage on you.";
							lines[2] = ANY_KEY;

							default_page_battle(player, map, location);
							text_interface( format_lines(lines[0], lines[1], lines[2]) );
							input();
							break;
						}
					}
				}
			}
			lines[0].clear(); 
			lines[1].clear(); 
			lines[2].clear();
		}
		round %= 3;
	}

	battlefield_recovery(map, original_location, temp_map);		// recover the buildings and events of map after finishing battle

	for (int i = 0; i < BATTLEFIELD_WIDTH + 2; i++)			// release the memory occupied by the temp map
		delete[] temp_map[i];
	delete[] temp_map;

	delete[] monsters;						// release the memory allocated to monsters
}
