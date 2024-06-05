#pragma once

#include <stdio.h>


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
		~Piece();

		int GetPieceID();

	private:
		int ID;	
};