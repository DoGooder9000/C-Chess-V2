#include <stdio.h>
#include <cmath>
#include "Includes/Piece.h"
#include "Includes/Move.h"
#include "Includes/Board.h"


Piece::Piece() : piecetype(None), color(White), index(-1), ID(None | White) {}


Piece::Piece(int piecetype, int color, int index) : piecetype(piecetype), color(color), index(index), ID(piecetype|color){}

Piece::Piece(const Piece& other) : piecetype(other.piecetype), color(other.color), index(other.index), ID(other.ID){}


Piece::~Piece(){}

int Piece::GetPieceID(){
	return ID;
}

void Piece::MoveSelf(int new_index){
	index = new_index;
}

/*
REMEMBER SMALLEST BIT IS TOP LEFT. THAT IS WHERE THE ARRAY INDECIES START;


LSB -> 	00000000
		11111111
		11111111
		11111111
		11111111
		11111111
		11111111
		11111111 <- MSB
*/

Bitboard NotInAFile = 0xFEFEFEFEFEFEFEFE;
Bitboard NotInHFile = 0x7F7F7F7F7F7F7F7F;

Bitboard NotInFirstRank = 0xFFFFFFFFFFFFFF00;
Bitboard NotInEighthRank = 0x00FFFFFFFFFFFFFF;

Bitboard NotInFirstTwoRanks = 0xFFFFFFFFFFFF0000;
Bitboard NotInLastTwoRanks = 0x0000FFFFFFFFFFFF;

Bitboard NotInFirstTwoFiles = 0xFCFCFCFCFCFCFCFC;
Bitboard NotInLastTwoFiles = 0x3F3F3F3F3F3F3F3F;


Bitboard Piece::GetPseudoLegalMoves(Board* board){ // Pseudo Legal Moves (Moves not based on color) are fixed inside this function
	Bitboard selfBitboard = 0ULL; // A list of all squares the piece can move to. Starts with self inside.

	selfBitboard |= (1ULL << index);

	switch (piecetype)
	{
	case Knight:
		return KnightLegalMoves(selfBitboard) & (~board->colorBitboards[color/8]);
		break;

	case Rook:
		return RookLegalMoves(board, selfBitboard) & (~board->colorBitboards[color/8]);
		break;
	
	case Bishop:
		return BishopLegalMoves(board, selfBitboard) & (~board->colorBitboards[color/8]);
		break;
	
	case Queen:
		return QueenLegalMoves(board, selfBitboard) & (~board->colorBitboards[color/8]);
		break;

	case King:
		return KingLegalMoves(board, selfBitboard) & (~board->colorBitboards[color/8]);
		break;
	
	case Pawn:
		return PawnLegalMoves(board, selfBitboard) & (~board->colorBitboards[color/8]);
		break;
	
	default:
		break;
	}

	

	return selfBitboard;
}

Bitboard Piece::GetFullyLegalMoves(Board* board){
	Bitboard pseudo = GetPseudoLegalMoves(board);

	Bitboard finalLegalMoves = 0ULL;

	for (int i=0; i<64; i++){
		if ((pseudo & (1ULL << i)) > 0){
			Move move = Move(index, i, this, (piecetype == Piece::Pawn && (abs(i-index)%16 == 0)), (piecetype == Piece::Pawn && ((i-index)%8 != 0) && board->squares[i].piecetype == Piece::None));

			board->MovePiece(move);


			if (board->KingChecked(Board::OppositeColor(board->color))){;}

			else{finalLegalMoves |= 1ULL << i;}

			board->UndoBoardMove();
		}
	}

	return finalLegalMoves;
}

Bitboard Piece::RookLegalMoves(Board* board, Bitboard selfBitboard){
	Bitboard LegalMoves = 0ULL;

	for (int dir=0; dir<4; dir++){
		for (int step=0; step < board->SquaresToEdge[index][dir]; step++){
			// We are stepping through the squares	

			if (board->squares[index+(step+1)*board->DirectionsArray[dir]].piecetype == Piece::None){ // Self Index + (Step+1) * The amount that the index changes. Step +1 is neccesary because it starts on itself and needs to go one further
				LegalMoves |= (1ULL << index+(step+1)*board->DirectionsArray[dir]);
			}
			else{
				LegalMoves |= (1ULL << index+(step+1)*board->DirectionsArray[dir]);
				break;
			}
		}
	}

	return LegalMoves;
}

Bitboard Piece::BishopLegalMoves(Board* board, Bitboard selfBitboard){
	Bitboard LegalMoves = 0ULL;

	for (int dir=4; dir<8; dir++){
		for (int step=0; step < board->SquaresToEdge[index][dir]; step++){
			// We are stepping through the squares	

			if (board->squares[index+(step+1)*board->DirectionsArray[dir]].piecetype == Piece::None){ // Self Index + (Step+1) * The amount that the index changes. Step +1 is neccesary because it starts on itself and needs to go one further
				LegalMoves |= (1ULL << index+(step+1)*board->DirectionsArray[dir]);
			}
			else{
				LegalMoves |= (1ULL << index+(step+1)*board->DirectionsArray[dir]);
				break;
			}
		}
	}

	return LegalMoves;
}

Bitboard Piece::QueenLegalMoves(Board* board, Bitboard selfBitboard){
	Bitboard LegalMoves = 0ULL;

	for (int dir=0; dir<8; dir++){
		for (int step=0; step < board->SquaresToEdge[index][dir]; step++){
			// We are stepping through the squares	

			if (board->squares[index+(step+1)*board->DirectionsArray[dir]].piecetype == Piece::None){ // Self Index + (Step+1) * The amount that the index changes. Step +1 is neccesary because it starts on itself and needs to go one further
				LegalMoves |= (1ULL << index+(step+1)*board->DirectionsArray[dir]);
			}
			else{
				LegalMoves |= (1ULL << index+(step+1)*board->DirectionsArray[dir]);
				break;
			}
		}
	}

	return LegalMoves;
}

