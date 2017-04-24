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


