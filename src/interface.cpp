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
void status_interface(const Profile & player)
{
	static string lines[5];

	if ( lines[0].empty() )
	{
		lines[0] = TOP_LEFT;
		for (int i = 0; i < Length; i++)
			lines[0] += HORIZONTAL;
		lines[0] += TOP_RIGHT;
	}

	lines[1] = VERTICAL;
	lines[1] += format_string("", (Length - 13) / 2) + "-Time: ";
	lines[1] += ( itoa(player.time.hour, 'u').length() == 2 ) ? itoa(player.time.hour, 'u') : ( "0" + itoa(player.time.hour, 'u') );
	lines[1] += ":";
	lines[1] += ( itoa(player.time.min, 'u').length() == 2 ) ? itoa(player.time.min, 'u') : ( "0" + itoa(player.time.min, 'u') );
	lines[1] += "-" + format_string("", (Length - 13) / 2 + ( (Length % 2 == 1) ? 0 : 1 ) );
	lines[1] += VERTICAL;

	lines[2] = VERTICAL;
	lines[2] += "　生命值ＨＰ： ";
	for (int i = 1; i <= 10; i++) lines[2] +=  ( rint(player.hp.quantity / 10.0) >= i ) ? BLACK_SQUARE : WHITE_SQUARE;
	lines[2] += " " + format_string( itoa( (int) player.hp.quantity, 'u' ) + "%", 4 ) + format_string("", Length - 61);
	lines[2] += "　体力值ＳＰ： ";
	for (int i = 1; i <= 10; i++) lines[2] +=  ( rint(player.sp.quantity / 10.0) >= i ) ? BLACK_SQUARE : WHITE_SQUARE;
	lines[2] += " " + format_string( itoa( (int) player.sp.quantity, 'u' ) + "%", 4 ) + " ";
	lines[2] += VERTICAL;

	lines[3] = VERTICAL;
	lines[3] += "　饥饿值Ｈｒ： ";
	for (int i = 1; i <= 10; i++) lines[3] +=  ( rint(player.hr.quantity / 10.0) >= i ) ? BLACK_SQUARE : WHITE_SQUARE;
	lines[3] += " " + format_string( itoa( (int) player.hr.quantity, 'u' ) + "%", 4 ) + format_string("", Length - 61);

	lines[3] += "　攻击力ATK ： " + itoa(player.attack, 'u') + format_string("", Length - 52 - itoa(player.attack, 'u').length() );
	lines[3] += VERTICAL;

	if ( lines[4].empty() )
	{
		lines[4] = BOTTOM_LEFT;
		for (int i = 0; i < Length; i++)
			lines[4] +=  HORIZONTAL;
		lines[4] +=  BOTTOM_RIGHT;
	}

	for (int i = 0; i < 5; i++)
	{
		cout << lines[i] << '\n';
	}
}

