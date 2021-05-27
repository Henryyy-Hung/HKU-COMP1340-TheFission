// File name: interface.cpp
// Author: Hung Ka Hing
// UID: 3035782750
// Description: To hold all functions regarding displaying the game content and facilitate modularization.

#include "interface.h"					// include self defined structures, external library, and function header of interface.cpp

#define HORIZONTAL "\xE2\x94\x81"							// components of bondary of text interface and status interface
#define VERTICAL "\xE2\x94\x83"
#define TOP_LEFT "\xE2\x94\x8F"
#define TOP_RIGHT "\xE2\x94\x93"
#define BOTTOM_LEFT "\xE2\x94\x97"
#define BOTTOM_RIGHT "\xE2\x94\x9B"

#define LIGHT_HORIZONTAL "\xE2\x94\x80"							// component of boundary of map interface
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

#define BLACK_SQUARE "\xE2\x96\xA0"							// components of status bar
#define WHITE_SQUARE "\xE2\x96\xA1"	

#define CHARACTOR 	"\xE2\x98\xBB"							// indicator of charactor
#define SHADE		"\xE2\x96\x91"							// indicator of boundary
#define DANGER		"\xE2\x9C\x98 "

#define WATER		"WT"
#define ATTACK		"AT"
#define FOOD		"FD"
#define HOSPITAL	"HP"
#define HOUSE		"UB"

const int Width = 70;									// Width of all interface
const int Length = Width - 2;								// Length of the output text
const int Height = 15;									// Height of the main interface (e.g. map & manual)

// Input: profile of player
// Return: void 
// Function: To visualize and display the current status (e.g. HP, SP, ATK) of player in a more intuitive and clear way (e.g. HP bar, status box)
// Meaning: To decrease the difficulty of understanding the game and make the complicated data more intuitive to user
void status_interface(Profile player)
{
	cout << TOP_LEFT;								// print the upper boundary
	for (int i = 0; i < Length; i++)
		cout << HORIZONTAL;
	cout << TOP_RIGHT << endl;

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
		<< VERTICAL << endl;							// print right boundary

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
		<< " " << VERTICAL << endl;

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
		<< VERTICAL << endl;

	cout << BOTTOM_LEFT;								// print the lower boundary
	for (int i = 0; i < Length; i++)
		cout << HORIZONTAL;
	cout << BOTTOM_RIGHT << endl;
}

// Input: string sentence that want to be displayed in the "chatbox", which is text interface
// Return: void
// Function: To enclose the output text within a "text box" and seperate sentence into 3 lines without "breaking" any word, which is, use the last space in a line as separator of lines , to allocate long sentence into 3 lines. so as to boost the readability of text inside the text interface.
// Example: "Hello world" will be separate into "Hello" & "world", instead of "Hell" & "o world" when separating lines.
void text_interface(string sentence)
{
	bool english = true;
	bool chinese = false;
	int len = sentence.length();				// store the initial length of sentence
	string line_1, line_2, line_3;

	for (int i = 0; i < len; i++)
	{
		if ((int)sentence[i] < 0 || (int)sentence[i] > 127)
		{
			english = false;
			chinese = true;
		}
	}	

	if (english)
	{
		for (int i = 0; i < (Length) * 3 - len + 3; i++)	// convert sentence into standard output format (i.e. specific length)
			sentence +=  " ";

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
	else if (chinese)
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
		cout << TOP_RIGHT << endl;

		cout << left;						// print output lines
		cout << VERTICAL << setw(Length) << line_1 << VERTICAL << endl;	
		cout << VERTICAL << setw(Length) << line_2 << VERTICAL << endl;
		cout << VERTICAL << setw(Length) << line_3 << VERTICAL << endl;

		cout << BOTTOM_LEFT;					// print the lower boundary
		for (int i = 0; i < Length; i++)
				cout << HORIZONTAL;
		cout << BOTTOM_RIGHT << endl;
	}
}

