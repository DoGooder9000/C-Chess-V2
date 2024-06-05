#pragma once

#include <stdio.h>
#include <tuple>
#include "Piece.h"

class Board{
	public:
		const static int width = 8;
		const static int height = 8;
		const static int size = width*height;

		int color = 0;

		int squares[size];

		Board(const char* FEN_String);
		~Board();

		std::tuple<int, int> BoardPosFromIndex(int index);
};