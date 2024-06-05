#pragma once

#include <stdio.h>
#include <tuple>
#include "Piece.h"

class Board;

class Board{
	public:
		const static int width = 8;
		const static int height = 8;
		const static int size = width*height;

		int color = 0;

		Piece squares[size];

		Board(const char* FEN_String);
		~Board();

		std::tuple<int, int> BoardPosFromIndex(int index);
		int IndexFromBoardPos(std::tuple<int, int> BoardPos);
};