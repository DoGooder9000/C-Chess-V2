#include <stdio.h>
#include <iostream>
#include <string>

#include "Includes/Board.h"
#include "Includes/Piece.h"

Board::Board(const char* FEN_String){
    int fen_index = 0;
	int square_index = 0;


	while (true){
		if (FEN_String[fen_index] == '\0'){break;}
		if (FEN_String[fen_index] == '/'){fen_index++; continue;}

		switch (FEN_String[fen_index])
		{
		case 'p':
			squares[square_index] = Piece::Pawn | Piece::Black;
			fen_index++;
			square_index++;
			break;
		
		case 'P':
			squares[square_index] = Piece::Pawn | Piece::White;
			fen_index++;
			square_index++;
			break;
		
		case 'n':
			squares[square_index] = Piece::Knight | Piece::Black;
			fen_index++;
			square_index++;
			break;
		
		case 'N':
			squares[square_index] = Piece::Knight | Piece::White;
			fen_index++;
			square_index++;
			break;

		case 'b':
			squares[square_index] = Piece::Bishop | Piece::Black;
			fen_index++;
			square_index++;
			break;
		
		case 'B':
			squares[square_index] = Piece::Bishop | Piece::White;
			fen_index++;
			square_index++;
			break;
		
		case 'r':
			squares[square_index] = Piece::Rook | Piece::Black;
			fen_index++;
			square_index++;
			break;
		
		case 'R':
			squares[square_index] = Piece::Rook | Piece::White;
			fen_index++;
			square_index++;
			break;

		case 'q':
			squares[square_index] = Piece::Queen | Piece::Black;
			fen_index++;
			square_index++;
			break;
		
		case 'Q':
			squares[square_index] = Piece::Queen | Piece::White;
			fen_index++;
			square_index++;
			break;
		
		case 'k':
			squares[square_index] = Piece::King | Piece::Black;
			fen_index++;
			square_index++;
			break;
		
		case 'K':
			squares[square_index] = Piece::King | Piece::White;
			fen_index++;
			square_index++;
			break;
		
		case '1':
			squares[square_index] = Piece::None;
			fen_index++;
			square_index++;
			break;
		
		case '2':
			for (int j=0; j<2; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;
		
		case '3':
			for (int j=0; j<3; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;

		case '4':
			for (int j=0; j<4; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;

		case '5':
			for (int j=0; j<5; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;

		case '6':
			for (int j=0; j<6; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;

		case '7':
			for (int j=0; j<7; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;


		case '8':
			for (int j=0; j<8; j++){
				squares[square_index] = Piece::None;
				square_index++;
			}
			fen_index++;
			break;


		default:
			break;
		}
	}
}

Board::~Board(){}

std::tuple<int, int> Board::BoardPosFromIndex(int index){
    return std::make_tuple(index % width, index / width);
}