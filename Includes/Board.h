#pragma once

#include <stdio.h>
#include <tuple>
#include "Piece.h"
#include "Move.h"
#include "Globals.h"

class Board;

class Board{
	public:
		const static int width = 8;
		const static int height = 8;
		const static int size = width*height;

		int color = 0;

		Piece squares[size];

		Bitboard bitboards[2][6]; // 2 Colors 6 types of pieces

		Board(const char* FEN_String);
		~Board();

		std::tuple<int, int> BoardPosFromIndex(int index);
		int IndexFromBoardPos(std::tuple<int, int> BoardPos);

		void MovePiece(Move move);

		void GenerateBitboards();
		Bitboard GenerateBitboard(int PieceID);
		void PrintBitboard(Bitboard bitboard);

		void GetBoardFromFEN(const char* FEN_String);
};