// Input: string sentence that want to be displayed in the "chatbox", which is text interface
// Return: void
// Function: To enclose the output text within a "text box" and seperate sentence into 3 lines without "breaking" any word, which is, use the last space in a line as separator of lines , to allocate long sentence into 3 lines. so as to boost the readability of text inside the text interface.
// Example: "Hello world" will be separate into "Hello" & "world", instead of "Hell" & "o world" when separating lines.
void text_interface(string sentence)
{
	static string lines[5];

	if ( is_english(sentence) )
	{
		sentence = format_string(sentence, Length * 3 + 3);
	
		int pos1, pos2, pos3;					// position of the space at the end of line, which will be line separator

		pos1 = sentence.rfind(" ", Length);			// find the position of line separator(space) 
		if (pos1 != -1)
			lines[1] = sentence.substr(0, pos1);		// if found, allocate string before the separator(space) to line 1 of output
		else
			lines[1] = "error";				// if the input sentence doesn't match with required format, output error

		pos2 = sentence.rfind(" ", pos1 + 1 + Length );		// same with above, but for line 2
		if (pos1 != -1 && pos2 != -1)
			lines[2] = sentence.substr(pos1 + 1, pos2 - pos1 - 1);
		else
			lines[2] = "error";
	
		pos3 = sentence.rfind(" ", pos2 + 1 + Length );		// same with above, but for line 3
		if (pos1 != -1 && pos2 != -1 && pos3 != -1)
			lines[3] = sentence.substr(pos2 + 1, pos3 - pos2 - 1);
		else
			lines[3] = "error";

		for (int i = 1; i <= 3; i++)
		{
			lines[i] = format_string(lines[i], Length);
		}
	}
	else
	{
		int len = Length / 2 * 3;
		sentence = format_string_chinese(sentence, Length * 3);

		lines[1] = sentence.substr(0, len);
		lines[2] = sentence.substr(len, len);
		lines[3] = sentence.substr(len * 2, len);
	}

	if ( lines[0].empty() )
	{
		lines[0] = TOP_LEFT;					// print the upper boundary
		for (int i = 0; i < Length; i++)
			lines[0] += HORIZONTAL;
		lines[0] += TOP_RIGHT;
	}
	if ( lines[4].empty() )
	{
		lines[4] = BOTTOM_LEFT;
		for (int i = 0; i < Length; i++)
			lines[4] += HORIZONTAL;
		lines[4] += BOTTOM_RIGHT;
	}

	cout << lines[0] << '\n';
	for (int i = 1; i <= 3; i++)
	{
		cout << VERTICAL << lines[i] << VERTICAL << '\n';
	}
	cout << lines[4] << '\n';
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
			return "房";
		case 2:						// lake's content
			return "水";
		case 3:						//Hospital's content
			return "医";
		case 4:						// Food shop's content
			return "食";
		case 5:						// Weapon shop's content
			return "武";
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

// Input; a string with unknown length, a int shows desire length
// Return: a string with desirable length new_len
// Function: to format the string
string format_string(string str, const int & new_len)
{
	while ( str.length() < new_len )
		str += " ";
	return str.substr(0, new_len);
}

string format_string_chinese(string str, const int & new_len)
{
	for (int i = 0; i < str.length(); i++)
	{
		if ( str[i] >= 0 && str[i] <= 127)
		{
			str.replace(i, 1, translate_chinese(str[i]) );
		}
	}
	for (int i = 0; str.length() < new_len / 2 * 3; i++)
	{
	       str += "　";
	}
	return str.substr(0, new_len / 2 * 3);
}
	

// Input: a string that with unkonwn length
// Return: a string that extended or cut into the standard format of line that with a symbol for line separation in text_interface() (i.e. ' ')
// Function: convert the input string to standard format of text_interface (i.e. "standard_sentence" + " "(separator) ) <- only one line
// Meaning: sub-function of format_lines()
string format_line(string line)
{
	switch (is_english(line))
	{
		case true:
			return format_string(line, Length) + " ";
		case false:
			return format_string_chinese(line, Length);
	}
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
	if ( ! is_english(l1) || ! is_english(l2) || ! is_english(l3) )
	{
		l1 += "　"; l2 += "　"; l3 += "　";
	}
	return format_line(l1) + format_line(l2) + format_line(l3);
}

// Input: a string with unknown length
// Return: a string that are 1/4 of "standard_sentence"
// Function: to format a string into a "column" of text inteface
// Meaning: sub-function of format_grids()
string format_grid(const string & grid)
{
	switch ( is_english(grid) )
	{
		case true:
			return format_string(grid, Length / 4);
		case false:
			return format_string_chinese(grid, Length / 4);
	}
}

// Input: 4 stirng with unknown length
// Return: a concatenated string into "standard_sentence" and separated into 4 equal column of a line
// Function: allow the align of options
// Example: "A.apple       B.banana       C.cat          D.dog"
string format_grids(string g1, string g2, string g3, string g4)
{
	if ( ! is_english(g1) || ! is_english(g2) || ! is_english(g3) || ! is_english(g4) )
	{
		g1 += "　"; g2 += "　"; g3 += "　"; g4 += "　";
	}
	return  format_line( format_grid(g1) + format_grid(g2) + format_grid(g3) + format_grid(g4) );
}

// Input: a integer, a char representing mode sign or unsign
// Return: the string of the integer with "+" sign or not
// Function: convert integer into string with sign and unsign format
string itoa(const int & num, const char & mode)
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
	string current_location = "[" + itoa(player.location.x,'u') + "，" + itoa(player.location.y,'u') + "]";
	string target_location = "[" + itoa(destiny.x,'u') + "，" + itoa(destiny.y,'u') + "]";

	int x = destiny.x - player.location.x;
	int y = destiny.y - player.location.y;

	string distance = itoa( (abs(x) + abs(y)) , 'u') + " km";
	string direction = "";

	if ( x > 0 && y == 0 )
		direction = "东方";
	else if ( x < 0 && y == 0 )
		direction = "西方";
	else if ( x == 0 && y > 0 )
		direction = "北方";
	else if ( x == 0 && y < 0 )
		direction = "南方";
	else if ( x > 0 && y > 0 )
		direction = "东北";
	else if ( x > 0 && y < 0 )
		direction = "东南";
	else if ( x < 0 && y > 0 )
		direction = "西北";
	else if ( x < 0 && y < 0 )
		direction = "西南";

	string lines[3];

	lines[0] = format_string_chinese("　方位：" + direction, 30) + "当前位置" + current_location;
	lines[1] = format_string_chinese("　距离：" + distance, 30) + "目标位置" + target_location;
	lines[2]  = ANY_KEY;

	text_interface( format_lines( lines[0], lines[1], lines[2]) );
}