// Input: integer which representing symbol on the map
// Return: void
// Function: to print the integer into the symbol it represent on the map
// Meaning: a sub-function of map_interface(), to facilitate modularization
void map_convertor(int symbol)
{
	if ( symbol == 0 )					// empty grid's content
		cout << "  ";
	else if ( symbol == 1 )					// unknown building's content
		cout << HOUSE;
	else if ( symbol == 2 )					// lake's content
		cout << WATER;
	else if ( symbol == 3 )					// Hospital's content
		cout << HOSPITAL;
	else if ( symbol == 4 )					// Food shop's content
		cout << FOOD;
	else if ( symbol == 5 )					// Weapon shop's content
		cout << ATTACK;
	else if ( symbol == 99 )
		cout << DANGER;
	else if ( symbol > 100 && symbol < 200 )		// location of monster
		cout << right << setw(2) << symbol % 100;
	else if ( symbol == 999 || symbol == 998 )		// boundary's content
		cout << SHADE << SHADE;
	else							// advoid bug
		cout << "  ";

}

// Input: the dynamic 2D int array of map, point of location of player
// Return: void
// Function: To print and visualize the map content in a more clear and intuitive manner (i.e. using of coordinate lines & convertion of map content)
// Meaning: increase the readability of map and make the game more user-friendly
void map_interface(int **map, Point location)
{
	int x = location.x;							// x coordinate of the player					
	int y = location.y;							// y coordinate of the player
	int h_range = (Width - 1) / 3;						// no. of horizontal grids that will be printed
	int v_range = (Height - 1) / 2;						// no. of vertical grids that will be printed

	int east = x + (h_range - 1) / 2 - 1;					// max. x coordinate of the map that will be printed
	int west = x - (h_range - 1) / 2 + 1;					// min. x coordinate of the map that will be printed
	int north = y + (v_range - 1) / 2;					// max. y coordinate of the map that will be printed
	int south = y - (v_range - 1) / 2;					// min. y coofdinate of the map that will be printed
	
	cout << "   ";
	cout << ARC_TOP_LEFT;							// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
	{
		if ( i % 3 == 0  || i % 3 == 1)
			cout << LIGHT_HORIZONTAL;
		else 
			cout << HORIZONTAL_DOWN;
	}
	cout << ARC_TOP_RIGHT
		<< endl;

	for (int j = north; j >= south; j--)					// iterate the y coordinate of map from north to south
	{
		if ( j != north )						// print horizontal boundary between grids
		{
			cout << "   ";
			cout << VERTICAL_RIGHT;
			for (int i = 0; i < Width - 8; i++)
			{
				if ( i % 3 == 0 || i % 3 == 1)
					cout << LIGHT_HORIZONTAL;
				else
					cout << CROSS;
			}
			cout << VERTICAL_LEFT
				<< endl;
		}

		cout << "   ";
		for (int i = west; i <= east; i++)				// iterate the x coordinate of map from west to east
		{
			if ( i == west)
				cout << LIGHT_VERTICAL;				// print the left-most boundary

			if ( i == x && j == y)
				cout << CHARACTOR << " ";			// print user's location
			else
				map_convertor(map[i][j]);			// print the symbol represented by the map[i][j]

			cout << LIGHT_VERTICAL;					// print the right-most boundary
		}
		cout << endl;
	}

	cout << "   ";
	cout << ARC_BOTTOM_LEFT;						// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
	{
		if ( i % 3 == 0 || i % 3 == 1)
			cout << LIGHT_HORIZONTAL;
		else
			cout << HORIZONTAL_UP;
	}
	cout << ARC_BOTTOM_RIGHT
		<< endl;
}

// Input; a string with unknown length, a int shows desire length
// Return: a string with desirable length new_len
// Function: to format the string
string format_string(string temp, int new_len)
{
	temp += " ";
	temp = temp.substr(0, new_len);
	int original_len = temp.length();
	for (int i = original_len; i <= new_len; i++)
		temp += " ";
	return temp;
}
	

