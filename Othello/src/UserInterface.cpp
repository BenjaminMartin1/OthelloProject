#include <windows.h>
#include <conio.h>
#include <string>
#include "constants.h"
#include "UserInterface.h"

UserInterface::UserInterface()
{
	//ctor
}

UserInterface::~UserInterface()
{
	//dtor
}

void UserInterface::setup()
{
	SetConsoleTitle("Jeu Othello");
	//system("mode con lines=40 cols=80");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
}


int UserInterface::menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);

	int  choice = 1;
	bool press_enter = false;

	do
	{
		system("cls");

		cout << endl << endl;

		cout << "                          ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
		cout << "                           " << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
		cout << "                          ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
		cout << "  Que voulez-vous faire ?  " << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
		cout << "                          ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
		cout << "                           " << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
		cout << endl << endl << endl;


		if (choice == 1)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + WHITE);

		cout << "                     " << char(196) << " Jouer a deux chacun son tour" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);



		if (choice == 2)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + WHITE);

		cout << "                     " << char(196) << " Jouer contre l'ordinateur (niveau 1)" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);



		if (choice == 3)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + WHITE);

		cout << "                     " << char(196) << " Jouer contre l'ordinateur (niveau 2)" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);


		if (choice == 4)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + WHITE);

		cout << "                     " << char(196) << " Ordinateur contre ordinateur" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);


		if (choice == 5)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + WHITE);

		cout << "                     " << char(196) << " Quitter" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);


		cout << endl << endl << endl << endl;
		cout << "                Pendant une partie appuyez sur [L] pour abandonner" << endl << endl;

		switch(getch())
		{
			case 'z':
				if (choice<=1)
					choice=5;
				else
					choice--;
				break;


			case 's':
				if (choice>=5)
					choice=1;
				else
					choice++;
				break;

			case 13:
				press_enter = true;
		}
	}
	while(!press_enter);

	return choice;
}


void UserInterface::hello()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	system("cls");

	cout << endl << endl;
	cout << "                       ____  _   _          _ _       " << endl;
	cout << "                      / __ \\| | | |        | | |      " << endl;
	cout << "                     | |  | | |_| |__   ___| | | ___  " << endl;
	cout << "                     | |  | | __| '_ \\ / _ \\ | |/ _ \\ " << endl;
	cout << "                     | |__| | |_| | | |  __/ | | (_) |" << endl;
	cout << "                      \\____/ \\__|_| |_|\\___|_|_|\\___/ " << endl;

	cout << endl << endl << endl;

	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "                                    " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << " [Appuyez sur ENTRER pour demarrer] " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "                                    " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << endl << endl << endl;

	getch();
	system("cls");
}


void UserInterface::bye(int winner, int score)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	system("cls");

	string winner_name;

	if (winner == PLAYER_WHITE)
		winner_name = "joueur blanc";
	else
		winner_name = "joueur noir ";


	cout << endl << endl;
	cout << "                        .d88b.  db    db d88888b d8888b." << endl; 
	cout << "                       .8P  Y8. 88    88 88'     88  `8D" << endl; 
	cout << "                       88    88 Y8    8P 88ooooo 88oobY'" << endl; 
	cout << "                       88    88 `8b  d8' 88~~~~~ 88`8b  " << endl; 
	cout << "                       `8b  d8'  `8bd8'  88.     88 `88." << endl; 
	cout << "                        `Y88P'     YP    Y88888P 88   YD" << endl; 


	cout << endl << endl << endl;


	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "                                     " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "  Le " << winner_name << " a gagne la partie  " << endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "               Score : " << score << "            " << endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "                                     " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << endl << endl << endl;

	getch();
	system("cls");
}
