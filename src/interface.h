// File name: interface.h
// Author: Hung Ka Hing
// UID: 3035782750
// Description: Hold the function header of interface.cpp and provide self defined structure and external libraries to interface.cpp

#ifndef INTERFACE_H
#define INTERFACE_H

#include "structure.h"			// include self defined structure and external libraries

void refresh(int);

void status_interface(const Profile &);

void map_interface(int**, Point);

void navigator_interface(Profile, Point);

void manual_interface(void);

void main_interface(string [13]);

void logo_interface_fission(void);

void logo_interface_fight(void);

void logo_interface_maze(void);

void logo_interface_story(void);

void logo_interface_win(void);

void logo_interface_loss(void);

void bag_interface(Item[], int []);

void black_screen();

void text_interface(string);

char input(void);

string format_string(string, const int &);

string format_string_chinese(string, const int &);

string format_lines(string, string, string);

string format_grids(string, string, string, string);

string itoa(const int &,const char &);

bool is_english(string);

void fps(const int & number);

#endif
