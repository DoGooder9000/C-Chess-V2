#include <stdio.h>
#include "Includes/Piece.h"


Piece::Piece(int piecetype, int color){
	ID = piecetype | color;
}

Piece::~Piece(){}

int Piece::GetPieceID(){
	return ID;
}