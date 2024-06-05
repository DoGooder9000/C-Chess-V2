#pragma once

#include <stdio.h>
#include "Piece.h"

class Move{
    public:
        int start_index;
        int target_index;
        Piece* piece;

        Move(int start_index, int target_index, Piece* piece);
        ~Move();
};