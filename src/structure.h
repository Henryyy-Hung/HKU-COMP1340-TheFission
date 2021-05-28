// File name: structure.h
// Author: Hung Ka Hing
// UID: 3035782750
// Description: Define the structure that will be used in the game, such structure can improve effeciency and readability of game.

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>							// include all the header files that will be used in other files.
#include <fstream>
#include <stdio.h> 
#include <termio.h>
#include <unistd.h>

#include <string>
#include <vector>

#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

using namespace std;

struct Point								// structure of a point on 2D surface (i.e. map)
{
	int x, y;							// x and y coordinate of the point

	// Input: x coordinate and y coordinate
	// Return: void
	// Function: to manipulate the x,y coordinate more intuitively
	void set(int x_value, int y_value)
	{
		x = x_value;
		y = y_value;
	}

	// Input: change in x coordinate, change in y coordinate
	// Return: void
	// Function: to change the location more intuitively
	void change(int x_value, int y_value)
	{
		x += x_value;
		y += y_value;
	}
};

struct Time								// structure of 24 hour time (i.e. hour:min)
{
	int hour,min;							// hour and minutes

	// Input: number of hour, number of minute
	// Return: void
	// Function: to set the time more intuitively
	void set(int hours, int mins)
	{
		hour = hours;
		min = mins;
	}

	// Input: change in minute
	// Return: void
	// Function: to change hour and minute by 24 base system and 60 base system respectively
	void change(int value)
	{
		if (min + value < 60)
			min += value;
		else
		{
			hour += (min + value) / 60;
			hour %= 24;					// 24 base system on hour
			min = (min + value) % 60;			// 60 base system on minute
		}
	}
};

struct Status								// structure of user status (i.e. Health Point, Stamina Poitn, etc.)
{
	double quantity;						// quantity of the status (e.g. 100 HP)

	// Input: value of status
	// Return: void
	// Function: to set the status more intuitively
	void set(double value)
	{
		quantity = value;
	}

	// Input: value of changing the status
	// Return: void
	// Function: to change the status within range [0,100]
	void change(double value)
	{
		if (quantity + value <= 0)
			quantity = 0;
		else if (quantity + value >= 100)
			quantity = 100;
		else
			quantity += value;
	}
};

struct Item								// structure that hold information of game items
{
	string name;							// name of item
	string type_1;							// type of effect (e.g. +HP)
	string effect_1;						// value of effect (e.g. +10)
	string type_2;
	string effect_2;
	string annotation;						// annotation from developer on specific item
};

struct Profile								// structure that holds information of player
{
	Time time;							// time of player
	Point location;							// virtual location of player (i.e. trigger story but not reference of map)

	Status hp;							// Healthy point of player
	Status sp;							// Stamina point of player
	Status hr;							// Hunger point of player

	int destiny;							// the check point no. character are going to (about story)

	int attack;							// attack pint of player

	int item[10];							// array storing quantity of items player owns
};

struct Monster								// structure that holds information of monster
{
	Point location;							// location of monster
	Status hp;							// Health Point of monster
	int attack;							// attack point of mosnter
};


struct Node
{
	int id;
	Point location;
	Node * branch_1;
	Node * branch_2;
};


#endif





