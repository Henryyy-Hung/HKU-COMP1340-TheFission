// File name: interface.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold all functions regarding displaying the game content and facilitate modularization.

#include "interface.h"					// include self defined structures, external library, and function header of interface.cpp

#define HORIZONTAL "\xE2\x94\x81"			// components of bondary of text interface and status interface
#define VERTICAL "\xE2\x94\x83"
#define TOP_LEFT "\xE2\x94\x8F"
#define TOP_RIGHT "\xE2\x94\x93"
#define BOTTOM_LEFT "\xE2\x94\x97"
#define BOTTOM_RIGHT "\xE2\x94\x9B"

#define LIGHT_HORIZONTAL "\xE2\x94\x80"			// component of boundary of map interface
#define LIGHT_VERTICAL "\xE2\x94\x82"
#define ARC_TOP_LEFT "\xE2\x95\xAD"
#define ARC_TOP_RIGHT "\xE2\x95\xAE"
#define ARC_BOTTOM_LEFT "\xE2\x95\xB0"
#define ARC_BOTTOM_RIGHT "\xE2\x95\xAF"
#define CROSS "\xE2\x94\xBC"
#define VERTICAL_RIGHT "\xE2\x94\x9C"
#define VERTICAL_LEFT "\xE2\x94\xA4"
#define HORIZONTAL_DOWN "\xE2\x94\xAC"
#define HORIZONTAL_UP "\xE2\x94\xB4"

#define BLACK_SQUARE "\xE2\x96\xA0"			// components of status bar
#define WHITE_SQUARE "\xE2\x96\xA1"	

#define CHARACTOR 	"\xE2\x98\xBB"			// indicator of charactor
#define SHADE		"\xE2\x96\x91"			// indicator of boundary
#define BLOCK		"\xE2\x96\x91\xE2\x96\x91"
#define DANGER		"\xE2\x9C\x98"

const int Width = 70;					// Width of all interface
const int Length = Width - 2;				// Length of the output text
const int Height = 15;					// Height of the main interface (e.g. map & manual)

// Input: profile of player
// Return: void 
// Function: To visualize and display the current status (e.g. HP, SP, ATK) of player in a more intuitive and clear way (e.g. HP bar, status box)
// Meaning: To decrease the difficulty of understanding the game and make the complicated data more intuitive to user
void status_interface(Profile player)
{
	cout << TOP_LEFT;								// print the upper boundary
	for (int i = 0; i < Length; i++)
		cout << HORIZONTAL;
	cout << TOP_RIGHT << '\n';

	int w = (Length - 13) / 2;							// distance from the boundary

	cout << VERTICAL								// print left boundary
		<< setw(w) << ""
		<< "-Time: "
		<< right << setfill('0')						// set the format of time to be "00:00"
		<< setw(2) << player.time.hour						// print time
		<< ":"
		<< setw(2) << player.time.min
		<< "-"
		<< setfill(' ')								// set back the fill char to be ' '
		<< setw( w + ( (Length % 2 == 1)? 0:1 ) ) << ""				// adjust width according to Length	
		<< VERTICAL << '\n';							// print right boundary

	cout << setfill(' ') << right;

	cout << VERTICAL << " Health Point: ";						// print the left boundary and identifer of status
	int hp = (int) rint(player.hp.quantity / 10);					// no. of grid of "health point bar" ( by round off)
	for (int i = 0; i < hp; i++)							// print the remaining health point grid in a bar
		cout << BLACK_SQUARE;
	for (int i = 0; i < 10 - hp; i++)						// print the lost health point grid in a bar
		cout << WHITE_SQUARE;
	cout << " " 
		<< setw(3) << (int) player.hp.quantity << "%" 
		<< setw(Length - 61) << "";						// print percentage of remining health point and adjust width

	cout << "Stamina Point: ";							// same as above, but for stamina point
	int sp = (int) rint(player.sp.quantity / 10);
	for (int i = 0; i < sp; i++)
		cout << BLACK_SQUARE;
	for (int i = 0; i < 10 - sp; i++)
		cout << WHITE_SQUARE;
	cout << " "
		<< setw(3) << (int) player.sp.quantity << "%" 
		<< " " << VERTICAL << '\n';

	cout << VERTICAL << " Hunger Point: ";						// same as above, but for hunger point
	int hr = (int) rint(player.hr.quantity / 10);
	for (int i = 0; i < hr; i++)
		cout << BLACK_SQUARE;
	for (int i = 0; i < 10 - hr; i++)
		cout << WHITE_SQUARE;
	cout << " " 
		<< setw(3) << (int) player.hr.quantity << "%" 
		<< setw(Length - 61) << "";

	cout << "Attack  Point: "							// print the attack point in status interface
		<< left << setw( Length - 52 )
		<< player.attack
		<< VERTICAL << '\n';

	cout << BOTTOM_LEFT;								// print the lower boundary
	for (int i = 0; i < Length; i++)
		cout << HORIZONTAL;
	cout << BOTTOM_RIGHT << '\n';
}

