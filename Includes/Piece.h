#pragma once

#include <stdio.h>
#include <list>
#include <algorithm>
#include <cstdint>
#include <array>
#include <vector>
#include <iterator>

typedef uint64_t Bitboard;

class Board;
class Move;

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

		bool moved = false;

		Piece();
		Piece(int piecetype, int color, int index);
		Piece(const Piece& other);

		~Piece();

		std::list<Move> GetPseudoLegalMoves(Board* board);
		std::list<Move> GetFullyLegalMoves(Board* board);
		std::list<Move> KnightLegalMoves(Board* board);
		std::list<Move> RookLegalMoves(Board* board);
		std::list<Move> BishopLegalMoves(Board* board);
		std::list<Move> QueenLegalMoves(Board* board);
		std::list<Move> KingLegalMoves(Board* board);
		std::list<Move> PawnLegalMoves(Board* board);

		Bitboard KingAttackedSquares(Board* board);

		Bitboard GetPawnAttacks(Board* board, Bitboard selfBitboard);

		static Bitboard MoveListToBitboard(std::list<Move> moveList);

		int GetPieceID();
		void MoveSelf(int new_index);

	private:
		int ID;	
};