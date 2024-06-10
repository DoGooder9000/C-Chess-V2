#pragma once

#include <stdio.h>
#include "Piece.h"

class Move{
	public:
		int start_index;
		int target_index;
		Piece* piece;
		bool DoublePawnPush;
		bool isEnPassant;
		bool isCastle;
		int PromotionPieceType;

		Move();
		Move(Move const& other);
		Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant);
		Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant, bool isCastle);
		Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant, bool isCastle, int PromotionPieceType);
		~Move();

		bool operator==(const Move& other);

		void Print();

		static char* GetReadableIndex(int index);
};