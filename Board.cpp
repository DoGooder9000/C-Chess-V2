#include <stdio.h>
#include "Piece.h"

class Board{
	public:
		const int width = 8;
		const int height = 8;

		int color = 0;

		int squares[64];
		
		Board(){
			squares[0] = Piece::Pawn | Piece::White;
		}
		~Board(){}


};