// Input: a string that with unkonwn length
// Return: a string that extended or cut into the standard format of line that with a symbol for line separation in text_interface() (i.e. ' ')
// Function: convert the input string to standard format of text_interface (i.e. "standard_sentence" + " "(separator) ) <- only one line
// Meaning: sub-function of format_lines()
string format_line(string line)
{
	bool english = true;
	bool chinese = false;
	int len = line.length();						// store the initial length of sentence

	for (int i = 0; i < len; i++)
	{
		if ((int)line[i] < 0 || (int)line[i] > 127)
		{
			english = false;
			chinese = true;
			break;
		}
	}

	if (english)
	{
		line = line.substr(0,Length);					// cut the string into "standard_sentence"
		for (int i = 0; line.length() < Length + 1; i++)
			line += " ";						// at space (separator) at the end of sentence to symbolize end of line
	}
	else if (chinese)
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
	for (int i = 0; grid.length() < len; i++)
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
	bool positive = true;
	string output = "";
	string sign = "";
	
	if ( mode == 's' )
		sign = "+";

	if (num < 0)
	{
		positive = false;						// record negative
		num *= -1;							// convert into positive form
	}
	else if (num == 0)							// exception for 0
		output = "0";

	while (num != 0)							// pop out the last digit which will concatenated with output string
	{
		int temp = num % 10;						// pop out the last digit
		num /= 10;

		char n[] = { (char) ('0' + temp), '\0'};			// convert the digit into c-string format
		output = n + output;						// concatenated with output
	}
	
	if (positive && output != "0")						// add sign (i.e. "+","-","")
		return sign + output;
	else if ( ! positive )
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

	// to conceptualize the travelling distance and direction, make it more user-friendly
	string line_1 = format_string(" Direction: " + direction, 30) + "Current: " + current_location;
	string line_2 = format_string(" Distance:  " + distance, 30) + "Target:  " + target_location;
	string line_3  = " Press ENTER to continue.";

	text_interface( format_lines( line_1, line_2, line_3) );
}

