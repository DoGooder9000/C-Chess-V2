#pragma once

#include <stdio.h>
#include <cstdint>
#include <array>

typedef uint64_t Bitboard;

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

		Bitboard GetLegalMoves(Board* board);
		Bitboard KnightLegalMoves(Bitboard selfBitboard);

		int GetPieceID();
		void Move(int new_index);

	private:
		int ID;	
};