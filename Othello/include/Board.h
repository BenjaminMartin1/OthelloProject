#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include "constants.h"

using namespace std;

//Structure pour définir le x et le y joué pour obtenir ce board
struct recordedMovePos
{
	int x;
	int y;
};

/*
	Classe qui modélise le plateau de jeu, et permet d'y effectuer
	les actions élémentaires propres aux pions :

	- Récupérer le contenu d'une cellule
	- Récupérer les positions possibles d'un joueur
	- Récupérer la liste des pions qui pourraient être mangés
	- Manger un pion
	- Ajouter un pion
*/
class Board
{
	public:
		Board();
		virtual ~Board();

		// Ajouter un pion à une case donnée
		bool move(int x, int y, int player);

		// Retourne la liste des cellules où le joueur peut se déplacer
		vector< map<char,int> > accessibles(int player);

		// Retourne la liste des pions qui peuvent être mangés
		vector< map<char,int> > eatables(int x_initial, int y_initial, int player);

		// Mange un pion : il le transforme en la couleur opposé
		bool eat(int x, int y);

		// Retourne le contenu d'une cellule
		int getCell(int x, int y);

		// Compte les pions d'un joueur
		int countPawns(int player);

		// Setter pour le score associé
		void setAssociatedScore(int _associatedScore);

		// Getter pour le score associé
		int getAssociatedScore();

		// Setter pour l'état précédent
		void setPreviousState(Board* _previousState);

		// Getter pour l'état précédent
		Board* getPreviousState();

		// Setter pour le move effectué
		void setRecordedMove(int _x, int _y);

		// Getter pour le move effectué
		recordedMovePos getRecordedMove();



	private:
		// Attributs
		int cells[8][8];
		//Score associé à l'état du board
		int associatedScore;
		//Renvoie à l'état précédent du board
		Board* previousState;
		//Initialization d'un objet de la structure
		recordedMovePos recordedMove;
};

#endif // BOARD_H
