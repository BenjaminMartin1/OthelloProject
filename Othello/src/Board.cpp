#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Board.h"

using namespace std;


/*
	Constructeur de l'objet, qui règle la disposition
	par défaut du plateau
*/  
Board::Board()
{
	// Remplisssage des cases vides partout
	for (int i=0 ; i<8 ; i++)
	{
		for (int j=0 ; j<8 ; j++)
		{
			cells[i][j] = CELL_EMPTY;
		}
	}

	// Remplissage des positions initiales
	cells[3][3] = CELL_WHITE;
	cells[3][4] = CELL_BLACK;
	cells[4][3] = CELL_BLACK;
	cells[4][4] = CELL_WHITE;

	associatedScore = NULL; //Nombre seulement utilisée dans les calculs de l'IA pour stocker le score associée au coup effectué précédent
	previousState = NULL;
	recordedMove.x = 0;
	recordedMove.y = 0;
}


Board::~Board()
{
	//dtor
}


/*
	Retourne le contenu d'une cellule
*/
int Board::getCell(int x, int y)
{
	if ( x < 0 || x > 7 || y < 0 || y > 7 )
		return 0;

	return cells[x][y];
}



/*
	Ajoute un pion à un endroit du plateau, si la cellule est autorisée.
	Et exécute les actions qui en découle, c'est à dire manger les pions
	adversaires.
	Retourne true si le déplacement a été effectué, false sinon (coords invalides)
*/
bool Board::move(int x, int y, int player)
{
	bool coord_valid;
	vector< map<char,int> > cells_accessibles;
	vector< map<char,int> > cells_to_eat;

	coord_valid = false;


	// On récupère la liste des cellules où le joueur a le droit de se déplacer
	cells_accessibles = accessibles(player);


	// On vérifie que les coordonnées passés en paramètres pointent vers une de ces cellules
	for (int i=0 ; i<cells_accessibles.size() ; i++)
	{
		if (cells_accessibles[i]['x'] == x && cells_accessibles[i]['y'] == y)
		{
			coord_valid = true;
			break;
		}
	}

	if (!coord_valid)
		return false;


	// On place le pion
	cells[x][y] = (player == PLAYER_WHITE) ? CELL_WHITE : CELL_BLACK;


	// On bouffe tous les pions que l'on peut
	cells_to_eat = eatables(x, y, player);

	for (int j=0 ; j<cells_to_eat.size() ; j++)
	{
		eat(cells_to_eat[j]['x'], cells_to_eat[j]['y']);
	}

	return true;
}



/*
	Retourne la liste des cellules où le joueur indiqué peut se déplacer.
	C'est à dire tous les cases adjacentes aux pions ennemis et qui permettent
	d'en encadrer.
	Le retour est sous forme d'un vecteur de maps (clés x et y)
*/
vector< map<char,int> > Board::accessibles(int player)
{
	std::vector< map<char,int> > accessibles;
	std::vector< map<char,int> > enemies;
	int x, y, step_x, step_y;


	// Vérification de la validité de player
	if (player != PLAYER_WHITE && player != PLAYER_BLACK)
		return accessibles;


	// On défini de quel type sont les cases enemies
	int enemy_cell	 = (player == PLAYER_WHITE) ? CELL_BLACK : CELL_WHITE;


	// On localise tous les pions ennemis
	for (int i=0 ; i<8 ; i++)
	{
		for (int j=0 ; j<8 ; j++)
		{
			if (cells[i][j] == enemy_cell)
			{
				// On ajoute l'ennemi au vecteur qui référence tous les ennemis
				map<char,int> enemy;
				enemy['x'] = i;
				enemy['y'] = j;

				enemies.push_back(enemy);
			}
		}
	}
