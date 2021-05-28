// File name: explore.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold functions regarding explore (i.e. map, move, bag).

#include "explore.h"					// include self defined structures, external library, and function header of explore.cpp
#include "interface.h"					// include function header in interface.h

// items can be found during explore
// define items and their attribute
const Item unknown_potion = {"Unknown Potion", "HP", "+50", "Hr", "+100", "It sounds magic right? But it is science!!!"};
const Item bondage = { "Bondage", "HP", "+30", "", "", "Become a mummy or corpse? Well you have made your choice."};
const Item meat = {"Meat", "HP", "+20", "Hr", "-50", "Want some black pepper? You think too much boy, this is Waste Land!"};
const Item radiated_meat = {"Radiated Meat", "Hr", "-50", "HP", "-20", "Aha, you feel like superman."};
const Item radiated_cake = {"Radiated Cake", "Hr", "-30", "HP", "-15", "Why not eat cake bro?"};
const Item pure_water = {"Pure Water", "Hr", "-10", "", "", "You feel full after drinking it. How melancholy."};
const Item adrenaline = {"Adrenaline", "SP", "+100", "", "", "Fight or Fligh? You decide it."};
const Item radiated_water = {"Radiated Water", "SP", "+30", "HP", "-10", "You feel like superman! But your body don't think so."};
const Item iodophor = {"Iodophor", "SP", "+20", "", "", "Woo hoo, radiation-free!"};

// arrange items in an array
Item items[9] = {unknown_potion, bondage, meat, radiated_meat, radiated_cake, pure_water, adrenaline, radiated_water, iodophor};

void event_allocator(int & event, const double & prosperity, const bool & resource_only)
{
	short randint = (rand() % 1001) / prosperity;

	if ( randint > 100 )
		event = 0;
	else if ( randint > 50 )
		event = 1;
	else if ( randint > 30 )
		event = 2;
	else if ( randint > 20 )
		event = 3;
	else if ( randint > 10 )
		event = 4;
	else
		event = 5;

	if ( ! resource_only )
	{
		randint = (rand() % 1001) / prosperity;

		if ( randint > 300 )
			return;
		else if ( randint > 10 )
			event = 10;
		else
			event = 11;
	}
}

// Input: A int dynamic 2D array map, the side length of the map.
// Return: Void.
// Function: randomly allocate buildings, monsters, and events on the map by changing the value of array(map) element and set obstacle in boundary.
// Meaning: Make the game more fun with random element and prevent bug.
void map_generator(int ** map, int  map_len)
{
	int min = 0, max = map_len - 1;

	srand(time(NULL));					// set the random seed to be "random"

	for (int i = 0; i < map_len; i++)
	{
		for (int j = 0; j < map_len; j++)		// iterate through all element of map
		{
			if ( i <= min + 10 || i >= max - 10 || j <= min + 10 || j >= max - 10 )
			{
				map[i][j] = 999;		// set the boundary part to be wall(999)
			}
			else if ( i <= min + 15 || i >= max - 15 || j <= min + 15 || j >= max - 15 )
			{
				event_allocator(map[i][j], 1, 1);
			}
			else
			{
				event_allocator(map[i][j], 1, 0);
			}
		}
	}
			
}

// Input: a dynamic 2D array map, side length of the map, actual location of player.
// Return: void
// Function: extend the map by 4 times and shift the actual location of player into center of new map while keeping the buildings in orginal map.
// Meaning: Reduce the occupation of memory when it is no necessary.
void extend_map(int** & map, int & map_len, Point& location)
{
	int new_len = map_len * 2;					// side length of new map

	int **new_map = new int *[new_len];				// declare a new 2D dynamic array map with doubled side length
	for (int row = 0; row < new_len; row++)
		new_map[row] = new int [new_len];

	map_generator(new_map, new_len);				// initialize the new map with random buildings,monsters, and events

	int x_diff = map_len - (location.x + 1);
	int y_diff = map_len - (location.y + 1);			// shifting distance on x,y axis of original map on new map

	location.set(x_diff + location.x, y_diff + location.y);		// shift actual location of player
	new_map[location.x][location.y] = 0;				// label the area to be safe

	for (int i = 0; i < map_len; i++)				// shift all element of original map to new map according to above rules
		for (int j = 0; j < map_len; j++)
			if ( (i + x_diff) < new_len && (j + y_diff) < new_len )
				if (map[i][j] != 999 && new_map[i + x_diff][j + y_diff] != 999)
					new_map[i + x_diff][j + y_diff] = map[i][j];

	for (int i = 0; i < map_len; i++)				// release the origal map
		delete[] map[i];
	delete[] map;

	map = new_map;							// copy the new map to original map
	map_len = new_len;						// update the length to new length
}

