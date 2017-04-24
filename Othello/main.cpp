#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <map>
#include <vector>

#include "Game.h"
#include "Board.h"
#include "constants.h"


using namespace std;

int main()
{
	
	Game game;
	game.display();

	while(!game.isOver())
	{
		game.playHumain();
		game.display();

		Sleep(1300);

		game.playIA();
		game.display();
	}

	return 0;
}
