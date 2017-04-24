#include <windows.h>
#include <conio.h>
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
	system("mode con lines=40 cols=80");
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
		cout << " Choisissez un mode de jeu " << endl;

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



		switch(getch())
		{
			case 'z':
				if (choice<=1)
					choice=4;
				else
					choice--;
				break;


			case 's':
				if (choice>=4)
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


void UserInterface::bye(int score)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + RED);
	system("cls");

	cout << endl << endl;
	cout << "                       ____  _   _          _ _       " << endl;
	cout << "                      / __ \\| | | |        | | |      " << endl;
	cout << "                     | |  | | |_| |__   ___| | | ___  " << endl;
	cout << "                     | |  | | __| '_ \\ / _ \\ | |/ _ \\ " << endl;
	cout << "                     | |__| | |_| | | |  __/ | | (_) |" << endl;
	cout << "                      \\____/ \\__|_| |_|\\___|_|_|\\___/ " << endl;

	cout << endl << endl << endl;


	cout << "Score du gagnant : " << score << endl << endl;
	
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "                                    " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << " [Appuyez sur ENTRER pour quitter] " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << "                     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW*16 + BLUE_GREY);
	cout << "                                    " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
	cout << endl << endl << endl;

	getch();
	system("cls");
}