Bitboard Piece::KnightLegalMoves(Bitboard selfBitboard){
	Bitboard LegalMoves = 0ULL;

	if (((selfBitboard & NotInHFile) & NotInFirstTwoRanks) > 0){ 		// ##
		LegalMoves |= selfBitboard >> 15;								// #
	}																	// #

	if (((selfBitboard & NotInAFile) & NotInFirstTwoRanks) > 0){		// ##
		LegalMoves |= selfBitboard >> 17;								//  #
	}																	//  #

	if (((selfBitboard & NotInFirstTwoFiles) & NotInFirstRank) > 0){	// 
		LegalMoves |= selfBitboard >> 10;								// #
	}																	// ###

	if (((selfBitboard & NotInLastTwoFiles) & NotInFirstRank) > 0){		// 
		LegalMoves |= selfBitboard >> 6;								//   #
	}																	// ###


	if (((selfBitboard & NotInAFile) & NotInLastTwoRanks) > 0){ 		//  #
		LegalMoves |= selfBitboard << 15;								//  #
	}																	// ##

	if (((selfBitboard & NotInHFile) & NotInLastTwoRanks) > 0){			// #
		LegalMoves |= selfBitboard << 17;								// #
	}																	// ##

	if (((selfBitboard & NotInLastTwoFiles) & NotInEighthRank) > 0){	// 
		LegalMoves |= selfBitboard << 10;								// ###
	}																	//   #

	if (((selfBitboard & NotInFirstTwoFiles) & NotInEighthRank) > 0){	// 
		LegalMoves |= selfBitboard << 6;								// ###
	}																	// #

	return LegalMoves;
}

Bitboard Piece::KingLegalMoves(Board* board, Bitboard selfBitboard){
	Bitboard LegalMoves = 0ULL;

	int Directions[8] = {-1};

	if ((selfBitboard & NotInAFile) > 0){
		Directions[0] = 1;
	}
	if ((selfBitboard & NotInFirstRank) > 0){
		Directions[1] = 1;
	}
	if ((selfBitboard & NotInHFile) > 0){
		Directions[2] = 1;
	}
	if ((selfBitboard & NotInEighthRank) > 0){
		Directions[3] = 1;
	}
	if ((selfBitboard & NotInAFile & NotInFirstRank) > 0){
		Directions[4] = 1;
	}
	if ((selfBitboard & NotInFirstRank & NotInHFile) > 0){
		Directions[5] = 1;
	}
	if ((selfBitboard & NotInHFile & NotInEighthRank) > 0){
		Directions[6] = 1;
	}
	if ((selfBitboard & NotInEighthRank & NotInAFile) > 0){
		Directions[7] = 1;
	}

	for (int dir=0; dir<8; dir++){
		if (Directions[dir] > 0){
			LegalMoves |= (1ULL << index+board->DirectionsArray[dir]);
		}

	}

	return LegalMoves;
}

Bitboard Piece::PawnLegalMoves(Board* board, Bitboard selfBitboard){
	Bitboard LegalMoves = 0ULL;

	if (color == Piece::White){
		if (!moved && board->squares[index-8].piecetype == Piece::None && board->squares[index-16].piecetype == Piece::None){ // Double Pawn Pushes
			LegalMoves |= (selfBitboard >> 16);
		}

		if (board->squares[index-8].piecetype == Piece::None){ // Single Pawn Pushes
			LegalMoves |= (selfBitboard >> 8);
		}

		if (board->squares[index-9].piecetype != Piece::None){
			LegalMoves |= (selfBitboard >> 9);
		}

		if (board->squares[index-7].piecetype != Piece::None){
			LegalMoves |= (selfBitboard >> 7);
		}

		if (board->DoublePawnPushIndex != -1){
			if (index+1 == board->DoublePawnPushIndex){
				LegalMoves |= (selfBitboard >> 7);
			}
			else if (index-1 == board->DoublePawnPushIndex){
				LegalMoves |= (selfBitboard >> 9);
			}
		}
	}

	else{
		if (!moved && board->squares[index+8].piecetype == Piece::None && board->squares[index+16].piecetype == Piece::None){
			LegalMoves |= (selfBitboard << 16);
		}

		if (board->squares[index+8].piecetype == Piece::None){
			LegalMoves |= (selfBitboard << 8);
		}

		if (board->squares[index+9].piecetype != Piece::None){
			LegalMoves |= (selfBitboard << 9);
		}

		if (board->squares[index+7].piecetype != Piece::None){
			LegalMoves |= (selfBitboard << 7);
		}

		if (board->DoublePawnPushIndex != -1){
			if (index+1 == board->DoublePawnPushIndex){
				LegalMoves |= (selfBitboard << 9);
			}
			else if (index-1 == board->DoublePawnPushIndex){
				LegalMoves |= (selfBitboard << 7);
			}
		}
	}
	
	return LegalMoves;
}

Bitboard Piece::GetPawnAttacks(Board* board, Bitboard selfBitboard){
	Bitboard attacked = 0ULL;

	if (color == Piece::White){
		if ((selfBitboard & NotInAFile) > 0){ attacked |= (selfBitboard >> 9);}
		if ((selfBitboard & NotInHFile) > 0){ attacked |= (selfBitboard >> 7);}
	}

	else{
		if ((selfBitboard & NotInAFile) > 0){ attacked |= (selfBitboard << 7);}
		if ((selfBitboard & NotInHFile) > 0){ attacked |= (selfBitboard << 9);}
	}
	
	return attacked;
}