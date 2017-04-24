#ifndef IA_H
#define IA_H
#include <unordered_map>
#include "Board.h"

/*
	Classe qui embarque les différentes intelligences artificielles.
	Permet de jouer un tour automatiquement.

	Pour cela, la classe utilise l'instance Board qui lui permet d'avoir
	accès et de manipuler le plateau de jeu.
*/
class IA
{
	public:
		IA();
		IA(Board* p_board, int lvl);
		virtual ~IA();

		// Exécute la bonne IA selon le level
		void run(int player);

	private:
		// Pointeur vers l'instance du plateau de jeu. Permet de le manipuler
		Board* board;

		vector<Board*> tree;

		// Attribut qui définit le niveau de l'IA
		int level;

		// Intelligence artificielle n°1, en privé et appellé par run()
		void lvl_1(int player);

		// Intelligence artificielle n°2, en privé et appellé par run()
		void lvl_2(int player);

		// Algorithme permettant de calculer le coup le plus efficace pour l'IA n°2
		void minmax( multimap <int, Board>& _boardStates);

};

#endif // IA_H
