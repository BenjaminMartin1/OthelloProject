#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <map>
#include <vector>

#include "UserInterface.h"
#include "Game.h"
#include "Board.h"
#include "constants.h"


using namespace std;


int main()
{

	int choice;
	Game game;


	UserInterface::setup();
	UserInterface::hello();

	choice = UserInterface::menu();

	game.display();
	while(!game.isOver())
	{

		// Joueur 1
		switch(choice)
		{
			case MENU_MULTI:
			case MENU_IA_1:
			case MENU_IA_2:
				game.playHumain(PLAYER_WHITE);
				break;

			case MENU_IA_IA:
				game.playIA(PLAYER_WHITE);
				break;

		}
		game.display();


		// On check une fin de partie entre les deux tours
		if(game.isOver())
			break;

		// Eventelle attente entre les deux tours
		if (choice == MENU_IA_1 or choice == MENU_IA_IA)
			Sleep(1300);



		// Joueur 2
		switch(choice)
		{
			case MENU_MULTI:
				game.playHumain(PLAYER_BLACK);
				break;


			case MENU_IA_1:
			case MENU_IA_IA:
				game.playIA(PLAYER_BLACK);
				break;


			case MENU_IA_2:
				game.playIA(PLAYER_BLACK);
				break;
		}
		game.display();

	}


	int winner = game.getWinner();
	int score  = game.getScore(PLAYER_WHITE);

	system("cls");
	cout << "Fin du jeu" << endl << endl;
	cout << "Gagnant : " << winner << endl;
	cout << "Score : " << score << endl;


	//UserInterface::bye();


	return 0;
}