// Input: void
// Return: void
// Function: print the manual page of the game in the main interface
void manual_interface(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	string a = "Rules:";
	string b = "1. Every action of the character causes time to pass.";
	string c = "2. Pass of time causes increase in Hunger Point (Hr).";
	string d = "3. Health Point (HP) decreases when Hr reaches 100 %.";
	string e = "4. HP decreases when attacked by enemy.";
	string f = "5. Game is over when HP decreases to 0 %.";
	string g = "6. Movement always comsumes Stamina Point (SP).";
	string h = "7. Character cannot act when SP becomes 0 %.";
	string i = "8. HP and SP recovered when at rest.";
	string j = "9. HP, SP, Hr can be recovered by items collected.";
	string k = "10.Items can be collected by exploring buildings on map.";
	string l = "11.Less distance always produce higher attack.";
	string m = "12.Your decisions determine the development of story.";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);	// convert lines into standard output format

	for (int i = 0; i < 13; i++)						// print lines
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: void
// Function: print logo "Fission" in the main interface
void logo_interface_fission(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	string a = " ";
	string b = " ";
	string c = "    /$$$$$$$$ /$$                    /$$ ";
	string d = "   | $$_____/|__/                   |__/     ";
	string e = "   | $$       /$$  /$$$$$$$ /$$$$$$$ /$$  /$$$$$$  /$$$$$$$ ";
	string f = "   | $$$$$   | $$ /$$_____//$$_____/| $$ /$$__  $$| $$__  $$";
	string g = "   | $$__/   | $$|  $$$$$$|  $$$$$$ | $$| $$  \\ $$| $$  \\ $$";
	string h = "   | $$      | $$ \\____  $$\\____  $$| $$| $$  | $$| $$  | $$";
	string i = "   | $$      | $$ /$$$$$$$//$$$$$$$/| $$|  $$$$$$/| $$  | $$";
	string j = "   |__/      |__/|_______/|_______/ |__/ \\______/ |__/  |__/";
	string k = "";
	string l = "";
	string m = "";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};				// same as previous function

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);

	for (int i = 0; i < 13; i++)
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: void
// Function: print logo "Fight" in the main interface
void logo_interface_fight(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	string a = " ";
	string b = " ";
	string c = "   /$$$$$$$$ /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$       /$$";
	string d = "  | $$_____/|_  $$_/ /$$__  $$| $$  | $$|__  $$__/      | $$";
	string e = "  | $$        | $$  | $$  \\__/| $$  | $$   | $$         | $$";
	string f = "  | $$$$$     | $$  | $$ /$$$$| $$$$$$$$   | $$         | $$";
	string g = "  | $$__/     | $$  | $$|_  $$| $$__  $$   | $$         |__/";
	string h = "  | $$        | $$  | $$  \\ $$| $$  | $$   | $$             ";
	string i = "  | $$       /$$$$$$|  $$$$$$/| $$  | $$   | $$          /$$";
	string j = "  |__/      |______/ \\______/ |__/  |__/   |__/         |__/";
	string k = "";
	string l = "";
	string m = "";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};				// same as previous function

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);

	for (int i = 0; i < 13; i++)
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: void
// Function: print logo "Maze" in the main interface
void logo_interface_maze(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	string a = " ";
	string b = " ";
	string c = "          /$$      /$$                              ";
	string d = "         | $$$    /$$$                              ";
	string e = "         | $$$$  /$$$$  /$$$$$$  /$$$$$$$$  /$$$$$$ ";
	string f = "         | $$ $$/$$ $$ |____  $$|____ /$$/ /$$__  $$";
	string g = "         | $$  $$$| $$  /$$$$$$$   /$$$$/ | $$$$$$$$";
	string h = "         | $$\\  $ | $$ /$$__  $$  /$$__/  | $$_____/";
	string i = "         | $$ \\/  | $$|  $$$$$$$ /$$$$$$$$|  $$$$$$$";
	string j = "         |__/     |__/ \\_______/|________/ \\_______/";
	string k = "";
	string l = "";
	string m = "";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};				// same as previous function

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);

	for (int i = 0; i < 13; i++)
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: void
// Function: print logo "story" in the main interface
void logo_interface_story(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

    string a = "";
	string b = "";
	string c = "        /$$$$$$   /$$                                  ";
	string d = "       /$$__  $$ | $$                                  ";
	string e = "      | $$  \\__//$$$$$$    /$$$$$$   /$$$$$$  /$$   /$$";
	string f = "      |  $$$$$$|_  $$_/   /$$__  $$ /$$__  $$| $$  | $$";
	string g = "       \\____  $$ | $$    | $$  \\ $$| $$  \\__/| $$  | $$";
	string h = "       /$$  \\ $$ | $$ /$$| $$  | $$| $$      | $$  | $$";
	string i = "      |  $$$$$$/ |  $$$$/|  $$$$$$/| $$      |  $$$$$$$";
	string j = "       \\______/   \\___/   \\______/ |__/       \\____  $$";
	string k = "                                              /$$  | $$";
	string l = "                                             |  $$$$$$/";
	string m = "                                              \\______/ ";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};				// same as previous function

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);

	for (int i = 0; i < 13; i++)
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: void
// Function: print the logo "win" in the main interface
void logo_interface_win(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	string a = "";
	string b = "";
	string c = "             /$$      /$$ /$$                 /$$";
	string d = "            | $$  /$ | $$|__/                | $$";
	string e = "            | $$ /$$$| $$ /$$ /$$$$$$$       | $$";
	string f = "            | $$/$$ $$ $$| $$| $$__  $$      | $$";
	string g = "            | $$$$_  $$$$| $$| $$  \\ $$      |__/";
	string h = "            | $$$/ \\  $$$| $$| $$  | $$          ";
	string i = "            | $$/   \\  $$| $$| $$  | $$       /$$";
	string j = "            |__/     \\__/|__/|__/  |__/      |__/";
	string k = "";
	string l = "";
	string m = "";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};				// same as previous function

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);

	for (int i = 0; i < 13; i++)
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: void
// Function: print the logo "loss" in the main interface
void logo_interface_loss(void)
{
	cout << "   " << ARC_TOP_LEFT;						// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	string a = "";
	string b = "";
	string c = "       /$$                                          /$$";
	string d = "      | $$                                         | $$";
	string e = "      | $$        /$$$$$$   /$$$$$$$ /$$$$$$$      | $$";
	string f = "      | $$       /$$__  $$ /$$_____//$$_____/      | $$";
	string g = "      | $$      | $$  \\ $$|  $$$$$$|  $$$$$$       |__/";
	string h = "      | $$      | $$  | $$ \\____  $$\\____  $$          ";
	string i = "      | $$$$$$$$|  $$$$$$/ /$$$$$$$//$$$$$$$/       /$$";
	string j = "      |________/ \\______/ |_______/|_______/       |__/";
	string k = "";
	string l = "";
	string m = "";

	string rules[] = {a,b,c,d,e,f,g,h,i,j,k,l,m};				// same as previous function

	for (int i = 0; i < 13; i++)
		rules[i] = format_line( rules[i] ).substr(0, Width - 8);

	for (int i = 0; i < 13; i++)
		cout << "   "
		        << LIGHT_VERTICAL
			<< rules[i]
			<< LIGHT_VERTICAL
			<< endl;

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}


