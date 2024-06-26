#include <stdio.h>
#include <algorithm>

#include "Includes/Board.h"
#include "Includes/Piece.h"

Board::Board(const char* FEN_String){
	GetBoardFromFEN(FEN_String);

	GenerateBitboards();
	GenerateColorBitboards();

	GenerateSquaresToEdge();
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
				if (square_index / 8 != 1){
					squares[square_index].moved = true;
				}
				fen_index++;
				square_index++;
				break;
			
			case 'P':
				squares[square_index] = Piece(Piece::Pawn, Piece::White, square_index);
				if (square_index / 8 != 6){
					squares[square_index].moved = true;
				}
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
				KingIndexes[1] = square_index;
				fen_index++;
				square_index++;
				break;
			
			case 'K':
				squares[square_index] = Piece(Piece::King, Piece::White, square_index);
				KingIndexes[0] = square_index;
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

	StorePositionAtHistoryIndex(HistoryIndex);

	if (HistoryIndex > MaxHistoryIndex){
		MaxHistoryIndex++;
	}


	/*

	First we move up to a free cell

	[pos0] [pos1] [pos2] [oldold] [ ]
									^
	
	Then we store the old postion

	[pos0] [pos1] [pos2] [oldold] [old]
									^

	We are now in a new position

	When we go back, we need to first load this new position at a new index, then go back

	When we go back, we load the old position at the current index

	[pos0] [pos1] [pos2] [oldold] [old]
									>

	And we go back one
	
	[pos0] [pos1] [pos2] [oldold] [future]
							^
	
	To go forward, we need to 
	*/

	// We need to save the position before we do the move

	DoublePawnPushIndex = -1;

	if (move.DoublePawnPush){
		DoublePawnPushIndex = move.target_index;
	}

	int target_piecetype, target_color;
	int start_piecetype = move.piece->piecetype;
	int start_color = move.piece->color;

	if (move.isEnPassant){
		if (move.piece->color == Piece::White){
			if (move.target_index - move.start_index == -9){ // Left En Passant
				squares[move.start_index-1] = Piece(Piece::None, Piece::White, move.start_index);
				target_piecetype = squares[move.start_index-1].piecetype;
				target_color = squares[move.start_index-1].color;
			}
			else{
				squares[move.start_index+1] = Piece(Piece::None, Piece::White, move.start_index); // Right En Passant
				target_piecetype = squares[move.start_index+1].piecetype;
				target_color = squares[move.start_index+1].color;
			}
		}
		else{
			if (move.target_index - move.start_index == 7){ // Left En Passant
				squares[move.start_index-1] = Piece(Piece::None, Piece::White, move.start_index);
				target_piecetype = squares[move.start_index-1].piecetype;
				target_color = squares[move.start_index-1].color;
			}
			else{
				squares[move.start_index+1] = Piece(Piece::None, Piece::White, move.start_index); // Right En Passant
				target_piecetype = squares[move.start_index+1].piecetype;
				target_color = squares[move.start_index+1].color;
			}
		}
	}

	else if(move.isCastle){
		target_piecetype = Piece::Rook;

		if (move.piece->color == Piece::White){
			target_color = 0;

			if (move.target_index == 62){
				squares[61] = squares[63];

				squares[63] = Piece(Piece::None, Piece::White, move.start_index);

				squares[61].MoveSelf(61);
			}

			else{
				squares[59] = squares[56];

				squares[56] = Piece(Piece::None, Piece::White, move.start_index);

				squares[59].MoveSelf(59);
			}
		}

		else{
			target_color = 8;

			if (move.target_index == 6){
				squares[5] = squares[7];

				squares[7] = Piece(Piece::None, Piece::White, move.start_index);

				squares[5].MoveSelf(5);
			}

			else{
				squares[3] = squares[0];

				squares[0] = Piece(Piece::None, Piece::White, move.start_index);

				squares[3].MoveSelf(3);
			}
		}
	}

	else{
		target_piecetype = squares[move.target_index].piecetype;
		target_color = squares[move.target_index].color;
	}

	if (move.PromotionPieceType != Piece::None){
		squares[move.start_index] = Piece(Piece::None, Piece::White, move.start_index);

		squares[move.target_index] = Piece(move.PromotionPieceType, start_color, move.target_index);
		squares[move.target_index].moved = true;

		PieceCount[move.piece->color/8][Piece::Pawn]--; //Refresh Pawn Counts

		PieceCount[move.piece->color/8][move.PromotionPieceType-1]++; // Refresh Promotion Piece Counts
	}

	else{

		squares[move.target_index] = *move.piece; // Set the target position on the board to the piece

		squares[move.target_index].MoveSelf(move.target_index); // Move the piece // Say the piece moved

		squares[move.start_index] = Piece(Piece::None, Piece::White, move.start_index); // Set the old position to blank

	}

	if (target_piecetype != Piece::None){
		PieceCount[target_color/8][target_piecetype-1]--; // Refresh captured Piece's Count
	}
	if (move.piece->piecetype == Piece::King){
		KingIndexes[move.piece->color/8] = move.target_index;
	}

	/**/
	GenerateColorBitboards();
	ChangeColor();
}

