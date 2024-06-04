#pragma once

#include <stdio.h>
#include "Piece.h"

class Board{
	public:
		const static int width = 8;
		const static int height = 8;

		int color = 0;

		int squares[64];

		Board();
		~Board();
};