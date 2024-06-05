#include <stdio.h>
#include <cstdint>

#include "Includes/Board.h"
#include "Includes/Piece.h"

typedef uint64_t Bitboard;

Board::Board(const char* FEN_String){
	int fen_index = 0;
	int square_index = 0;


	while (true){
		if (FEN_String[fen_index] == '\0'){break;}
		if (FEN_String[fen_index] == '/'){fen_index++; continue;}

		switch (FEN_String[fen_index]){
			case 'p':
				squares[square_index] = Piece(Piece::Pawn, Piece::Black, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'P':
				squares[square_index] = Piece(Piece::Pawn, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'n':
				squares[square_index] = Piece(Piece::Knight, Piece::Black, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'N':
				squares[square_index] = Piece(Piece::Knight, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;

			case 'b':
				squares[square_index] = Piece(Piece::Bishop, Piece::Black, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'B':
				squares[square_index] = Piece(Piece::Bishop, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'r':
				squares[square_index] = Piece(Piece::Rook, Piece::Black, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'R':
				squares[square_index] = Piece(Piece::Rook, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;

			case 'q':
				squares[square_index] = Piece(Piece::Queen, Piece::Black, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'Q':
				squares[square_index] = Piece(Piece::Queen, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'k':
				squares[square_index] = Piece(Piece::King, Piece::Black, square_index);
				fen_index++;
				square_index++;
				break;
			
			case 'K':
				squares[square_index] = Piece(Piece::King, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;
			
			case '1':
				squares[square_index] = Piece(Piece::None, Piece::White, square_index);
				fen_index++;
				square_index++;
				break;
			
			case '2':
				for (int j=0; j<2; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
					square_index++;
				}
				fen_index++;
				break;
			
			case '3':
				for (int j=0; j<3; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
					square_index++;
				}
				fen_index++;
				break;

			case '4':
				for (int j=0; j<4; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
					square_index++;
				}
				fen_index++;
				break;

			case '5':
				for (int j=0; j<5; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
					square_index++;
				}
				fen_index++;
				break;

			case '6':
				for (int j=0; j<6; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
					square_index++;
				}
				fen_index++;
				break;

			case '7':
				for (int j=0; j<7; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
					square_index++;
				}
				fen_index++;
				break;


			case '8':
				for (int j=0; j<8; j++){
					squares[square_index] = Piece(Piece::None, Piece::White, square_index);
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

int Board::IndexFromBoardPos(std::tuple<int, int> BoardPos){
	int x, y;

	std::tie(x, y) = BoardPos;

	return y*width+x;
}

void Board::MovePiece(Move move){
	printf("start: %d target: %d piece: %d\n", move.start_index, move.target_index, move.piece->piecetype);

	squares[move.target_index] = *move.piece; // Set the target position on the board to the piece

	squares[move.target_index].Move(move.target_index);

	//move.piece->Move(move.target_index); // Move the piece internal (inside itself)

	squares[move.start_index] = Piece(Piece::None, Piece::White, move.start_index); // Set the old position to black
}