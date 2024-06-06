#pragma once

#include <stdio.h>
#include <array>

class Board;

class Piece{
	public:
		const static int None = 0;
		const static int Pawn = 1;
		const static int Knight = 2;
		const static int Bishop = 3;
		const static int Rook = 4;
		const static int Queen = 5;
		const static int King = 6;
		
		const static int White = 0;
		const static int Black = 8;

		int piecetype;
		int color;

		int index;

		Piece();
		Piece(int piecetype, int color, int index);
		Piece(const Piece& other);

		~Piece();

		std::array<int, 64> GetLegalMoves(Board* board);

		int GetPieceID();
		void Move(int new_index);

	private:
		int ID;	
};