bool is_english(string line)
{
	const int len = line.length();
	for (int i = 0; i < len; i++)
	{
		if ( (int) line[i] < 0 || (int) line[i] > 127)
			return false;
	}
	return true;
}

// Input: string sentence that want to be displayed in the "chatbox", which is text interface
// Return: void
// Function: To enclose the output text within a "text box" and seperate sentence into 3 lines without "breaking" any word, which is, use the last space in a line as separator of lines , to allocate long sentence into 3 lines. so as to boost the readability of text inside the text interface.
// Example: "Hello world" will be separate into "Hello" & "world", instead of "Hell" & "o world" when separating lines.
void text_interface(string sentence)
{
	string line_1, line_2, line_3;

	if ( is_english(sentence) )
	{
		sentence = format_string(sentence, Length * 3 + 3);
	
		int pos1, pos2, pos3;					// position of the space at the end of line, which will be line separator

		pos1 = sentence.rfind(" ", Length);			// find the position of line separator(space) 
		if (pos1 != -1)
			line_1 = sentence.substr(0, pos1);		// if found, allocate string before the separator(space) to line 1 of output
		else
			line_1 = "error";				// if the input sentence doesn't match with required format, output error

		pos2 = sentence.rfind(" ", pos1 + 1 + Length );		// same with above, but for line 2
		if (pos1 != -1 && pos2 != -1)
			line_2 = sentence.substr(pos1 + 1, pos2 - pos1 - 1);
		else
			line_2 = "error";
	
		pos3 = sentence.rfind(" ", pos2 + 1 + Length );		// same with above, but for line 3
		if (pos1 != -1 && pos2 != -1 && pos3 != -1)
			line_3 = sentence.substr(pos2 + 1, pos3 - pos2 - 1);
		else
			line_3 = "error";
	}
	else
	{
		int line_len = Length / 2 * 3;
		int len = sentence.length() / 3;

		for (int i = 0; i < sentence.length(); i++)
		{
			if ( sentence[i] >= 0 && sentence[i] <= 127 )
			{
				sentence.replace(i, 1, "　");
			}
		}

		for (int i = 0; i < Length * 3 / 2 - len; i++)
		{
			sentence += "　";
		}

		line_1 = sentence.substr(0, line_len);
		line_2 = sentence.substr(line_len, line_len);
		line_3 = sentence.substr(line_len * 2, line_len);
	}

	{
		cout << TOP_LEFT;					// print the upper boundary
		for (int i = 0; i < Length; i++)
			cout << HORIZONTAL;
		cout << TOP_RIGHT << '\n';

		cout << left;						// print output lines
		cout << VERTICAL << setw(Length) << line_1 << VERTICAL << '\n';	
		cout << VERTICAL << setw(Length) << line_2 << VERTICAL << '\n';
		cout << VERTICAL << setw(Length) << line_3 << VERTICAL << '\n';

		cout << BOTTOM_LEFT;					// print the lower boundary
		for (int i = 0; i < Length; i++)
				cout << HORIZONTAL;
		cout << BOTTOM_RIGHT << '\n';
	}
}

// Input: integer which representing symbol on the map
// Return: void
// Function: to print the integer into the symbol it represent on the map
// Meaning: a sub-function of map_interface(), to facilitate modularization
string map_convertor(const int & symbol)
{
	switch ( symbol )
	{
		case 0:						// empty grid's content
			return "  ";
		case 1:						// unknown building's content
			return "UB";
		case 2:						// lake's content
			return "WT";
		case 3:						//Hospital's content
			return "HP";
		case 4:						// Food shop's content
			return "FD";
		case 5:						// Weapon shop's content
			return "AT";
		case 99:					// DANGER sign
			return "\xE2\x9C\x98 ";
		case 998: case 999:				// wall
			return "\xE2\x96\x91\xE2\x96\x91";
		default:
			if ( symbol > 100 && symbol < 200 )	// monster
			{
				string output = itoa(symbol % 100, 'u');
				return ( output.length() == 2 ) ? output : " " + output;
			}
			else
			{
				return "  ";
			}
	}

}

