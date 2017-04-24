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


	// On récupère toutes les cases libres adjacentes à chacun des ennemis
	for (int i=0; i<enemies.size() ; i++)
	{

		// On répète l'opération de détection de la case adjacente les 4 directions
		for (int direction=0 ; direction<4 ; direction++)
		{
			// On règle le déplacement (steps x et y) selon la direction en cours
			switch (direction) {
				case 0: step_x=0;  step_y=-1; break;	// gauche
				case 1: step_x=-1; step_y=0;  break;	// haut
				case 2: step_x=0;  step_y=1;  break;	// droite
				case 3: step_x=1;  step_y=0;  break;	// bas
			}

			x = enemies[i]['x'] + step_x;
			y = enemies[i]['y'] + step_y;


			// Si la case est hors terrain, on coupe
			if (x<0 || x>7 || y<0 || y>7)
				continue;


			// Si la case n'est pas vide, on coupe
			if (cells[x][y] != CELL_EMPTY)
				continue;


			// Si la case a déjà été ajouté, on coupe
			bool already_added = false;

			for (int j=0 ; j<accessibles.size() ; j++)
			{
				if (accessibles[j]['x'] == x && accessibles[j]['y'] == y)
					already_added = true;
			}

			if (already_added)
				continue;


			// Si la case ne permet de manger des adversaires, on coupe
			if (eatables(x,y,player).size() == 0)
				continue;


			// Donc ici, tout a été validé. La case est jouable, on l'ajoute
			map<char,int> cell;
			cell['x'] = x;
			cell['y'] = y;

			accessibles.push_back(cell);
		}

	}

	return accessibles;
}



/*
	Retourne toutes les coordonnées des pièces adversaires qui peuvent être
	mangées, selon la position indiquée.
	Le retour est sous forme d'un vecteur de maps (clés x et y)
*/
vector< map<char,int> > Board::eatables(int x_initial, int y_initial, int player)
{

	std::vector< map<char,int> > eatables;
	int nb_enemies, x, y, step_x, step_y;
	bool friend_found;


	// On défini de quel type sont les cases amies
	int friend_cell	 = (player == PLAYER_WHITE) ? CELL_WHITE : CELL_BLACK;


	// On répétera l'opération de détection dans les 8 directions différentes
	for (int direction=0 ; direction<8 ; direction++)
	{

		// Initialisation des variables
		friend_found = false;
		nb_enemies 	 = 0;

		x = x_initial;
		y = y_initial;

		// On règle le déplacement (steps x et y) selon la direction en cours
		switch (direction) {
			case 0: step_x=0;  step_y=-1; break;	// gauche
			case 1: step_x=-1; step_y=-1; break;	// diagonale gauche haut
			case 2: step_x=-1; step_y=0;  break;	// haut
			case 3: step_x=-1; step_y=1;  break;	// diagonale haut droit
			case 4: step_x=0;  step_y=1;  break;	// droite
			case 5: step_x=1;  step_y=1;  break;	// diagonale bas droit
			case 6: step_x=1;  step_y=0;  break;	// bas
			case 7: step_x=1;  step_y=-1; break;	// diagonale bas gauche
		}


		// On parcourt le plateau dans la direction donnée jusqu'à atteindre la bordure
		while ( x >= 0 && x <= 7 && y >= 0 && y <= 7 )
		{
			// On se déplace
			x += step_x;
			y += step_y;

			// On est arrivé à l'ami, on stop notre déplacement
			if (cells[x][y] == friend_cell)
			{
				friend_found = true;
				break;
			}
			// On est arrivé à une case vide, il y a donc pas d'ami. Rien n'est eatable
			else if (cells[x][y] == CELL_EMPTY)
			{
				break;
			}
			// On est sur une case enemie
			else
			{
				nb_enemies++;
			}
		}


		// Si ami trouvé, on ajoute dans "eatables" tous les ennemis entre moi et l'ami
		if (friend_found)
		{
			// On se replace sur nous même
			x = x_initial;
			y = y_initial;

			// On se redéplace jusqu'à l'ami, donc en passant par tous les enemis
			for (int i=0 ; i<nb_enemies ; i++)
			{
				x += step_x;
				y += step_y;

				// On référence l'enemi sur lequel on est actuellement
				map<char,int> enemy;
				enemy['x'] = x;
				enemy['y'] = y;

				eatables.push_back(enemy);
			}
		}

	}

	return eatables;
}



/*
	Mange un pion : il le transforme en la couleur opposé
	Retourne true ou false
*/
bool Board::eat(int x, int y)
{
	// Vérification du non-dépassement des bordures
	if ( x<0 || x>7 || y <0 || y>7)
		return false;


	// Modification de la case
	switch (cells[x][y])
	{
		// Pion blanc sur la case
		case CELL_WHITE:
			cells[x][y] = CELL_BLACK;
			return true;
			break;

		// Pion noir sur la case
		case CELL_BLACK:
			cells[x][y] = CELL_WHITE;
			return true;
			break;

		// Case vide ou erronnée
		default:
			return false;
			break;
	}
}

/*
	 Setter pour le score associé
*/
void Board::setAssociatedScore(int _associatedScore)
{
	associatedScore = _associatedScore;
}

/*
	Getter pour le score associé
	Retourner le score associé
*/
int Board::getAssociatedScore()
{
	return associatedScore;
}


/*
Setter pour l'état précédent
*/
void Board::setPreviousState(Board* _previousState)
{
	previousState = _previousState;
}


/*
Getter pour l'état précédent
Retourner l'état précédent
*/
Board* Board::getPreviousState()
{
	return previousState;
}

/*
Setter pour le move effectué
*/
void Board::setRecordedMove(int _x, int _y)
{
	recordedMove.x = _x;
	recordedMove.y = _y;
}


/*
Getter pour le move effectué
Retourner le move effectué
*/
recordedMovePos Board::getRecordedMove()
{
	return recordedMove;
}

