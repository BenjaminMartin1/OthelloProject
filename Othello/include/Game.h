#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "IA.h"

class Game
{
	public:
		Game();
		virtual ~Game();

		// Réinitialise une partie
		void reset();

		// Affiche le tableau de jeu
		void display();

		// Retourne true sur la partie est terminée, false sinon
		bool isOver();

		// Fais jouer l'humain
		void playHumain();

		// Fais jouer l'IA
		void playIA();


	private:

		// Instance du plateau de jeu, permet de le manipuler
		Board board;

		// Instance de l'intelligence artificelle, permet de l'exécuter
		IA ia;

		// Attribut qui définit le vainqueur
		int winner;


};

#endif // GAME_H