// Input: a item type array containning info of items, and int array containning quantity of item player owns
// Output: void
// Function: print and visualize the attribute and quantity of items in the main interface
void bag_interface(Item items[], int quantity[])
{
	cout << "   " << ARC_TOP_LEFT;								// print the upper boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_TOP_RIGHT << endl;

	cout << "   "										// print the header of columns
		<< LIGHT_VERTICAL
		<< format_grids("Items", " Effect 1", "Effect 2", "Quantity").substr(0,Width - 8)
		<< LIGHT_VERTICAL
		<< endl;

	for (int i = 0; i < 9; i++)								// iterate through items
	{
		if ( i % 3 == 0 )
			cout << "   " << LIGHT_VERTICAL << setw(Width - 8) << "" << LIGHT_VERTICAL << endl;	// print empty lines

		string c1 = itoa(i,'u') + "." + items[i].name;					// index and name of item
		string c2 = " " + items[i].type_1 + " " + items[i].effect_1;			// type and effect of item
		string c3 = items[i].type_2 + " " + items[i].effect_2;				// type 2 and effect 2 of item
		string c4 = itoa(quantity[i],'u');						// quantity of item that player owns

		string output = format_grids(c1, c2, c3, c4).substr(0, Width - 8);		// format string into four grids
		cout << "   " << LIGHT_VERTICAL << output << LIGHT_VERTICAL << endl;		// print the line
	}

	cout << "   " << ARC_BOTTOM_LEFT;					// print the lower boundary
	for (int i = 0; i < Width - 8; i++)
			cout << LIGHT_HORIZONTAL;
	cout << ARC_BOTTOM_RIGHT << endl;
}

// Input: void
// Return: the key value of keyboard
// Function: receive key value without pressing "Enter".
// Reference: https://reurl.cc/e9269M
// Declaration: the receive of key value of keyboard could be done by us, for example, we could just use cin
//              but in order to facilitate the user experience, we decide to use the 
//              function that could avoid pressing "Enter".
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
	//cout << "Please enter your command: ";
	return (char) scanKeyboard();
}

// Input: void
// Return: char 
// Function: receive input char from user and return
// Declaration: this is our original function, it indicates that we have the capabilty to implement the input part and handle invalid input!!!
//char input(void)
//{
//	cout << "Please enter your command: ";
//
//	string input;						// prevent long input that produce bug
//	getline(cin, input);
//
//	if (input.length() == 1)
//	{
//		char output = input.c_str()[0];
//
//		if ( output >= 'A' && output <= 'Z')		// make the input case insensitive
//			output = output - 'A' + 'a';
//
//		return output;
//	}
//	else							// indicator of invalid input
//		return 'x';
//}

// Input: void
// Return: void
// Function: refresh the screen
void refresh(int num)
{
	//for (int i = 0; i < 1; i++)
		//cout << endl;
	system("clear");
	cout << endl;
}
