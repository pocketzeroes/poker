#ifndef _GAMEDEBUG_H
#define _GAMEDEBUG_H
#include<vector>
#include"Card.h"
#include<iostream>
#include"Color.h"
#if DEBUG
void print_cards(const char *name, std::vector<Card> *cards);
#else
# define print_cards(args...)
#endif
#endif
