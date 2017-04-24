#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "Game.h"
#include <windows.h>
#include <conio.h>

using namespace std;

Game::Game()
{
	reset();
}

Game::~Game()
{
	//dtor
}


/*
	(Ré)initialise la partie
*/
void Game::reset()
{
	board	= Board();
	ia		= IA(&board, IA_LVL_2);
	winner	= 0;
}


/*
	Fait jouer un tour de jeu à l'humain
*/
void Game::playHumain()
{
    int x, y, x_cursor, y_cursor;
    bool press_enter = false;

    COORD pos;
    CONSOLE_SCREEN_BUFFER_INFO infos;

    // On répète la saisie tant qu'un pion n'a pas été ajouté
    do
    {
        // Au début du tour, on place le curseur dans la première case
        x_cursor = 2;
        y_cursor = 1;

        pos = {x_cursor,y_cursor};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        // Tant que la touche entré n'a pas été pressée
        do
        {

            switch(getch())
            {
                // Récupération de la position du curseur
                GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&infos);
                x_cursor = infos.dwCursorPosition.X;
                y_cursor = infos.dwCursorPosition.Y;

                case 'z':
                    if ((y_cursor-2)>=1)
                        y_cursor-=2;
                    break;

                case 'd':
                    if ((x_cursor+4)<=30)
                        x_cursor+=4;
                    break;

                case 's':
                    if ((y_cursor+2)<=16)
                        y_cursor+=2;
                    break;

                case 'q':
                    if ((x_cursor-4)>=2)
                        x_cursor-=4;
                    break;

                case 13:
                    press_enter = true;
                    break;
            }

            pos = {x_cursor, y_cursor};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        }
        while(!press_enter);


        // Traduction de (x,y) terrain en (x,y) tableau
        x = (y_cursor/2);
        y = (x_cursor/4);

        press_enter = false;
    }
    while (!board.move(x,y,PLAYER_WHITE));
}

/*
	Fait un tour de jeu à l'IA
*/
void Game::playIA()
{
	ia.run();
}


/*
	Returne true si la partie est terminée, false sinon
*/
bool Game::isOver()
{
	return (winner == 0) ? false : true;
}


void Game::display()
{
	// Nettoyage de la console
	system("cls");


	cout << char(218) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(191) << endl;


	// Pour change rangé
	for (int i=0 ; i<8 ; i++)
	{

		if (i!=0)
		{
			cout << char(195) << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(197);
			cout << char(196) << char(196) << char(196) << char(180);

			cout << endl;
		}



		// Pour chaque colonne
		for (int j=0 ; j<8 ; j++)
		{
			cout << char(179);

			if (board.getCell(i, j) == CELL_WHITE)
				cout << " W ";

			else if (board.getCell(i, j) == CELL_BLACK)
				cout << " B ";

			else
				cout << "   ";
		}

		cout << char(179) << endl;
	}


	cout << char(192) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	cout << char(217) << endl;

}
