#include <stdio.h>

#include "Includes/Board.h"
#include "Includes/Piece.h"

Board::Board(){
    for (int i=0; i < size; i++){
        squares[i] = Piece::None;
    }
    squares[0] = Piece::Pawn | Piece::White;
}

Board::~Board(){}

std::tuple<int, int> Board::BoardPosFromIndex(int index){
    return std::make_tuple(index / width, index % width);
}