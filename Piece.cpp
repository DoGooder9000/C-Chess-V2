#include <stdio.h>
#include "Includes/Piece.h"
#include "Includes/Board.h"


Piece::Piece() : piecetype(None), color(White), index(-1), ID(None | White) {}


Piece::Piece(int piecetype, int color, int index) : piecetype(piecetype), color(color), index(index), ID(piecetype|color){}

Piece::Piece(const Piece& other) : piecetype(other.piecetype), color(other.color), index(other.index), ID(other.ID){}


Piece::~Piece(){}

int Piece::GetPieceID(){
	return ID;
}

void Piece::Move(int new_index){
	index = new_index;
}

std::array<int, 64> Piece::GetLegalMoves(Board* board){
	std::array<int, 64> LegalMoves = { -1 }; // A list of all squares the piece can move to

	return LegalMoves;
}