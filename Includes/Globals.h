#pragma once

#include <stdio.h>
#include <cstdint>
#include <array>

#include "Piece.h"

#define MAX_CHESS_MOVES 512

typedef uint64_t Bitboard;

// Enums

enum Pieces { None, Pawn, Knight, Bishop, Rook, Queen, King };
//	  0		1	  2		  3		  4		5	   6

enum Colors { White = 0, Black = 8 };

enum CastleRights { WK = 1, WQ = 2, BK = 4, BQ = 8 };


typedef struct UndoMove{
	int color;

	std::array<Piece, 64> squares;

	std::array<int, 6> PieceCount[2];

	std::array<int, 2> KingIndexes;

	std::array<Bitboard, 2> colorBitboards;

	int DoublePawnPushIndex;

}UndoMove;