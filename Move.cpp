#include "Includes/Move.h"

Move::Move(int start_index, int target_index, Piece* piece) : start_index(start_index), target_index(target_index), piece(piece) {
}

Move::~Move(){}