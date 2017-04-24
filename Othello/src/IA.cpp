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


/*
	Intelligence artificielle level 2
	Utilise la classe Board pour placer un pion
*/
void IA::lvl_2()
{
	//Détermine le joueur actuellement en train de jouer l'état du plateau pour l'algorithme
	int currentPlayer = 0;

	//Multi-map permettant de combiner les états futures et leurs profondeur en 1 seul conteneur
	multimap<int, Board> boardStates;

	//Itérateur utilisée pour trouver les états d'une profondeur particulière
	pair<multimap<int, Board>::iterator, multimap<int, Board>::iterator> depthPosition;

	//Insertion du plateau actuelle à la profondeur 0
	boardStates.insert(pair<int, Board>(0, *board));

	//Reinitialisation de l'état précédent à NULL pour l'état de départ
	(*boardStates.equal_range(0).first).second.setPreviousState(NULL);

	//On parcourt une profondeur de 5
	for (int j = 0; j < 4; j++)
	{
		//On détermine en fonction de la profondeur quel joueur est actuellement en train de jouer
		if (j % 2 != 0) { currentPlayer = PLAYER_WHITE; }
		else { currentPlayer = PLAYER_BLACK; }

		//Insertion inutile qui est seulement faite pour délimiter la fonction equal_range du multimap
		boardStates.insert(pair<int, Board>(j + 1, *board));

		//Détermination de la position de départ d'une certaine profondeur pour l'itérateur de parcourt
		depthPosition = boardStates.equal_range(j);

		//Parcours de tout les états de la profondeur déterminée précédemment
		for (multimap<int, Board>::iterator it = depthPosition.first; it != depthPosition.second; ++it)
		{
			//Evaluation de toutes les positions actuelles
			vector< map<char, int> > availablePos = (*it).second.accessibles(currentPlayer);

			//Pour chaque coup possible dans l'état actuel
			for (int i = 0; i < (*it).second.accessibles(currentPlayer).size(); i++)
			{
				//Création d'un nouvel état
				Board tempBoardState = (*it).second;

				//On lui associe comme score le nombre de pions renversé quand le coup est joué
				tempBoardState.setAssociatedScore(tempBoardState.eatables(availablePos[i]['x'], availablePos[i]['y'], currentPlayer).size());

				//On joue le coup
				tempBoardState.move(availablePos[i]['x'], availablePos[i]['y'], currentPlayer);

				//On enregistre la position du coup joué pour cet état
				tempBoardState.setRecordedMove(availablePos[i]['x'], availablePos[i]['y']);

				//On enregistre l'état précedent dans un pointeur
				tempBoardState.setPreviousState(&(*it).second);

				//Puis on l'ajoute à une profondeur plus basse
				boardStates.insert(pair<int, Board>(j + 1, tempBoardState));
			}
		}
		//Destruction de l'insertion inutile faite auparavant
		boardStates.erase(depthPosition.second);
	}

	//Utilisation du minmax pour déterminé le meilleur coup
	minmax(boardStates);

	//On se place à la profondeur 1
	depthPosition = boardStates.equal_range(1);

	//Remplissage d'un vecteur de Board pour l'affichage de l'arbre sur le côté du jeu
	for (multimap<int, Board>::iterator it = depthPosition.first; it != depthPosition.second; ++it)
	{
		tree.push_back(&(*it).second);
	}

}

/*
Algorithme déterminant le meilleur coup pour l'IA
Utilise la classe Board pour placer un pion
Utilise une multimap en paramètre pour récupérer les états futurs
*/
void IA::minmax(multimap<int, Board> &_boardStates)
{
	int i = 0;

	//Etat resultat final choisi
	Board* nodeResult = NULL;

	//Etat de parcours pour remonter le graphe
	Board* temp;

	//Itérateur de position en profondeur
	pair<multimap<int, Board>::iterator, multimap<int, Board>::iterator> depthPosition;

	//On part de la profondeur la plus basse
	depthPosition = _boardStates.equal_range(4);

	//Valeur maximale associé à l'état choisi
	int maxValue = 0;

	//Parcours de tout les états de la profondeur déterminé précédement
	for (multimap<int, Board>::iterator it = depthPosition.first; it != depthPosition.second; ++it)
	{
		i = 0;
		temp = &(*it).second;

		//Temps que nous ne sommes pas à la profondeur 0
		while(temp->getPreviousState() != NULL)
		{
			//On descend d'une profondeur
			temp = temp->getPreviousState();

			//L'IA joue un tour sur deux
			if (i % 2 == 0)
			{
				//Quand l'IA joue, le score acquierit est bénéfique donc on ajoute
				(*it).second.setAssociatedScore((*it).second.getAssociatedScore() + temp->getAssociatedScore());
			}
			else
			{
				//Quand l'humain joue, le score acquierit est mauvaix pour l'IA donc on le soustrait
				(*it).second.setAssociatedScore((*it).second.getAssociatedScore() - temp->getAssociatedScore());
			}

			//Changement de tour
			i++;

			//Si on est a la profondeur 2, soit un coup après l'état de départ, on enregistre les coordonnées du coup dans l'état du quelle on est partie
			if ((temp->getPreviousState() != NULL) && temp->getPreviousState()->getPreviousState() == NULL)
			{
				(*it).second.setRecordedMove(temp->getRecordedMove().x, temp->getRecordedMove().y);
			}
		}

		//Si le score associé à l'état du quel on est parti est plus forte que maxValue
		if ((*it).second.getAssociatedScore() > maxValue)
		{
			//Alors on affecte maxValue à ce score
			maxValue = (*it).second.getAssociatedScore();
			//Et on associe le noeud choisie à cette état
			nodeResult = &(*it).second;
		}

	}
	//Finalement, on effectue le coup de l'IA avec le noeud choisi
	board->move(nodeResult->getRecordedMove().x, nodeResult->getRecordedMove().y, PLAYER_BLACK);
}