// Input: a dynamic 2D array map, int x and y that symbolize the current coordinate on map
// Return: void
// Function: develop a maze within the pre-processed map.
void maze_generator(int** map, int x, int y)
{
	vector<char> direction{'w','a','s','d'};				// vectors containing path-developing direction
	random_shuffle( direction.begin(), direction.end() );			// set random conbination for the direction

	const int wall = 998;
	const int node = -1;
	const int path = 0;

	int grid = path;

	event_allocator(grid, 4, 1);

	for (int i = 0; i < 4; i++)							// iterate through the directions
	{
		switch ( direction[i] )							// develop the route to top
		{
			case 'w':
				if ( map[x][y+1] == wall && map[x][y+2] == node )	// check whether there is a wall and node that not been modified
				{							// in this direction
					map[x][y+1] = grid;				// set route 
					map[x][y+2] = grid;
					maze_generator(map, x, y+2);			// keep generating route at the next node
				}
				break;

			case 'a':
				if ( map[x-1][y] == wall && map[x-2][y] == node )
				{
					map[x-1][y] = grid;
					map[x-2][y] = grid;
					maze_generator(map, x-2, y);
				}
				break;

			case 's':
				if ( map[x][y-1] == wall && map[x][y-2] == node )
				{
					map[x][y-1] = grid;
					map[x][y-2] = grid;
					maze_generator(map, x, y-2);
				}
				break;

			case 'd':
				if ( map[x+1][y] == wall && map[x+2][y] == node )
				{
					map[x+1][y] = grid;
					map[x+2][y] = grid;
					maze_generator(map, x+2, y);
				}
				break;
		}
	}
	return;									// stop the function after processing all four direction
}

// Input: a dynamic 2D array map, the location of player
// Return: void
// Function: generate random maze on map by breaking wall between nodes
void maze(int** map, Point location)
{
	const int size = 15 * 2 + 1;
	const int x_origin = location.x - size / 2;				// the origin of maze
	const int y_origin = location.y - size / 2;				// centered the player

	const int wall = 998;
	const int node = -1;
	const int path = 0;

	for (int i = 0; i < size; i++)						// iterate through maze grids on map and set walls and nodes
	{
		for (int j = 0; j < size; j++)					// that is, pre-process the map
		{
			if ( i % 2 == 0 )
				map[x_origin + i][y_origin + j] = wall;		// set walls that surrounding nodes
			else if ( j % 2 == 0 )
				map[x_origin + i][y_origin + j] = wall;		// set walls that surrounding nodes
			else
				map[x_origin + i][y_origin + j] = node;		// set nodes
		}
	}

	srand(time(NULL));							// set the random seed for generating random maze
	maze_generator(map, x_origin + 1, y_origin + 1);			// generate paths by breaking walls between nodes

	map[x_origin][y_origin + 1] = path;					// set a oping in bottom-left corner of maze
	map[x_origin + size - 1][y_origin + size - 2] = path;			// set a opening in top-right corner of maze
}

// Input: Profile of player, a dynamic 2D array map, location of player, command from keyboard.
// Return: If success to move, return true, else, return false.
// Function: determine whether the movement is valid, if yes, change the virtual location(story dependent) and actual location(map dependent).
// Meaning: Allow movement of player and set the condition of movement.
bool moved(Profile & player, int ** map, Point & location, char direction)
{
	int x = 0, y = 0;					// movement in x and y direction.

	if ( direction == 'w' )					// with different command, move in different direction.
		y += 1;
	else if ( direction == 's' )
		y -= 1;
	else if ( direction == 'a' )
		x -= 1;
	else if ( direction == 'd' )
		x += 1;
	
	if ( map[location.x + x][location.y + y]  >= 100 )	// check whether there is a obstacle
		return false;					// indicate failed movement
	else
	{
		player.location.change(x,y);			// change the virtual location
		location.change(x,y);				// change the actual location
		return true;					// indicate sucessful movement
	}
}

