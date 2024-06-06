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

	int castleRights;

	std::array<Bitboard, 6> bitboards[2];

	std::array<Bitboard, 2> colorBitboards;

}UndoMove;