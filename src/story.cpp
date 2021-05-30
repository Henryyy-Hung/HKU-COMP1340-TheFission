// File name: story.cpp
// Author: Huang Jiaxin && Hung Ka Hing
// UID: 303577177 && 3035782750
// Description: To hold functions regarding storyline building and story display

#include "story.h"
#include "interface.h"

// Input: the head of a linked list, and the tail of linked list, a node id, and the node location Point
// Return: void
// Function: Add the node with node id and location to the tail of the linked list
void tail_insert(Node * &head, Node * &tail, int id, Point location)
{
	Node * p = new Node;
	p->id = id;
	p->location = location;
	p->branch_1 = NULL;
	p->branch_2 = NULL;

	if (head == NULL)
	{
		head = p;
		tail = p;
	}
	else
	{
		tail->branch_1 = p;
		tail->branch_2 = p;
		tail = p;
	}
}

// Input: head of a linked list, tail of a linked list, start id of the linked list, stop id of the linked list
// Return: void
// Function: create a linked list with nodes with consecutive id from start to stop, excluding the stop.
void extend_list(Node * &head, Node * &tail, int start, int stop)
{
	static Point location = {0, 0};

	for (int i = start; i < stop; i++)
	{
		int id = i;

		tail_insert(head, tail, id, location);
	}
	{
		int sign_1 = 1, sign_2 = 1;

		if (rand()%2 == 1) sign_1 *= -1;
		if (rand()%2 == 1) sign_2 *= -1;

		location.x += ((rand() % 15) * sign_1);
		location.y += ((rand() % 15) * sign_2);
	}
}

// Input: head of the linked list, node id
// Return; the node pointer pointed to the node with the node id in the linked list
// Function:: search the node recursively
Node * search(Node * head, int id)
{
	Node * output = NULL;

	if ( head != NULL )
	{
		if (head->id == id)
		{
			output = head;
		}
		else
		{
			if (output == NULL && head->branch_1 != NULL && head->id <  head->branch_1->id)
			{
				output = search(head->branch_1, id);
			}
			if (output == NULL && head->branch_2 != NULL && head->branch_2 != head->branch_1 && head->id < head->branch_2->id)
			{	
				output = search(head->branch_2, id);
			}
		}
	}

	return output;
}

// Input: a head of master branch linked list, a node id, and the head of the sub-branch
// Return: void
// Function: set the branch_2 of the node with the node id point to the sub-branch
//           which means branch the sub-branch from node with node id of master branch
void branch_from(Node * master_head, int node_id, Node * head)
{
	Node * branch_node = search(master_head, node_id);
	if (branch_node != NULL)
	{
		branch_node->branch_2 = head;
	}
}

// Input: a head of mster branch linked list, a node id, and the tail of sub-branch
// Return: void
// Function: set all the branch of the last node of sub-branch point to the node with node-id in master branch
//           which means merge the sub-branch to the node with node id in master branch
void merge_to(Node * master_head, int merging_id, Node * branch_tail)
{
	Node * merging_node = search(master_head, merging_id);

	if (merging_node != NULL)
	{
		branch_tail->branch_1 = merging_node;
		branch_tail->branch_2 = merging_node;
	}
}

// Input: a head of master branch, a linking node id, a linked node id, validity of linking branch 1 and 2
// Return: void
// Function: link the branch_1 or branch_2 of node with linked node id to the node with linking node id.
//           which means link two node together 
void link(Node * master_head, int linking_id, int linked_id, int branch)
{
	Node * linking_node = search(master_head, linking_id);
	Node * linked_node = search(master_head, linked_id);

	if (linking_node != NULL && linked_node != NULL)
	{
		if (branch == 1)
			linking_node->branch_1 = linked_node;
		if (branch == 2)
			linking_node->branch_2 = linked_node;
	}
}

// Input: void
// Return: the head of master branch
// Function: form a network or tree of storyline.
Node *  initialize_story(void)
{
	Node * master_head = NULL;
	Node * master_tail = NULL;
	extend_list(master_head, master_tail, 1000, 1999);

	link(master_head, 1000, 1002, 2);
	link(master_head, 1001, 1003, 2);
	link(master_head, 1002, 1001, 1);

	//Node * branch_2_head = NULL;
	//Node * branch_2_tail = NULL;
	//extend_list(branch_2_head, branch_2_tail, 100000, 100002);

	//branch_from(master_head, 1100, branch_2_head);
	//merge_to(master_head, 1008, branch_2_tail);

	return master_head;
}

// Input; information of player, the head of storyline
// Return: a point symbolize the next target position
// Function: initialize the target position, which is the triggering position of next story.
Point initialize_destiny(Profile player, Node * story)
{
	Node * temp = search(story, player.destiny);
	Point error = {404, 404};
	if ( temp != NULL )
		return temp->location;
	else
		return error;
}

// Input; information of player, the head of storyline
// Return: int that symbolize the existance of story.txt, if it is 1, story.txt is not exist
// Function: check the existance of story.txt, display the story, allow user to make choice, and update the destiny of user.
int display_story(Profile &player, Node * story)
{
	int id = player.destiny;
	char command = '0';
	bool start = false;
	string line;

	ifstream fin;
	fin.open("story.txt");

	if (fin.fail())
		return 1;

	while (getline(fin, line))
	{
		if ( line == ("#" + itoa(id, 'u') + " start") )
		{
			start = true;
		}
		else if (start == true && line == "#end")
		{
			break;
		}
		else if (start == true)
		{
			refresh(100);
			status_interface(player);
			logo_interface_story();
			text_interface(line);
			input();
		}
	}

	while (getline(fin, line) && start == true)
	{
		if ( line == ("#" + itoa(id, 'u') + " choice" ) )
		{
			bool english = true, chinese = false;

			string line_1, line_2, line_3;
			line_1 = " Your decision is?";
			getline(fin, line_2);
			getline(fin, line_3);

			if ( ! is_english(line_2) || ! is_english(line_3) )
			{
				line_1 = "　你的选择是？";
				english = false;
				chinese = true;
			}

			refresh(100);
			status_interface(player);
			logo_interface_story();
			text_interface( format_lines(line_1, line_2, line_3) );
			command = input();

			while (command != '1' && command != '2')			
			{
				refresh(100);
				status_interface(player);
				logo_interface_story();
				text_interface( format_lines(line_1, line_2, line_3) );
				command = input();
			}

			string choice = (command == '1') ? line_2 : line_3;

			refresh(100);
			status_interface(player);
			logo_interface_story();

			if (english) 
				text_interface(format_lines("Your decision is:" + choice, "", "Note: Please follow the Navigator"));
			else if (chinese) 
				text_interface(format_lines("你的选择是：" + choice, "　",  "注：请根据导航寻找剧情点"));

			input();
			break;
		}
	}

	// update destiny and avoid reading the non-exixt pointer
	// avoid bug after display last story
	Node * current = search(story, player.destiny);
	if (current != NULL && start == true)
	{
		if (current->branch_1 != NULL && command != '2')
			player.destiny = current->branch_1->id;
		else if (current->branch_2 != NULL && command == '2')
			player.destiny = current->branch_2->id;
		else
			player.destiny = 0;
	}

	fin.close();

	if (start == true)
		return 0;
	else
		return 2;
}



	



