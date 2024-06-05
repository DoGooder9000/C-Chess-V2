#include <stdio.h>
#include "Includes/Piece.h"

/*
Piece::Piece() : piecetype(None), color(White), index(-1), ID(None | White) {
	// Default constructor initializes to a "None" piece
}
*/

Piece::Piece(){}

Piece::Piece(int piecetype, int color, int index){
	piecetype = piecetype;
	color = color;

	index = index;

	ID = piecetype | color;
}

Piece::~Piece(){}

int Piece::GetPieceID(){
	return ID;
}

void Piece::Move(int new_index){
	index = new_index;
}