#include <stdio.h>

#include "Includes/Board.h"
#include "Includes/Piece.h"

Board::Board(const char* FEN_String){
	GetBoardFromFEN(FEN_String);

	GenerateBitboards();
}

Board::~Board(){}

void Board::GetBoardFromFEN(const char* FEN_String){
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

std::tuple<int, int> Board::BoardPosFromIndex(int index){
	return std::make_tuple(index % width, index / width);
}

int Board::IndexFromBoardPos(std::tuple<int, int> BoardPos){
	int x, y;

	std::tie(x, y) = BoardPos;

	return y*width+x;
}

void Board::MovePiece(Move move){
	HistoryIndex++;

	History[HistoryIndex].color = color;
	History[HistoryIndex].squares = squares;

	// We need to save the position before we do the move

	squares[move.target_index] = *move.piece; // Set the target position on the board to the piece

	squares[move.target_index].Move(move.target_index);

	squares[move.start_index] = Piece(Piece::None, Piece::White, move.start_index); // Set the old position to black

	GenerateBitboard(move.piece->GetPieceID());

	if (squares[move.target_index].piecetype != Piece::None){
		GenerateBitboard(squares[move.target_index].GetPieceID());
	}
}

void Board::GenerateBitboards(){

	for (int i=0; i<2; i++){
		for (int j=0; j<6; j++){
			bitboards[i][j] = 0ULL;

			for (int k=0; k<size; k++){
				if (squares[k].GetPieceID() == (i*8)+(j+1)){ // j+1 is neccesary because the Pawn ID starts at 1. 0 means type None
					bitboards[i][j] |= (1ULL << k);
				}
			}
		}
	}
}

Bitboard Board::GenerateBitboard(int PieceID){
	Bitboard bitboard = 0ULL;

	for (int k=0; k<size; k++){
		if (squares[k].GetPieceID() == PieceID){ // j+1 is neccesary because the Pawn ID starts at 1. 0 means type None
			bitboard |= (1ULL << k);
		}
	}

	return bitboard;
}

void Board::PrintBitboard(Bitboard bitboard){
	int index;

	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			index = i*8 + j;

			if (bitboard & (1ULL << index)){printf("1 ");}
			else{printf(". ");}
		}
		printf("\n");
	}
	printf("\n");
}

void Board::UndoBoardMove(){
	squares = History[HistoryIndex].squares;
	color = History[HistoryIndex].color;
	castleRights = History[HistoryIndex].castleRights;


	History[HistoryIndex] = UndoMove();

	HistoryIndex--;

}