// Input: Profile of player.
// Return: void.
// Function: refresh the interface and print the status interface and bag interface.
// Meaning: For better modularization.
void default_page_b(Profile player)
{
	refresh(100);						// refresh the interface
	status_interface(player);				// print status interface
	bag_interface(items, player.item);			// print bag interface
}

// Input: void
// Return: void
// Function: print the text interface with some default text, which is the command instruction.
// Meaning: better modularization
void default_text_b(void)
{
	string line_1 = " Command list:";
	string line_2 = " Use item: 0 - 8";
	string line_3 = " Back: b";
	text_interface( format_lines(line_1, line_2, line_3) );	// format the output text in text interface separate into 3 line and keep left.
}

// Input: Profile of player, type of effect of item, value of effect of item.
// Return: void.
// Function: modify player's status according to attribute of item.
// Meaning: better modularization.
void buff(Profile& player, string type, int value)
{
	if ( type == "HP" )
		player.hp.change(value);			// change hp
	else if ( type == "SP" )
		player.sp.change(value);			// change sp
	else if ( type == "Hr" )
		player.hr.change(value);			// change hr
}

// Input: Profile of player, mode of game(explore/battle).
// Return: void.
// Function: provide a interface to show no. and effect and quantity of items, to allow player to consume items to modify their status.
// Meaning: increase elements that is fun, as there is often positive and negative effect on same item. User have to evaluate it.
bool bag_manipulation(Profile& player, char mode)
{
	default_page_b(player);					// print status and bag interface
	default_text_b();					// print command instruction

	bool use_a_item = false;				// record the item is used

	while (true)
	{
		char command = input();				// receive input char as command
		string temp1 = "", temp2 = "", temp3 = "";	// 3 lines ready for output in text interface

		if ( command == 'b' )				// quit the bag interface and return to the map interface
			break;

		else if ( command >= '0' && command <= '8' )	// use items numbered 0 to 8.
		{
			int index = (int) command - '0';	// convert the input char into int

			if (player.item[index] > 0)		// check the quantity of item
			{
				buff( player, items[index].type_1, atoi(items[index].effect_1.c_str()) );	// modify status base on effect 1
	
				if ( items[index].type_2 != "" && items[index].effect_2 != "" )			// modify status base on efefct 2
					buff(player, items[index].type_2, atoi(items[index].effect_2.c_str()) );

				temp1 = " " + items[index].name + " is used.";					// show the thing has been used
				temp2 = " " + items[index].annotation;						// show the annotation of developer

				player.item[index] -= 1;	// decrease the quantity of item by 1.

				if ( mode != 'e' )		// if not in exploration mode, teminate the page.(allow 1 act only).
				{
					use_a_item = true;
				}
			}
			else					// if quantity is 0, notice the user.
			{
				temp1 = " You don't have this item.";
				temp2 = " Press ENTER to continue.";
			}
		}

		default_page_b(player);				// show default page of bag interface

		if ( temp1 != "" || temp2 != "" || temp3 != "" )
		{
			text_interface(format_lines(temp1, temp2, temp3));
		}
		else						// show command instruction.
		{
			default_text_b();
		}

		if ( use_a_item )				// in battle mode, only usage of one item is allowed
		{
			input();
			break;					// terminate program if one item is used
		}
	}
	return use_a_item;					// indicate whether a item is used
}

void detect(Profile player, int ** map, Point location)
{
	string lines[3];
	int monster = 0;

	for (int i = location.x - 1; i <= location.x + 1; i++)
		for (int j = location.y - 1; j <= location.y + 1; j++)
			if ( map[i][j] == 10 || map[i][j] == 99)
			{
				monster++;
				map[i][j] = 99;
			}

	lines[0] = " There are " + itoa(monster, 'u') + " monster is found around 3 x 3 grids.";
	lines[1] = " Safe area has been labelled.";
	lines[2] = " Press ENTER to continue.";

	refresh(100);
	status_interface(player);
	map_interface(map, location);
	text_interface( format_lines( lines[0], lines[1], lines[2]) );
	input();
}

	

