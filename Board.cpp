#include <stdio.h>

#include "Includes/Board.h"
#include "Includes/Piece.h"

Board::Board(){
    squares[0] = Piece::Pawn | Piece::White;
}

Board::~Board(){}