// Input: the dynamic 2D int array of map, point of location of player
// Return: void
// Function: To print and visualize the map content in a more clear and intuitive manner (i.e. using of coordinate lines & convertion of map content)
// Meaning: increase the readability of map and make the game more user-friendly
void map_interface(int **map, Point location)
{
	//int x = location.x;							// x coordinate of the player		
	//int y = location.y;							// y coordinate of the player
	//int h_range = (Width - 1) / 3;					// no. of horizontal grids that will be printed
	//int v_range = (Height - 1) / 2;					// no. of vertical grids that will be printed
	//int east = x + (h_range - 1) / 2 - 1;					// max. x coordinate of the map that will be printed
	//int west = x - (h_range - 1) / 2 + 1;					// min. x coordinate of the map that will be printed
	//int north = y + (v_range - 1) / 2;					// max. y coordinate of the map that will be printed
	//int south = y - (v_range - 1) / 2;					// min. y coofdinate of the map that will be printed

	int east = location.x + 10;
	int west = location.x - 10;
	int north = location.y + 3;
	int south = location.y - 3;
	
	int idx = 0;
	static string lines[Height];

	if ( lines[idx].empty() )
	{
		lines[idx] = ARC_TOP_LEFT;
		for (int i = 0; i < Width - 8; i++)
		{
			if ( i % 3 == 2 )
				lines[idx] += HORIZONTAL_DOWN;
			else
				lines[idx] += LIGHT_HORIZONTAL;
		}
		lines[idx] += ARC_TOP_RIGHT;
	}
	idx++;

	for (int j = north; j >= south; j--)					// iterate the y coordinate of map from north to south
	{
		if ( j != north )						// print horizontal boundary between grids
		{
			if ( lines[idx].empty() )
			{
				lines[idx] = VERTICAL_RIGHT;
				for (int i = 0; i < Width - 8; i++)
				{
					if ( i % 3 == 2 )
						lines[idx] += CROSS;
					else
						lines[idx] += LIGHT_HORIZONTAL;
				}
				lines[idx] += VERTICAL_LEFT;
			}
			idx++;
		}

		lines[idx]= LIGHT_VERTICAL;
		for (int i = west; i <= east; i++)				// iterate the x coordinate of map from west to east
		{
			if ( i != location.x || j != location.y )
			{
				lines[idx] += map_convertor(map[i][j]);
			}
			else
			{
				lines[idx] += CHARACTOR;			// print user's location
				lines[idx] += " ";
			}
			lines[idx] += LIGHT_VERTICAL;				// print the right-most boundary
		}
		idx++;
	}

	if ( lines[idx].empty() )
	{
		lines[idx] = ARC_BOTTOM_LEFT;					// print the lower boundary
		for (int i = 0; i < Width - 8; i++)
		{
			if ( i % 3 == 2 )
				lines[idx] += HORIZONTAL_UP;
			else
				lines[idx] += LIGHT_HORIZONTAL;
		}
		lines[idx] += ARC_BOTTOM_RIGHT;
	}

	for (int i = 0; i < Height; i++)
	{
		cout << "   " << lines[i] << '\n';
	}
}

// Input; a string with unknown length, a int shows desire length
// Return: a string with desirable length new_len
// Function: to format the string
string format_string(string str, int new_len)
{
	while ( str.length() < new_len )
		str += " ";
	return str.substr(0, new_len);
}
	

// Input: a string that with unkonwn length
// Return: a string that extended or cut into the standard format of line that with a symbol for line separation in text_interface() (i.e. ' ')
// Function: convert the input string to standard format of text_interface (i.e. "standard_sentence" + " "(separator) ) <- only one line
// Meaning: sub-function of format_lines()
string format_line(string line)
{
	bool english = true;
	int len = line.length();						// store the initial length of sentence

	for (int i = 0; i < len; i++)						// scan the line to see whether there is chinese
	{
		if ((int)line[i] < 0 || (int)line[i] > 127)
		{
			english = false;
			break;
		}
	}

	if (english)
	{
		line = format_string(line, Length) + " ";
	}
	else
	{
		for (int i = 0; i < line.length(); i++)
		{
			if ( line[i] >= 0 && line[i] <= 127)
			{
				line.replace(i, 1, "　");
			}
		}

		line = line.substr(0, Length / 2 * 3);

		for (int i = 0; line.length() / 3 < Length / 2; i++)
		{
		       line += "　";
		}
	}
	
	return line;
}