void Board::ChangeColor(){
	color = OppositeColor(color);
}

int Board::OppositeColor(int color){
	if (color == 0){return 8;}
	else{return 0;}
}

void Board::GenerateBitboards(){
	for (int k=0; k<64; k++){
		if (squares[k].piecetype != Piece::None){
			PieceCount[squares[k].color/8][squares[k].piecetype-1]++;
		}
	}
}

void Board::GenerateColorBitboards(){
	colorBitboards[0] = 0ULL;
	colorBitboards[1] = 0ULL;

	for (int k=0; k<size; k++){
		if (squares[k].piecetype != Piece::None){
			if (squares[k].color == Piece::White){ // j+1 is neccesary because the Pawn ID starts at 1. 0 means type None
				colorBitboards[0] |= (1ULL << k);
			}
			else{
				colorBitboards[1] |= (1ULL << k);
			}
		}
	}
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
	LoadPositionAtHistoryIndex(HistoryIndex);

	History[HistoryIndex] = UndoMove();

	HistoryIndex--;
}

void Board::BoardBack(){
	if (HistoryIndex >= 0){
		StorePositionAtHistoryIndex(HistoryIndex+1);

		LoadPositionAtHistoryIndex(HistoryIndex);

		HistoryIndex--;
	}
}

void Board::BoardForward(){
	if (HistoryIndex < MaxHistoryIndex){
		HistoryIndex++;

		LoadPositionAtHistoryIndex(HistoryIndex+1);
	}
}

void Board::LoadPositionAtHistoryIndex(int index){
	squares = History[index].squares;
	color = History[index].color;

	// Instead of saving the bitboards, you could just regenerate them, but that would take time.

	PieceCount[0] = History[index].PieceCount[0];
	PieceCount[1] = History[index].PieceCount[1];
	KingIndexes = History[index].KingIndexes;
	colorBitboards = History[index].colorBitboards;
	DoublePawnPushIndex = History[index].DoublePawnPushIndex;
}

void Board::StorePositionAtHistoryIndex(int index){
	History[index].color = color;
	History[index].squares = squares;
	History[index].PieceCount[0] = PieceCount[0];
	History[index].PieceCount[1] = PieceCount[1];
	History[index].KingIndexes = KingIndexes;
	History[index].colorBitboards = colorBitboards;
	History[index].DoublePawnPushIndex = DoublePawnPushIndex;
}

void Board::GenerateSquaresToEdge(){
	int X, Y;
	int DistanceUp, DistanceDown, DistanceLeft, DistanceRight;

	for (int j=0; j<size; j++){
		std::tie(X, Y) = BoardPosFromIndex(j);

		DistanceUp = Y;
		DistanceDown = 7-Y;
		DistanceLeft = X;
		DistanceRight = 7-X;

		for (int i=0; i<8; i++){
			switch (i)
			{
			case TopLeft:
				SquaresToEdge[j][i] = std::min(DistanceLeft, DistanceUp);
				break;
			
			case TopRight:
				SquaresToEdge[j][i] = std::min(DistanceRight, DistanceUp);
				break;

			case BottomLeft:
				SquaresToEdge[j][i] = std::min(DistanceLeft, DistanceDown);
				break;
			
			case BottomRight:
				SquaresToEdge[j][i] = std::min(DistanceRight, DistanceDown);
				break;
			
			case Up:
				SquaresToEdge[j][i] = DistanceUp;
				break;
			
			case Down:
				SquaresToEdge[j][i] = DistanceDown;
				break;
			
			case Left:
				SquaresToEdge[j][i] = DistanceLeft;
				break;
			
			case Right:
				SquaresToEdge[j][i] = DistanceRight;
				break;
			
			default:
				break;
			}
		}		
	}
}

Bitboard Board::GetAllAttackedSquares(int color){
	Bitboard attacked = 0ULL;

	for (int i=0; i<size; i++){
		if (squares[i].piecetype != Piece::None && squares[i].color == color){
			attacked |= GetPieceAttackedSquares(squares[i]);
		}
	}

	return attacked;
}

Bitboard Board::GetPieceAttackedSquares(Piece piece){
	if (piece.piecetype == Piece::Pawn){
		return piece.GetPawnAttacks(this, 0ULL| 1ULL << piece.index);
	}
	else if(piece.piecetype == Piece::King){
		return piece.KingAttackedSquares(this);
	}
	else{
		return Piece::MoveListToBitboard(piece.GetPseudoLegalMoves(this));
	}
}

bool Board::KingChecked(int color){
	return ((1ULL << KingIndexes[color/8]) & GetAllAttackedSquares(OppositeColor(color)))>0;
}

std::list<Move> Board::GetAllLegalMoves(int color){
	std::list<Move> allMoves;

	for (int i=0; i<64; i++){
		if (squares[i].color == color){
			allMoves.splice(allMoves.end(), squares[i].GetFullyLegalMoves(this));
		}
	}

	return allMoves;
}