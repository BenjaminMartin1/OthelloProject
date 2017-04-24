#include <iostream>
#include <stdlib.h>
#include "constants.h"
#include "IA.h"
#include "Board.h"
#include <algorithm>



using namespace std;

IA::IA()
{
}

IA::IA(Board* p_board, int lvl)
{
	board = p_board;
	level = lvl;
}

IA::~IA()
{
	//dtor
}


/*
	Déclenche la bonne IA
*/
void IA::run()
{
	if (level == IA_LVL_1)
	{
		lvl_1();
	}
	else if (level == IA_LVL_2)
	{
		lvl_2();
	}
}



/*
	Intelligence artificielle level 1
	Utilise la classe Board pour placer un pion
*/
void IA::lvl_1()
{
	vector< map<char,int> > cells_accessibles;
	int random, x, y;

	// On récupère toutes les cellules où peut aller l'IA
	cells_accessibles = board->accessibles(PLAYER_BLACK);

	// On choisit une cellule au hasard
	random = rand() % (int)(cells_accessibles.size());
	x = cells_accessibles[random]['x'];
	y = cells_accessibles[random]['y'];

	// Et on y va !
	board->move(x, y, PLAYER_BLACK);
}