// Input: 3 strings with unknown length
// Return: a concatenated string that will be separated into 3 lines in text_interface()
// Function: separate input strings into 3 lines during printing of text_interface()
// Example: input("a", "b", "c") output:
// a
// b
// c (within the text interface)
string format_lines(string l1, string l2, string l3)
{
	return format_line(l1) + format_line(l2) + format_line(l3);
}

// Input: a string with unknown length
// Return: a string that are 1/4 of "standard_sentence"
// Function: to format a string into a "column" of text inteface
// Meaning: sub-function of format_grids()
string format_grid(string grid)
{
	int len = Length / 4;
	while ( grid.length() < len )
		grid += " ";
	return grid.substr(0, len);
}

// Input: 4 stirng with unknown length
// Return: a concatenated string into "standard_sentence" and separated into 4 equal column of a line
// Function: allow the align of options
// Example: "A.apple       B.banana       C.cat          D.dog"
string format_grids(string g1, string g2, string g3, string g4)
{
	return  format_line( format_grid(g1) + format_grid(g2) + format_grid(g3) + format_grid(g4) );
}

// Input: a integer, a char representing mode sign or unsign
// Return: the string of the integer with "+" sign or not
// Function: convert integer into string with sign and unsign format
string itoa(int num, char mode)
{
	if (num == 0)
		return "0";

	int temp = (int) abs(num);
	string output = "";
	
	while (temp != 0)							// pop out the last digit which will concatenated with output string
	{
		int last = temp % 10;						// pop out the last digit
		temp /= 10;

		char n[] = { (char) ('0' + last), '\0'};			// convert the digit into c-string format
		output = n + output;						// concatenated with output
	}
	
	if (num > 0 && mode == 's')
		return "+" + output;
	else if ( num < 0 )
		return "-" + output;
	else
		return output;
}

void navigator_interface(Profile player, Point destiny)
{
	string current_location = "[" + itoa(player.location.x,'u') + "," + itoa(player.location.y,'u') + "]";
	string target_location = "[" + itoa(destiny.x,'u') + "," + itoa(destiny.y,'u') + "]";

	int x = destiny.x - player.location.x;
	int y = destiny.y - player.location.y;

	string distance = itoa( (abs(x) + abs(y)) , 'u') + " km";
	string direction = "";

	if ( x > 0 && y == 0 )
		direction = "East";
	else if ( x < 0 && y == 0 )
		direction = "West";
	else if ( x == 0 && y > 0 )
		direction = "North";
	else if ( x == 0 && y < 0 )
		direction = "South";
	else if ( x > 0 && y > 0 )
		direction = "North-East";
	else if ( x > 0 && y < 0 )
		direction = "South-East";
	else if ( x < 0 && y > 0 )
		direction = "North-West";
	else if ( x < 0 && y < 0 )
		direction = "South-West";

	string lines[3];

	lines[0] = format_string(" Direction: " + direction, 30) + "Current: " + current_location;
	lines[1] = format_string(" Distance:  " + distance, 30) + "Target:  " + target_location;
	lines[2]  = " Press ENTER to continue.";

	text_interface( format_lines( lines[0], lines[1], lines[2]) );
}

void main_interface(string lines[13])
{
	const int len = Width - 8;

	cout << "   " << ARC_TOP_LEFT;
	for (int i = 0; i < len; i++)
	{
		cout << LIGHT_HORIZONTAL;
	}
	cout << ARC_TOP_RIGHT << '\n';

	for (int i = 0; i < 13; i++)
	{
		lines[i] = format_string(lines[i], len);
	}

	for (int i = 0; i < 13; i++)
	{
		cout << "   " << LIGHT_VERTICAL << lines[i] << LIGHT_VERTICAL << '\n';
	}

	cout << "   " << ARC_BOTTOM_LEFT;				
	for (int i = 0; i < len; i++)
	{
			cout << LIGHT_HORIZONTAL;
	}
	cout << ARC_BOTTOM_RIGHT << '\n';
}

