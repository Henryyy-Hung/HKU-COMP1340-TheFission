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
	bool indicator = true;

	for (int i = 0; i < BATTLEFIELD_WIDTH + 2; i++)			// iterate through all available locations
	{
		for (int j = 0; j < BATTLEFIELD_WIDTH; j++)		// v find available location
		{
			if ( (x + i != player_location.x) && (y + j != player_location.y) && (map[x + i][y + j] == 0) )
			{
				if ( loop >= randint )			// when loop no. greater than randint, allocate location
				{
					monster.location.set(x + i, y + j);
					map[monster.location.x][monster.location.y] = (monster.hp.quantity + 100);
					indicator = false;
				}
			}
			loop++;

			if ( ! indicator )				// break when allocated
				break;
		}
		if ( ! indicator )					// break when allocated
			break;
	}
}

// Input: a dynamic 1D monster array monsters, number of monster in array, a dynamic 2D int array map, a point location of player
// Return: void
// Function: generate random number [1,10] of monster and initiate them(i.e. set their hp, atk, location)
void monster_generator(Monster* &monsters, int &monster_num, int** &map, Point location)
{
	for (int i = 0; i < 10; i++)					// generate multiple monsters
	{
		srand(time(NULL)+i);

		monsters[i].hp.quantity = rand() % 70 + 30;		// hp of monster should between [30,99]
		monsters[i].attack = rand() % 31 + 10;			// ATK of monster should between [10,40]
		monster_allocation(monsters[i], map, location);		// allocate location of monster on map

		int randint = rand() % 100;
		if ( randint < 45 )					// chance of generating one more monster decrease exponentially
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
	int x = 0, y = 0;					// movement in x and y direction.

	if ( command == 'w' )					// with different command, move in different direction.
		y += 1;
	else if ( command == 's' )
		y -= 1;
	else if ( command == 'a' )
		x -= 1;
	else if ( command == 'd' )
		x += 1;

	// check whether it is a valid move, if not, return false
	if ( map[monster.location.x + x][monster.location.y + y] > 100 || ( monster.location.x + x == player.x && monster.location.y + y == player.y) )
		return false;
	else
	{
		map[monster.location.x][monster.location.y] = 0;				// label the original location on map as empty
		monster.location.change(x,y);							// change monster's location
		map[monster.location.x][monster.location.y] = (100 + monster.hp.quantity);	// label the new location as monster's hp
		return true;
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
	string line_1 = format_grids(" Command list:", "", "", " Your round: " + itoa(round + 1, 'u') + "/2" );
	string line_2 = format_grids(" Move: W A S D", "", " Attack: K", "");
	string line_3 = format_grids(" Bag: B", "", " Escape: E", "");
	text_interface( format_lines( line_1, line_2, line_3) );
}

// Input: profile of player, a dynamic 2D int array map, a point location of player
// Return: void
// Function: provide battle interface to user and integrate all the battle-related functions
void battle(Profile& player, int** map, Point& location)
{
	Point original_location = location;				// memory the original location
	Point origin = {location.x - 4, location.y - 3};		// memory the origin of the map

	int **temp_map = new int *[BATTLEFIELD_WIDTH + 4];		// declare a dynamic 2D array temp map to store map covered by battlefield
	for (int i = 0; i < BATTLEFIELD_WIDTH + 4; i++)
		temp_map[i] = new int [BATTLEFIELD_WIDTH + 2];

	battlefield_memory(map, original_location, temp_map);		// copy the buildings and events in main map to temp map
	battlefield_generator(map, original_location);			// generate battle field which cover the main map

	int monster_num = 1;						// number of monsters
	Monster *monsters = new Monster [monster_num];			// declare a dynamic array to store data of monsters
	monster_generator(monsters, monster_num, map, location);	// set number and attributes of monsters and store them in monster array

	refresh(100);							// show the logo "fight" to notice player he encounter with a battle
	status_interface(player);
	logo_interface_fight();
	text_interface( format_lines(" You encountered with MONSTERS !!!!!", " Press ENTER to continue.", "") );
	input();

	int round = 0;							// round of player

	default_page_battle(player, map, location);			// allow player to put first command
	default_text_battle(round);
	char command = input();

	while (true)
	{
		if ( command == 'w' || command == 'a' || command == 's' || command == 'd' )		// movement that trigger out events
		{
			if ( player.sp.quantity != 0 && moved(player, map, location, command) )		// check validity of move and move
			{
				status_after_move(player);						// update player's status

				refresh(100);								// update interface to show notification
				default_page_battle(player, map, location);
				text_interface(format_lines(" You have moved 1 grid.", " Press Enter to continue", ""));
				input();

				round++;								// increase round number
			}
			else if ( player.sp.quantity == 0 )
			{
				refresh(100);								// update interface to show notification
				default_page_battle(player, map, location);
				text_interface( format_lines( " Your stamina point is used up.", " Press ENTER to make another command", "") );
				input();
			}
			else
			{
				refresh(100);								// update interface to show notification
				default_page_battle(player, map, location);
				text_interface( format_lines( " Invalid move.", " Press ENTER to make another command.","") );
				input();
			}
		}

		else if ( command == 'b' )							// using of item
		{
			if ( bag_manipulation(player, 'b') == true )				// enter bag page with battle mode (use one items only)
				round++;
		}

		else if ( command == 'e' )							// try to escape
		{
			srand(time(NULL)+round);
			int chance = rand() % 100;
			int rate = 50 + pow(monster_num, 1.4);
			if ( chance < rate )							// 50 % chance to escape
			{
				refresh(100);							// notice the user escape success
				default_page_battle(player, map, location);
				text_interface(format_lines(" Escape succeed !", " Press Enter to continue", ""));
				input();
				break;

			}
			else
			{
				refresh(100);							// notice the user escape failed
				default_page_battle(player, map, location);
				text_interface(format_lines(" Escape failed !", " Press Enter to continue", ""));
				input();

				round++;							// increase round number
			}
		}
		else if (command == 'k' )							// user try to attack
		{
			int valid_attack = 0;							// no. of non-zero attack on monster

			for (int i = 0; i < monster_num; i++)					// iterate through monster
			{
				int atk = (int)  player.attack / pow(distance_between(location, monsters[i].location), 2);
				atk *= (rand() % 125 + 75 ) / 100.0;

				if ( monsters[i].hp.quantity > 0 && atk > 0 )			// check valid attack
				{
					// hp of monster before attack
					string original_hp = itoa(monsters[i].hp.quantity, 'u');

					// refresh the status and symbol of monster on map
					monsters[i].hp.change(-atk);

					// update the map
					if ( monsters[i].hp.quantity == 0 )
						map[monsters[i].location.x][monsters[i].location.y] = 0;
					else
						map[monsters[i].location.x][monsters[i].location.y] = monsters[i].hp.quantity + 100;
					
					// calc the relative location of monster to give user a concept which monster he is attacking
					int x = monsters[i].location.x  - (original_location.x - 3) + 1;
					int y = monsters[i].location.y  - (original_location.y - 2) + 1;
					string relative_location = "[" + itoa(x,'u') + "," + itoa(y,'u') + "]";

					// hp of monster after attack
					string monster_hp = itoa(monsters[i].hp.quantity, 'u');

					// notice user he has made an valid attack, with the numeric values
					default_page_battle(player, map, location);
					string line_1 = " You have made " + itoa(atk, 'u') + " unit of damage on monster " + itoa(i+1, 'u') + " at ";
					line_1 += relative_location;
					string line_2 = " The Health Point of monster drops from " + original_hp + " to " + monster_hp + ".";
					string line_3 = " Press ENTER to continue.";
					text_interface( format_lines(line_1, line_2, line_3) );
					input();

					valid_attack++;
				}
			}

			if ( valid_attack == 0 )
			{
				// notice user he has no made any valid attack
				default_page_battle(player, map, location);
				text_interface(" You are too far away from enemy, all attack failed.");
				input();
			}
			else
			{
				round++;					// increase round
			}
		}

		int dead_monster = 0;					// check the number of dead monster and update the map
		for (int i = 0; i < monster_num; i++)
		{
			if ( monsters[i].hp.quantity == 0)
			{
				dead_monster++;
			}
		}

		if (dead_monster == monster_num)			// check whether the player wins, if yes, calc the trophy for the player
		{
			int trophy = monster_num;			// chance of getting more trophy increase with number of monster
			for (int i = 0; i < monster_num; i++)
			{
				if ( (rand() % 100) > (33 + pow(monster_num, 3)) )
					break;
				else
					trophy++;
			}

			// prepare output strings
			string line_1 = " You have killed " + itoa(monster_num,'u') + " monsters, and get meat x " + itoa(trophy,'u') + ".";
			string line_2 = " Now, you know where the meat comes from.";
			string line_3 = " The meat taste delicious right? They were once a man......";

			player.item[2] += trophy;			// update user's item

			refresh(100);					// notice user he has win and show "win" logo
			status_interface(player);
			logo_interface_win();
			text_interface( format_lines(line_1, line_2, line_3) );
			input();
			break;
		}

		else if ( round != 0 && round % 2 == 0 )		// after player makes 2 action, is monster's round
		{
			for (int i = 0; i < monster_num; i++)
			{
				for (int j = 0; j < 2 && monsters[i].hp.quantity > 0; j++)
				{
					// check the status of player to decide whether continue the game
					if (player.hp.quantity == 0)
						break;

					// find the relative location of monster before any action is done
					int x = monsters[i].location.x  - (original_location.x - 3) + 1;
					int y = monsters[i].location.y  - (original_location.y - 2) + 1;
					string relative_location = "[" + itoa(x,'u') + "," + itoa(y,'u') + "]";

					// Provide basic information of monster
					string column_1 = " Monster: " + itoa(i + 1, 'u');
					string column_3 = " Location: " + relative_location;
					string column_2 = " ATK: " + itoa(monsters[i].attack, 'u');
					string column_4 = "    Round: (" + itoa(j+1, 'u') + "/2)";
					string line_1 = format_grids(column_1, column_2, column_3, column_4);

					char command = 'x';

					{
						// simple algorithm before AI is done
						// move toward user and then attack
						if ( distance_between(monsters[i].location, location) > 2 )
							command = chase_player(monsters[i], location);
						else if ( rand() % 3 > 1 )
							command = chase_player(monsters[i], location);
						else
							command = 'k';
						if ( ! monster_moved(command, monsters[i], location, map) )
							command = 'k';
					}


					// if monster attack
					if ( command == 'k' )
					{
						// make damage on player by function
						int damage_on_player = monster_attack(monsters[i], player, location);

						// notice user he is attacked with numerical values
						default_page_battle(player, map, location);
						string line_2 = " Make " + itoa(damage_on_player,'u') + " point of damage on you.";
						string line_3 = " Press ENTER to continue.";
						text_interface( format_lines(line_1, line_2, line_3) );
						input();
					}

					// if monster move
					else if ( command == 'w' || command == 'a' || command == 's' || command == 'd')
					{
						// find the relative location of monster after moving
						int x_1 = monsters[i].location.x  - (original_location.x - 3) + 1;
						int y_1 = monsters[i].location.y  - (original_location.y - 2) + 1;
						string relative_location_1 = "[" + itoa(x_1,'u') + "," + itoa(y_1,'u') + "]";

						string line_2 = " Moved form " + relative_location + " to " + relative_location_1 + ".";
						string line_3 = " Press ENTER to continue.";

						// notice user the monster moved
						default_page_battle(player, map, location);
						text_interface( format_lines(line_1, line_2, line_3) );
						input();
					}
				}
			}
		}

		if (player.hp.quantity == 0)				// check whether player is dead every round, if yes, terminate the game
			break;

		round %= 2;

		default_page_battle(player, map, location);		// show the default page to user
		default_text_battle(round);
		command = input();					// allow user to enter command
	}

	battlefield_recovery(map, original_location, temp_map);		// recover the buildings and events of map after finishing battle

	for (int i = 0; i < BATTLEFIELD_WIDTH + 2; i++)			// release the memory occupied by the temp map
		delete[] temp_map[i];
	delete[] temp_map;

	delete[] monsters;						// release the memory allocated to monsters
}
