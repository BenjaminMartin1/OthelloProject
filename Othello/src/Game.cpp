#include <iostream>
#include <map>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include "Board.h"
#include "Game.h"

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
	ia		= IA(&board);
	winner	= 0;
	message	= "";
}


/*
	Fait jouer un tour de jeu à l'humain
*/
void Game::playHumain(int player)
{
	int x, y, x_cursor, y_cursor;
	bool press_enter = false;

	COORD pos;
	CONSOLE_SCREEN_BUFFER_INFO infos;

	// Au début du tour, on place le curseur dans la première case
	x_cursor = 2;
	y_cursor = 1;

	pos = {x_cursor,y_cursor};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);


	// On quitte la fonction si on se rend compte que le joueur n'a pas de cases dispo
	if (board.accessibles(player).size() == 0)
	{
		winner = (player == PLAYER_WHITE) ? PLAYER_BLACK : PLAYER_WHITE;
		return;
	}


	// On répète la saisie tant qu'un pion n'a pas été ajouté
	do
	{

		// Tant que la touche entré n'a pas été pressée
		do
		{

			if (player == PLAYER_WHITE)
				displayMessage("C'est au joueur blanc de jouer");
			else if (player == PLAYER_BLACK)
				displayMessage("C'est au joueur noir de jouer");


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

				// Abandon
				case 'l':
					winner = (player == PLAYER_WHITE) ? PLAYER_BLACK : PLAYER_WHITE;
					return;
					break;



				case 13:
					press_enter = true;
					break;

				default:
					displayMessage("Pour se deplacer c'est Z, D, S et Q");
			}

			pos = {x_cursor, y_cursor};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		}
		while(!press_enter);


		// Traduction de (x,y) terrain en (x,y) tableau
		x = (y_cursor/2);
		y = (x_cursor/4);

		press_enter = false;

		 // Message effacé si passe le move
		displayMessage("Deplacement impossible");
	}
	while (!board.move(x, y, player));

	// On afface le "deplacement impossible"
	displayMessage("                           ");
}


/*
	Fait un tour de jeu à l'IA
*/
void Game::playIA(int level, int player)
{
	// On quitte la fonction si on se rend compte que le joueur n'a pas de cases dispo
	if (board.accessibles(player).size() == 0)
	{
		winner = (player == PLAYER_WHITE) ? PLAYER_BLACK : PLAYER_WHITE;
		return;
	}

	ia.run(level, player);
}


/*
	Retourne le score d'un joueur
*/
int Game::getScore(int player)
{
	if (player != PLAYER_WHITE && player != PLAYER_BLACK)
		return 99;
	else
		return board.countPawns(player);
}


/*
	Retourne true si la partie est terminée, false sinon
*/
bool Game::isOver()
{
	return (winner == 0) ? false : true;
}



/*
	Retourne le gagnant
*/
int Game::getWinner()
{
	return winner;
}



/*
	Affiche le terrain de jeu
*/
void Game::display()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);

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
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + WHITE);
				cout << " " << char(2) << " ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
			}

			else if (board.getCell(i, j) == CELL_BLACK)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + BLACK);
				cout << " " << char(2) << " ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BLUE_GREY*16 + YELLOW);
			}

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


	cout << endl << endl << endl;


	// Affichage de l'arbre
	vector<map<char,int>> tree;
	std::map<char,int>::iterator it;
	tree = ia.getTree();

	if (tree.size() > 0)
	{

		cout << "Arbre de l'intelligence artificielle au dernier tour : " << endl << endl;

		for (int i=0 ; i<tree.size() ; i++)
		{
			cout << "[" << i << "]" << endl;
			cout << " |- Case : (" << tree[i]['x'] << ", " << tree[i]['y'] << ")" << endl;

			it = tree[i].find('s');
			if (it != tree[i].end())
				cout << " |- Score : " << tree[i]['s'] << endl;

			cout << endl;
		}
	}

	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);



	displayMessage(message);
}



void Game::displayMessage(string msg)
{

	message = msg;

	COORD pos;
	CONSOLE_SCREEN_BUFFER_INFO infos;

	// On sauvegrade la position du curseur
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&infos);

	// On efface un eventuel message déjà présent
	pos = {40, 5};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "                                      ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	// On écrit le message
	cout << message;

	// On remet le curseur là où il était
	pos = {infos.dwCursorPosition.X, infos.dwCursorPosition.Y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