void main_interface(string content[13])
{
	const int len = Width - 8;

	static string lines[Height];
	int idx = 0;

	if ( lines[idx].empty() )
	{
		lines[idx] = ARC_TOP_LEFT;
		for (int i = 0; i < len; i++)
		{
			lines[idx] += LIGHT_HORIZONTAL;
		}
		lines[idx] += ARC_TOP_RIGHT;
	}
	idx++;
	for (int i = 0; i < 13; i++)
	{
		if ( is_english(content[i]) )
		{
			lines[idx] = LIGHT_VERTICAL;
			lines[idx] += format_string(content[i], len);
			lines[idx] += LIGHT_VERTICAL;
		}
		else
		{
			lines[idx] = LIGHT_VERTICAL;
			lines[idx] += format_string_chinese(content[i], len);
			lines[idx] += LIGHT_VERTICAL;
		}
		idx++;
	}
	if ( lines[idx].empty() )
	{
		lines[idx] = ARC_BOTTOM_LEFT;				
		for (int i = 0; i < len; i++)
		{
			lines[idx] += LIGHT_HORIZONTAL;
		}
		lines[idx] += ARC_BOTTOM_RIGHT;
	}

	for (int i = 0; i < Height; i++)
	{
		cout << "   " << lines[i] << '\n';
	}
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

	static string filling = format_string("", Width - 8);
	for (int i = 0; i < 13; i++)
		lines[i] = filling + lines[i];
	filling = filling.substr(0, filling.length() - 1);

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
	static string lines[13]
	{
		"",
		"        /$$$$$$   /$$                                  ",
		"       /$$__  $$ | $$                                  ",
		"      | $$  \\__//$$$$$$    /$$$$$$   /$$$$$$  /$$   /$$",
		"      |  $$$$$$|_  $$_/   /$$__  $$ /$$__  $$| $$  | $$",
		"       \\____  $$ | $$    | $$  \\ $$| $$  \\__/| $$  | $$",
		"       /$$  \\ $$ | $$ /$$| $$  | $$| $$      | $$  | $$",
		"      |  $$$$$$/ |  $$$$/|  $$$$$$/| $$      |  $$$$$$$",
		"       \\______/   \\___/   \\______/ |__/       \\____  $$",
		"                                              /$$  | $$",
		"                                             |  $$$$$$/",
		"                                              \\______/ ",
		""
	};


	//string temp = lines[12];
	//for (int i = 12; i > 0; i--)
	//	lines[i] = lines[i-1];
	//lines[0] = temp;
	//	string temp = lines[0];
	//	for (int i = 0; i < 13; i++)
	//		lines[i] = lines[i+1];
	//	lines[12] = temp;

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
	static string word = "Author: Henry----------";
	static int num = 0;
	while (word.length() < (12 * 3 + num*3 + (Width - 8) * 3) )
	{
		word += word;
	}
	for (int i = 0; i < 13; i++)
	{
		lines[i] = word.substr(i * 3 + num*3, (Width - 8) * 3);
	}
	num++;
	main_interface(lines);
}