// Input: void
// Return: void
// Function: print the manual page of the game in the main interface
void manual_interface(void)
{
	string rules[13];

	rules[0] = "Rules:";
	rules[1] = "1. Every action of the character causes time to pass.";
	rules[2] = "2. Pass of time causes increase in Hunger Point (Hr).";
	rules[3] = "3. Health Point (HP) decreases when Hr reaches 100 %.";
	rules[4] = "4. HP decreases when attacked by enemy.";
	rules[5] = "5. Game is over when HP decreases to 0 %.";
	rules[6] = "6. Movement always comsumes Stamina Point (SP).";
	rules[7] = "7. Character cannot act when SP becomes 0 %.";
	rules[8] = "8. HP and SP recovered when at rest.";
	rules[9] = "9. HP, SP, Hr can be recovered by items collected.";
	rules[10] = "10.Items can be collected by exploring buildings on map.";
	rules[11] = "11.Less distance always produce higher attack.";
	rules[12] = "12.Your decisions determine the development of story.";

	main_interface(rules);
}

// Input: void
// Return: void
// Function: print logo "Fission" in the main interface
void logo_interface_fission(void)
{
	string lines[13];

	lines[0] = " ";
	lines[1] = " ";
	lines[2] = "    /$$$$$$$$ /$$                    /$$ ";
	lines[3] = "   | $$_____/|__/                   |__/     ";
	lines[4] = "   | $$       /$$  /$$$$$$$ /$$$$$$$ /$$  /$$$$$$  /$$$$$$$ ";
	lines[5] = "   | $$$$$   | $$ /$$_____//$$_____/| $$ /$$__  $$| $$__  $$";
	lines[6] = "   | $$__/   | $$|  $$$$$$|  $$$$$$ | $$| $$  \\ $$| $$  \\ $$";
	lines[7] = "   | $$      | $$ \\____  $$\\____  $$| $$| $$  | $$| $$  | $$";
	lines[8] = "   | $$      | $$ /$$$$$$$//$$$$$$$/| $$|  $$$$$$/| $$  | $$";
	lines[9] = "   |__/      |__/|_______/|_______/ |__/ \\______/ |__/  |__/";
	lines[10] = "";
	lines[11] = "";
	lines[12] = "";

	main_interface(lines);
}

// Input: void
// Return: void
// Function: print logo "Fight" in the main interface
void logo_interface_fight(void)
{
	string lines[13];

	lines[0] = " ";
	lines[1] = " ";
	lines[2] = "   /$$$$$$$$ /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$       /$$";
	lines[3] = "  | $$_____/|_  $$_/ /$$__  $$| $$  | $$|__  $$__/      | $$";
	lines[4] = "  | $$        | $$  | $$  \\__/| $$  | $$   | $$         | $$";
	lines[5] = "  | $$$$$     | $$  | $$ /$$$$| $$$$$$$$   | $$         | $$";
	lines[6] = "  | $$__/     | $$  | $$|_  $$| $$__  $$   | $$         |__/";
	lines[7] = "  | $$        | $$  | $$  \\ $$| $$  | $$   | $$             ";
	lines[8] = "  | $$       /$$$$$$|  $$$$$$/| $$  | $$   | $$          /$$";
	lines[9] = "  |__/      |______/ \\______/ |__/  |__/   |__/         |__/";
	lines[10] = "";
	lines[11] = "";
	lines[12] = "";

	main_interface(lines);
}

// Input: void
// Return: void
// Function: print logo "Maze" in the main interface
void logo_interface_maze(void)
{
	string lines[13];

	lines[0] = " ";
	lines[1] = " ";
	lines[2] = "          /$$      /$$                              ";
	lines[3] = "         | $$$    /$$$                              ";
	lines[4] = "         | $$$$  /$$$$  /$$$$$$  /$$$$$$$$  /$$$$$$ ";
	lines[5] = "         | $$ $$/$$ $$ |____  $$|____ /$$/ /$$__  $$";
	lines[6] = "         | $$  $$$| $$  /$$$$$$$   /$$$$/ | $$$$$$$$";
	lines[7] = "         | $$\\  $ | $$ /$$__  $$  /$$__/  | $$_____/";
	lines[8] = "         | $$ \\/  | $$|  $$$$$$$ /$$$$$$$$|  $$$$$$$";
	lines[9] = "         |__/     |__/ \\_______/|________/ \\_______/";
	lines[10] = "";
	lines[11] = "";
	lines[12] = "";

	main_interface(lines);
}

