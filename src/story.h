// File name: story.h
// Author: Huang Jiaxin && Hung Ka Hing
// UID: 303577177 && 3035782750
// Description: To hold functions prototypes of story.cpp

#ifndef STORY_H
#define STORY_H

#include "structure.h"

void tail_insert(Node * &head, Node * &tail, int id, Point location);

void extend_list(Node * &head, Node * &tail, int start, int stop);

Node * search(Node * head, int id);

void branch_from(Node * master_head, int node_id, Node * head);

void merge_to(Node * master_head, int merging_id, Node * branch_tail);

void link_to(Node * master_head, int linking_id, int linked_id, bool branch_1, bool branch_2);

Node *  initialize_story(void);

Point initialize_destiny(Profile player, Node * story);

int display_story(Profile &player, Node * story);

#endif