// Input: a item type array containning info of items, and int array containning quantity of item player owns
// Output: void
// Function: print and visualize the attribute and quantity of items in the main interface
void bag_interface(Item items[], int quantity[])
{
	string lines[13];
	int index = 0;

	lines[index] = format_grids("物品名称", "效果一", "效果二", "剩余数量");

	for (int i = 0; i < 9; i++)								// iterate through items
	{
		index++;

		if ( i % 3 == 0 ) index++;

		string output[4];
		output[0] = itoa(i,'u') + "．" + items[i].name;					// index and name of item
		output[1] = items[i].type_1 + items[i].effect_1;				// type and effect of item
		output[2] = items[i].type_2 + items[i].effect_2;				// type 2 and effect 2 of item
		output[3] = itoa(quantity[i],'u');						// quantity of item that player owns

		lines[index] = format_grids(output[0], output[1], output[2], output[3]);	
	}
	
	main_interface(lines);
}

string translate_chinese(const char & ch)
{
	switch ( ch )
	{
		case 'A':
			return "Ａ";
		case 'B':
			return "Ｂ";
		case 'C':
			return "Ｃ";
		case 'D':
			return "Ｄ";
		case 'E':
			return "Ｅ";
		case 'F':
			return "Ｆ";
		case 'G':
			return "Ｇ";
		case 'H':
			return "Ｈ";
		case 'I':
			return "Ｉ";
		case 'J':
			return "Ｊ";
		case 'K':
			return "Ｋ";
		case 'L':
			return "Ｌ";
		case 'M':
			return "Ｍ";
		case 'N':
			return "Ｎ";
		case 'O':
			return "Ｏ";
		case 'P':
			return "Ｐ";
		case 'Q':
			return "Ｑ";
		case 'R':
			return "Ｒ";
		case 'S':
			return "Ｓ";
		case 'T':
			return "Ｔ";
		case 'U':
			return "Ｕ";
		case 'V':
			return "Ｖ";
		case 'W':
			return "Ｗ";
		case 'X':
			return "Ｘ";
		case 'Y':
			return "Ｙ";
		case 'Z':
			return "Ｚ";
		case 'a':
			return "ａ";
		case 'b':
			return "ｂ";
		case 'c':
			return "ｃ";
		case 'd':
			return "ｄ";
		case 'e':
			return "ｅ";
		case 'f':
			return "ｆ";
		case 'g':
			return "ｇ";
		case 'h':
			return "ｈ";
		case 'i':
			return "ｉ";
		case 'j':
			return "ｊ";
		case 'k':
			return "ｋ";
		case 'l':
			return "ｌ";
		case 'm':
			return "ｍ";
		case 'n':
			return "ｎ";
		case 'o':
			return "ｏ";
		case 'p':
			return "ｐ";
		case 'q':
			return "ｑ";
		case 'r':
			return "ｒ";
		case 's':
			return "ｓ";
		case 't':
			return "ｔ";
		case 'u':
			return "ｕ";
		case 'v':
			return "ｖ";
		case 'w':
			return "ｗ";
		case 'x':
			return "ｘ";
		case 'y':
			return "ｙ";
		case 'z':
			return "ｚ";
		case '0':
			return "０";
		case '1':
			return "１";
		case '2':
			return "２";
		case '3':
			return "３";
		case '4':
			return "４";
		case '5':
			return "５";
		case '6':
			return "６";
		case '7':
			return "７";
		case '8':
			return "８";
		case '9':
			return "９";
		case '!':
			return "！";
		case '@':
			return "＠";
		case '#':
			return "＃";
		case '$':
			return "￥";
		case '%':
			return "％";
		case '^':
			return "＾";
		case '&':
			return "＆";
		case '*':
			return "＊";
		case '(':
			return "（";
		case ')':
			return "）";
		case '_':
			return "＿";
		case '=':
			return "＝";
		case '+':
			return "＋";
		case '-':
			return "－";
		case '~':
			return "～";
		case '`':
			return "｀";
		case '{':
			return "｛";
		case '}':
			return "｝";
		case '[':
			return "【";
		case ']':
			return "】";
		case '\\':
			return "＼";
		case '|':
			return "｜";
		case ':':
			return "：";
		case ';':
			return "；";
		case '"':
			return "＂";
		case '\'':
			return "＇";
		case '<':
			return "＜";
		case '>':
			return "＞";
		case ',':
			return "，";
		case '.':
			return "．";
		case '?':
			return "？";
		case '/':
			return "／";
		case ' ':
			return "　";
		default:
			return "　";
	}
}
					
			
void fps(const int & number)
{
	int second = 1000000;
	usleep(second/number);
	return;
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
