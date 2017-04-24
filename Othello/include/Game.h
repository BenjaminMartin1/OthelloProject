#ifndef GAME_H
#define GAME_H

#include <string>
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

		// Affiche un message
		void displayMessage(string message);

		// Retourne true sur la partie est terminée, false sinon
		bool isOver();

		// Fais jouer l'humain
		void playHumain(int player);

		// Fais jouer l'IA
		void playIA(int level, int player);

		// Retourne le score d'un joueur
		int getScore(int player);

		// Retourne le gagnant
		int getWinner();


	private:

		// Instance du plateau de jeu, permet de le manipuler
		Board board;

		// Instance de l'intelligence artificelle, permet de l'exécuter
		IA ia;

		// Attribut qui définit le vainqueur
		int winner;

		// Stocker un message qui sera affiche avec display()
		string message;

};

#endif // GAME_H
