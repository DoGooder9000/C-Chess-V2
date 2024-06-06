#pragma once

#include <stdio.h>
#include <tuple>
#include <array>
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

		std::array<Piece, size> squares;

		std::array<Bitboard, 6> bitboards[2]; // All pieces of both colors
		std::array<Bitboard, 2> colorBitboards; // One for all pieces of the color

		UndoMove History[MAX_CHESS_MOVES];
		int HistoryIndex = -1; // Start at -1 because we will increment at the start of the MovePiece function.

		int castleRights; // WK is 1, WQ is 2, BK is 4, BQ is 8

		Board(const char* FEN_String);
		~Board();
		
		void GetBoardFromFEN(const char* FEN_String);

		static std::tuple<int, int> BoardPosFromIndex(int index);
		static int IndexFromBoardPos(std::tuple<int, int> BoardPos);

		void GenerateBitboards();
		void GenerateColorBitboards();
		Bitboard GenerateBitboard(int PieceID);
		static void PrintBitboard(Bitboard bitboard);


		void MovePiece(Move move);
		void UndoBoardMove();

};