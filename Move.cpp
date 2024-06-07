#include "Includes/Move.h"

Move::Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant) : start_index(start_index), target_index(target_index), piece(piece), 
DoublePawnPush(DoublePawnPush), isEnPassant(isEnPassant) {}

Move::Move(){}

Move::~Move(){}