#include <stdio.h>
#include "Piece.h"


Piece::Piece(int piecetype, int color){
	ID = piecetype | color;
}

Piece::~Piece(){}
