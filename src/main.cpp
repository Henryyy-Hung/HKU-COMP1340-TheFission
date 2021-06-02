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
	srand(2021);

	Profile player;								// create a profile for player (record players data)
	initialize(player);							// initialize the profile of player (set default values)
	log_in_page(player);							// initialize the profile of player according to his command

	int map_len = (int) pow(2, 7) ;						// the edge length of a square map (max = 2^31)
	Point location = { (int) pow(2, 6), (int) pow(2, 6)};			// Actual location of player on the map

	int **map = new int *[map_len];						// initialize the dynamic 1D array to store map
	for (int row = 0; row < map_len; row++)
		map[row] = new int [map_len];					// map size = map_len * map_len

	map_generator(map, map_len);						// generate map with random distribution of buildings and events

	if ( player.attack == 15 )
		herbination_base(map, location);

	Node * story = initialize_story();					// bulld the story line and return the head of divergent linked list
	Point destiny = initialize_destiny(player, story);			// the location that trigger out story

	bool skip = true;
	bool test = (argc > 1)? true:false;

	bool hold = true;
	char command;
	string lines[3];

	while (true)								// refresh the interface whenever command is received
	{
		if ( hold == false || (game_over(player) && !restart(player)) )
		{
			lines[0] = "　退出成功";
			lines[1].clear();
			lines[2].clear();
			for (int i = 0; i < 60 * 1.2; i++)
			{
				refresh(100);
				status_interface(player);
				black_screen();
				text_interface(format_lines(lines[0], lines[1], lines[2]));
				fps(60);
			}
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
			lines[0].clear();
			lines[1].clear();
			lines[2].clear();
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
						lines[0] = "　游戏已存档";
						lines[1] = ANY_KEY;
						break;
					case 1:
						lines[0] = "　存档失败";
						lines[1] = ANY_KEY;
						break;
				}
				break;

			case 'm':
				refresh(100);							
				status_interface(player);					
				manual_interface();						
				text_interface( ANY_KEY );
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
				lines[0] = "　休息完毕，已恢复少量ＨＰ及ＳＰ";
				lines[1] = ANY_KEY;
				break;

			case 'w': case 'a': case 's': case 'd':
				if ( player.sp.quantity == 0 )
				{
					lines[0] = "　你的ＳＰ为０";
					lines[1] = "　请休息或是用道具恢复ＳＰ";
					lines[2] = ANY_KEY;
				}
				else if ( ! moved(player, map, location, command) )
				{
					lines[0] = "　你似乎遇到了一些障碍物";
					lines[1] = "　请朝别的方向移动";
					lines[2] = ANY_KEY;
				}
				else
				{
					int x = location.x, y = location.y;
					int event = map[x][y];
					int randint = rand() % 100 + 1;
					int min = 0, max = map_len - 1;

					if ( ! test ) status_after_move(player);

					map[x][y] = 0;

					if ( ( max - x <= 20 || x - min <= 20 || max - y <= 20 || y - min <= 20 ) && map_len * 2 < pow(2, 13))
					{
						extend_map(map, map_len, location);
					}

					switch ( event )
					{
						case 1:
							lines[0] = "　你探索了一栋未知建筑";
							if ( randint <= 10 )
							{
								player.item[rand() % 9]++;
								lines[1] = "　你似乎发现了什么";
								lines[2] = "　请检查你的背包";
							}
							else
							{
								lines[1] = "　然而你什么也没有找到";
							}
							break;
						
						case 2:
							lines[0] = "　你探索了一处水源";
							if ( randint <= 33 )
							{
								player.item[5]++;
								lines[1] = "　你得到了一瓶纯净水";
							}
							else
							{
								player.item[7]++;
								lines[1] = "　你得到了一瓶辐射水";
							}
							break;

						case 3:
							lines[0] = "　你探索了一所废弃医院";
							if ( randint > 50 )
							{
								lines[1] = "　然而你什么也没有找到";
							}
							else if ( randint > 25 )
							{
								player.item[8]++;				
								lines[1] = "　你得到了一瓶碘伏";
							}
							else if ( randint > 10 )				
							{
								player.item[6]++;
								lines[1] = "　你得到了一瓶肾上腺素";
							}
							else if ( randint > 3 )					
							{
								player.item[1]++;
								lines[1] = "　你得到了一捆绷带";
							}
							else								
							{
								player.item[0]++;
								lines[1] = "　你得到了一瓶未知药剂";
							}
							break;

						case 4:
							lines[0] = "　你探索了一间食品商店";
							if ( randint > 50 )						
							{
								player.item[4]++;
								lines[1] = "　你得到了一块辐射小蛋糕";
							}
							else if ( randint > 20 )					
							{
								player.item[3]++;
								lines[1] = "　你得到了一块辐射肉";
							}
							else						
							{
								player.item[2]++;
								lines[1] = "　你得到了一块纯净肉";
							}
							break;

						case 5:
							player.attack++;
							lines[0]  = "　你探索了一间武器商店";
							lines[1]  = "　你的攻击力提升了１点";
							break;

						case 10: case 99:
							if ( test ) break;
							save(player);
							battle(player, map, location);
							break;

						case 11:
							if ( test ) break;
							string notice[3];
							notice[0] = "　你掉进了一处地下城废墟";
							notice[1] = "　出口东北和西南方向";
							notice[2] = ENTER;
							while ( command != '\n' )
							{
								refresh(100);
								status_interface(player);
								logo_interface_maze();
								text_interface( format_lines( notice[0], notice[1], notice[2]) );
								command = input();
							}
							maze(map,location);
							break;
					}
				}

			default:
				{
					static int count = 0;
					if ( player.hr.quantity < 100 )
					{
						count = 0;
					}
					else if ( player.hr.quantity == 100 && count < 1 && ! game_over(player) )	
					{
						string warning[3];
						warning[0] = "　极度饥饿状态！！！你的饥饿值太高了！！！";
						warning[1] = "　请尽快吃些东西，避免ＨＰ的下降！！！";
						warning[2] = ENTER;
						while (command != '\n')
						{
							default_page(player, map, location);
							text_interface( format_lines( warning[0], warning[1], warning[2] ) );
							command = input();
						}
						count++;
					}
				}
				break;
		}

		for (int i = -1; i <= 1; i++)						// search whether there is story around the player (3 x 3)
		{
			for (int j = -1; j <= 1; j++)
			{
				Point nearby = player.location;
				nearby.change(i, j);
				string notice[3];
				static char confirm = '\0';
				if (nearby == destiny)					// check the triggering position
				{
					switch ( display_story(player, story) )		// check the existance of story.txt and play story
					{
						case 0:
							skip = true;
							break;
						case 1:
							notice[0] = "　请下载ｓｔｏｒｙ．ｔｘｔ";
							notice[1] = ENTER;
							notice[2].clear();
							while ( confirm != '\n' )
							{
								refresh(100);
								default_page(player, map, location);
								text_interface(format_lines(notice[0], notice[1], notice[2]));
								confirm = input();
							}
							break;
						case 2:
							notice[0] = "　请等待作者更新故事";
							notice[1] = "　创作不易，多多支持";
							notice[2] = ENTER;
							while ( confirm != '\n' )
							{
								refresh(100);
								default_page(player, map, location);
								text_interface(format_lines(notice[0], notice[1], notice[2]));
								confirm = input();
							}
							break;
					}
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

	lines[0] = "　操作指南：";
	lines[1] = format_grids( "　移动：ＷＡＳＤ", "　休息：Ｒ", "　背包：Ｂ", "　导航：Ｎ");
	lines[2] = format_grids( "　侦查：Ｌ"     , "　手册：Ｍ", "　存档：Ｚ", "　退出：！");
	
	text_interface( format_lines(lines[0], lines[1], lines[2]) );
}

void log_in_page(Profile & player)
{
	string lines[3];

	lines[0] = "　欢迎来到《裂变》";
	lines[1] = "　开启新游戏请按ｎ";
	lines[2] = "　加载存档请按ｌ";

	bool hold = true;

	for (int i = 0; i <= 62; i++)
	{
		refresh(100);
		status_interface(player);
		logo_interface_fission();
		text_interface(format_lines(lines[0], "　加载中．．．", ""));
		fps(90);
	}

	while (true)
	{
		refresh(100);
		status_interface(player);
		logo_interface_fission();
		text_interface(format_lines(lines[0], lines[1], lines[2]));
		char command = input();	

		if ( ! hold )
		{
			if (command == '\n')
				break;
		}
		else if ( command == 'n' )				
		{
			hold = false;
			lines[0] = "　初始化成功";
			lines[1] = "　新游戏已载入";
			lines[2] = ENTER;
		}
		else if ( command == 'l' && load(player) == 0 )	
		{
			hold = false;
			lines[0] = "　加载成功";
			lines[1] = "　游戏将从存档点继续";
			lines[2] = ENTER;
		}
		else if ( command == 'l' )
		{
			lines[0] = "　加载失败";
		}
		else
		{
			lines[0] = "　输入非法，请再次输入．";
		}

	}
}

bool restart(Profile & player)
{
	string lines[3];
	lines[0] = "　１．新游戏";
	lines[1] = "　２．加载存档";
	lines[2] = "　３．退出游戏";

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
			lines[0] = "　读档成功";
			lines[1] = ANY_KEY;
			lines[2] = "";
		}
		else if ( command == '2' )
		{
			lines[0] = "　读档失败";
			lines[1] = ANY_KEY;
			lines[2] = "";
		}
		else if ( command == '1' )
		{
			hold = false;
			initialize(player);
			lines[0] = "　新游戏初始化完毕";
			lines[1] = ANY_KEY;
			lines[2] = "";
		}
		else
		{
			lines[0] = "　１．新游戏";
			lines[1] = "　２．加载存档";
			lines[2] = "　３．退出游戏";
		}
	}
	
	return true;
}
