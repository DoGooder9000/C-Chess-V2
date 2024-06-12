#pragma once

#include "Board.h"

class Bot{
	public:
		int color;
		Board* board;

		int numPositions = 0;

		int PieceValues[7] = {0, 100, 300, 300, 500, 900, 0};

		int NegativeInfinity = -1000000;
		int PositiveInfinity = 1000000;


		Bot(int color, Board* board);

		Move GetMove(int depth);

		int NegaMax(int alpha, int beta, int depth);
		int Evaluate();
		std::list<Move> OrderMoves();
}; 