// Input: void
// Return: void
// Function: print logo "story" in the main interface
void logo_interface_story(void)
{
	string lines[13];

	lines[0] = "";
	lines[1] = "        /$$$$$$   /$$                                  ";
	lines[2] = "       /$$__  $$ | $$                                  ";
	lines[3] = "      | $$  \\__//$$$$$$    /$$$$$$   /$$$$$$  /$$   /$$";
	lines[4] = "      |  $$$$$$|_  $$_/   /$$__  $$ /$$__  $$| $$  | $$";
	lines[5] = "       \\____  $$ | $$    | $$  \\ $$| $$  \\__/| $$  | $$";
	lines[6] = "       /$$  \\ $$ | $$ /$$| $$  | $$| $$      | $$  | $$";
	lines[7] = "      |  $$$$$$/ |  $$$$/|  $$$$$$/| $$      |  $$$$$$$";
	lines[8] = "       \\______/   \\___/   \\______/ |__/       \\____  $$";
	lines[9] = "                                              /$$  | $$";
	lines[10] = "                                             |  $$$$$$/";
	lines[11] = "                                              \\______/ ";
	lines[12] = "";

	main_interface(lines);	
}

// Input: void
// Return: void
// Function: print the logo "win" in the main interface
void logo_interface_win(void)
{
	string lines[13];

	lines[0] = "";
	lines[1] = "";
	lines[2] = "             /$$      /$$ /$$                 /$$";
	lines[3] = "            | $$  /$ | $$|__/                | $$";
	lines[4] = "            | $$ /$$$| $$ /$$ /$$$$$$$       | $$";
	lines[5] = "            | $$/$$ $$ $$| $$| $$__  $$      | $$";
	lines[6] = "            | $$$$_  $$$$| $$| $$  \\ $$      |__/";
	lines[7] = "            | $$$/ \\  $$$| $$| $$  | $$          ";
	lines[8] = "            | $$/   \\  $$| $$| $$  | $$       /$$";
	lines[9] = "            |__/     \\__/|__/|__/  |__/      |__/";
	lines[10] = "";
	lines[11] = "";
	lines[12] = "";

	main_interface(lines);
}

// Input: void
// Return: void
// Function: print the logo "loss" in the main interface
void logo_interface_loss(void)
{
	string lines[13];

	lines[0] = "";
	lines[1] = "";
	lines[2] = "       /$$                                          /$$";
	lines[3] = "      | $$                                         | $$";
	lines[4] = "      | $$        /$$$$$$   /$$$$$$$ /$$$$$$$      | $$";
	lines[5] = "      | $$       /$$__  $$ /$$_____//$$_____/      | $$";
	lines[6] = "      | $$      | $$  \\ $$|  $$$$$$|  $$$$$$       |__/";
	lines[7] = "      | $$      | $$  | $$ \\____  $$\\____  $$          ";
       	lines[8] = "      | $$$$$$$$|  $$$$$$/ /$$$$$$$//$$$$$$$/       /$$";
	lines[9] = "      |________/ \\______/ |_______/|_______/       |__/";
	lines[10] = "";
	lines[11] = "";
	lines[12] = "";

	main_interface(lines);
}

void black_screen(void)
{
	string lines[13];

	string word = "Author: Henryyy         ";

	for (int i = 0; i < 10; i++)
		word += word;

	for (int i = 0; i < 13; i++)
		lines[i] = word.substr(i * 3, Length);

	main_interface(lines);
}


// Input: a item type array containning info of items, and int array containning quantity of item player owns
// Output: void
// Function: print and visualize the attribute and quantity of items in the main interface
void bag_interface(Item items[], int quantity[])
{
	string lines[13];
	int index = 0;

	lines[index] = format_grids("Items", " Effect 1", "Effect 2", "Quantity");

	for (int i = 0; i < 9; i++)								// iterate through items
	{
		index++;

		if ( i % 3 == 0 ) index++;

		string output[4];
		output[0] = itoa(i,'u') + "." + items[i].name;					// index and name of item
		output[1] = " " + items[i].type_1 + " " + items[i].effect_1;			// type and effect of item
		output[2] = items[i].type_2 + " " + items[i].effect_2;				// type 2 and effect 2 of item
		output[3] = itoa(quantity[i],'u');						// quantity of item that player owns

		lines[index] = format_grids(output[0], output[1], output[2], output[3]);	
	}
	
	main_interface(lines);
}

// Input: void
// Return: the key value of keyboard
// Function: receive key value without pressing "Enter".
int scanKeyboard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	in = getchar();
	tcsetattr(0,TCSANOW,&stored_settings);
	return in;
}

char input(void)
{
	return (char) scanKeyboard();
}

// Input: void
// Return: void
// Function: refresh the screen
void refresh(int num)
{
	system("clear");
	cout << endl;
}
