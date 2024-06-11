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
	moved = true;
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


std::list<Move> Piece::GetPseudoLegalMoves(Board* board){ // Pseudo Legal Moves (Moves not based on color) are fixed inside this function
	switch (piecetype)
	{
	case Knight:
		return KnightLegalMoves(board);
		break;

	case Rook:
		return RookLegalMoves(board);
		break;
	
	case Bishop:
		return BishopLegalMoves(board);
		break;
	
	case Queen:
		return QueenLegalMoves(board);
		break;

	case King:
		return KingLegalMoves(board);
		break;
	
	case Pawn:
		return PawnLegalMoves(board);
		break;
	
	default:
		std::list<Move> _;
		return _;		
		break;
	}
}

std::list<Move> Piece::GetFullyLegalMoves(Board* board){
	std::list<Move> pseudoLegalMoves = GetPseudoLegalMoves(board);
	std::list<Move> finalLegalMoves;

	for (Move move : pseudoLegalMoves){
		board->MovePiece(move);

		if (board->KingChecked(Board::OppositeColor(board->color))){;}
		else{finalLegalMoves.push_back(move);}

		board->UndoBoardMove();
	}

	return finalLegalMoves;
}

Bitboard Piece::MoveListToBitboard(std::list<Move> moveList){
	Bitboard bitboard = 0ULL;

	for (auto it = moveList.begin(); it != moveList.end(); ++it){
		bitboard |= (1ULL << it->target_index);
	}

	return bitboard;
}

std::list<Move> Piece::RookLegalMoves(Board* board){
	std::list<Move> LegalMoves;

	for (int dir=0; dir<4; dir++){
		for (int step=0; step < board->SquaresToEdge[index][dir]; step++){
			// We are stepping through the squares	

			if (board->squares[index+(step+1)*board->DirectionsArray[dir]].piecetype == Piece::None){ // Self Index + (Step+1) * The amount that the index changes. Step +1 is neccesary because it starts on itself and needs to go one further
				LegalMoves.push_back(Move(index, index+(step+1)*board->DirectionsArray[dir], this, false, false)); // Blank Square
			}
			else{
				if (board->squares[index+(step+1)*board->DirectionsArray[dir]].color != color){
					LegalMoves.push_back(Move(index, index+(step+1)*board->DirectionsArray[dir], this, false, false));
				}
				break;
			}
		}
	}

	//if (index == 31){
	//	board->PrintBitboard(MoveListToBitboard(LegalMoves));
	//}

	return LegalMoves;
}

std::list<Move> Piece::BishopLegalMoves(Board* board){
	std::list<Move> LegalMoves;

	for (int dir=4; dir<8; dir++){
		for (int step=0; step < board->SquaresToEdge[index][dir]; step++){
			// We are stepping through the squares	

			if (board->squares[index+(step+1)*board->DirectionsArray[dir]].piecetype == Piece::None){ // Self Index + (Step+1) * The amount that the index changes. Step +1 is neccesary because it starts on itself and needs to go one further
				LegalMoves.push_back(Move(index, index+(step+1)*board->DirectionsArray[dir], this, false, false));
			}
			else{
				if (board->squares[index+(step+1)*board->DirectionsArray[dir]].color != color){
					LegalMoves.push_back(Move(index, index+(step+1)*board->DirectionsArray[dir], this, false, false));
				}
				break;
			}
		}
	}

	return LegalMoves;
}

std::list<Move> Piece::QueenLegalMoves(Board* board){
	std::list<Move> LegalMoves;

	for (int dir=0; dir<8; dir++){
		for (int step=0; step < board->SquaresToEdge[index][dir]; step++){
			// We are stepping through the squares	

			if (board->squares[index+(step+1)*board->DirectionsArray[dir]].piecetype == Piece::None){ // Self Index + (Step+1) * The amount that the index changes. Step +1 is neccesary because it starts on itself and needs to go one further
				LegalMoves.push_back(Move(index, index+(step+1)*board->DirectionsArray[dir], this, false, false));
			}
			else{
				if (board->squares[index+(step+1)*board->DirectionsArray[dir]].color != color){
					LegalMoves.push_back(Move(index, index+(step+1)*board->DirectionsArray[dir], this, false, false));
				}
				break;
			}
		}
	}

	return LegalMoves;
}

std::list<Move> Piece::KnightLegalMoves(Board* board){
	Bitboard selfBitboard = 0ULL | (1ULL << index);

	Bitboard notSameColor = ~board->colorBitboards[color/8];

	std::list<Move> LegalMoves;

	if (((selfBitboard & NotInHFile) & NotInFirstTwoRanks) > 0 && ((selfBitboard >> 15) & notSameColor) > 0){ 		// ##
		LegalMoves.push_back(Move(index, index-15, this, false, false));											// #
	}																												// #

	if (((selfBitboard & NotInAFile) & NotInFirstTwoRanks) > 0 && ((selfBitboard >> 17) & notSameColor) > 0){		// ##
		LegalMoves.push_back(Move(index, index-17, this, false, false));											//  #
	}																												//  #

	if (((selfBitboard & NotInFirstTwoFiles) & NotInFirstRank) > 0 && ((selfBitboard >> 10) & notSameColor) > 0){	// 
		LegalMoves.push_back(Move(index, index-10, this, false, false));											// #
	}																												// ###

	if (((selfBitboard & NotInLastTwoFiles) & NotInFirstRank) > 0 && ((selfBitboard >> 6) & notSameColor) > 0){		// 
		LegalMoves.push_back(Move(index, index-6, this, false, false));												//   #
	}																												// ###


	if (((selfBitboard & NotInAFile) & NotInLastTwoRanks) > 0 && ((selfBitboard << 15) & notSameColor) > 0){ 		//  #
		LegalMoves.push_back(Move(index, index+15, this, false, false));											//  #
	}																												// ##

	if (((selfBitboard & NotInHFile) & NotInLastTwoRanks) > 0 && ((selfBitboard << 17) & notSameColor) > 0){		// #
		LegalMoves.push_back(Move(index, index+17, this, false, false));											// #
	}																												// ##

	if (((selfBitboard & NotInLastTwoFiles) & NotInEighthRank) > 0 && ((selfBitboard << 10) & notSameColor) > 0){	// 
		LegalMoves.push_back(Move(index, index+10, this, false, false));											// ###
	}																												//   #

	if (((selfBitboard & NotInFirstTwoFiles) & NotInEighthRank) > 0 && ((selfBitboard << 6) & notSameColor) > 0){	// 
		LegalMoves.push_back(Move(index, index+6, this, false, false));												// ###
	}																												// #

	return LegalMoves;
}

std::list<Move> Piece::KingLegalMoves(Board* board){
	std::list<Move> LegalMoves;

	Bitboard selfBitboard = 0ULL | (1ULL << index);

	Bitboard notSameColor = ~board->colorBitboards[color/8];

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
			if (board->squares[index+board->DirectionsArray[dir]].piecetype == Piece::None || board->squares[index+board->DirectionsArray[dir]].color != color){
				LegalMoves.push_back(Move(index, index+board->DirectionsArray[dir], this, false, false));
			}
		}

	}

	if (!moved && !board->KingChecked(color)){
		if (color == 0){
			if (board->squares[63].piecetype == Piece::Rook && board->squares[63].moved == false){ // King Side Castle
				if (board->squares[61].piecetype == Piece::None && board->squares[62].piecetype == Piece::None){
					Bitboard attackedSquares = board->GetAllAttackedSquares(Piece::Black);
					Bitboard movingTo = 0ULL | (1ULL << 61) | (1ULL << 62);

					if ((attackedSquares & movingTo) > 0){}
					else{LegalMoves.push_back(Move(index, 62, this, false, false, true));}
				}
			}
			if (board->squares[63].piecetype == Piece::Rook && board->squares[63].moved == false){ // Queen Side
				if (board->squares[57].piecetype == Piece::None && board->squares[58].piecetype == Piece::None && board->squares[59].piecetype == Piece::None){
					Bitboard attackedSquares = board->GetAllAttackedSquares(Piece::Black);
					Bitboard movingTo = 0ULL | (1ULL << 58) | (1ULL << 59);

					if ((attackedSquares & movingTo) > 0){}
					else{LegalMoves.push_back(Move(index, 58, this, false, false, true));}
				}
			}
		}
		else{
			if (board->squares[7].piecetype == Piece::Rook && board->squares[7].moved == false){ // King Side
				if (board->squares[5].piecetype == Piece::None && board->squares[6].piecetype == Piece::None){
					Bitboard attackedSquares = board->GetAllAttackedSquares(Piece::White);
					Bitboard movingTo = 0ULL | (1ULL << 5) | (1ULL << 6);

					if ((attackedSquares & movingTo) > 0){}
					else{LegalMoves.push_back(Move(index, 6, this, false, false, true));}
					
				}
			}
			if (board->squares[0].piecetype == Piece::Rook && board->squares[0].moved == false){ // Queen Side
				if (board->squares[1].piecetype == Piece::None && board->squares[2].piecetype == Piece::None && board->squares[3].piecetype == Piece::None){
					Bitboard attackedSquares = board->GetAllAttackedSquares(Piece::White);
					Bitboard movingTo = 0ULL | (1ULL << 2) | (1ULL << 3);

					if ((attackedSquares & movingTo) > 0){}
					else{LegalMoves.push_back(Move(index, 2, this, false, false, true));}
				}
			}
		}
	}

	return LegalMoves;
}

Bitboard Piece::KingAttackedSquares(Board* board){
	Bitboard attacked;

	Bitboard selfBitboard = 0ULL | (1ULL << index);

	Bitboard notSameColor = ~board->colorBitboards[color/8];

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
			if (board->squares[index+board->DirectionsArray[dir]].piecetype == Piece::None || board->squares[index+board->DirectionsArray[dir]].color != color){
				attacked |= (1ULL << index+board->DirectionsArray[dir]);
			}
		}

	}

	return attacked;
}

std::list<Move> Piece::PawnLegalMoves(Board* board){
	std::list<Move> LegalMoves;

	Bitboard selfBitboard = 0ULL | (1ULL << index);

	if (color == Piece::White){
		if (!moved && board->squares[index-8].piecetype == Piece::None && board->squares[index-16].piecetype == Piece::None){ // Double Pawn Pushes
			LegalMoves.push_back(Move(index, index-16, this, true, false));
		}

		if (board->squares[index-8].piecetype == Piece::None){ // Single Pawn Pushes
			if (index/8 != 1){
				LegalMoves.push_back(Move(index, index-8, this, false, false));
			}
			else{
				LegalMoves.push_back(Move(index, index-8, this, false, false, false, Piece::Queen));
				LegalMoves.push_back(Move(index, index-8, this, false, false, false, Piece::Rook));
				LegalMoves.push_back(Move(index, index-8, this, false, false, false, Piece::Knight));
				LegalMoves.push_back(Move(index, index-8, this, false, false, false, Piece::Bishop));
			}
		}

		if (board->squares[index-9].piecetype != Piece::None && (selfBitboard & NotInAFile) > 0){
			if (board->squares[index-9].color != color){
				if (index/8 != 1){
					LegalMoves.push_back(Move(index, index-9, this, false, false));
				}
				else{
					LegalMoves.push_back(Move(index, index-9, this, false, false, false, Piece::Queen));
					LegalMoves.push_back(Move(index, index-9, this, false, false, false, Piece::Rook));
					LegalMoves.push_back(Move(index, index-9, this, false, false, false, Piece::Knight));
					LegalMoves.push_back(Move(index, index-9, this, false, false, false, Piece::Bishop));
				}
			}
		}

		if (board->squares[index-7].piecetype != Piece::None && (selfBitboard & NotInHFile) > 0){
			if (board->squares[index-7].color != color){
				if (index/8 != 1){
					LegalMoves.push_back(Move(index, index-7, this, false, false));
				}
				else{
					LegalMoves.push_back(Move(index, index-7, this, false, false, false, Piece::Queen));
					LegalMoves.push_back(Move(index, index-7, this, false, false, false, Piece::Rook));
					LegalMoves.push_back(Move(index, index-7, this, false, false, false, Piece::Knight));
					LegalMoves.push_back(Move(index, index-7, this, false, false, false, Piece::Bishop));
				}
			}
		}

		if (board->DoublePawnPushIndex != -1){
			if (index+1 == board->DoublePawnPushIndex && board->squares[index+1].color != color  && (selfBitboard & NotInHFile) > 0){
				LegalMoves.push_back(Move(index, index-7, this, false, true));
			}
			else if (index-1 == board->DoublePawnPushIndex && board->squares[index-1].color != color && (selfBitboard & NotInAFile) > 0){
				LegalMoves.push_back(Move(index, index-9, this, false, true));
			}
		}
	}

	else{
		if (!moved && board->squares[index+8].piecetype == Piece::None && board->squares[index+16].piecetype == Piece::None){
				LegalMoves.push_back(Move(index, index+16, this, true, false));
		}

		if (board->squares[index+8].piecetype == Piece::None){
			if (index/8 != 6){
				LegalMoves.push_back(Move(index, index+8, this, false, false));
			}
			else{
				LegalMoves.push_back(Move(index, index+8, this, false, false, false, Piece::Queen));
				LegalMoves.push_back(Move(index, index+8, this, false, false, false, Piece::Rook));
				LegalMoves.push_back(Move(index, index+8, this, false, false, false, Piece::Knight));
				LegalMoves.push_back(Move(index, index+8, this, false, false, false, Piece::Bishop));
			}
		}

		if (board->squares[index+9].piecetype != Piece::None && (selfBitboard & NotInHFile) > 0){
			if (board->squares[index+9].color != color){
				if (index/8 != 6){
					LegalMoves.push_back(Move(index, index+9, this, false, false));
				}
				else{
					LegalMoves.push_back(Move(index, index+9, this, false, false, false, Piece::Queen));
					LegalMoves.push_back(Move(index, index+9, this, false, false, false, Piece::Rook));
					LegalMoves.push_back(Move(index, index+9, this, false, false, false, Piece::Knight));
					LegalMoves.push_back(Move(index, index+9, this, false, false, false, Piece::Bishop));
				}
			}
		}

		if (board->squares[index+7].piecetype != Piece::None && (selfBitboard & NotInAFile) > 0){
			if (board->squares[index+7].color != color){
				if (index/8 != 6){
					LegalMoves.push_back(Move(index, index+7, this, false, false));
				}
				else{
					LegalMoves.push_back(Move(index, index+7, this, false, false, false, Piece::Queen));
					LegalMoves.push_back(Move(index, index+7, this, false, false, false, Piece::Rook));
					LegalMoves.push_back(Move(index, index+7, this, false, false, false, Piece::Knight));
					LegalMoves.push_back(Move(index, index+7, this, false, false, false, Piece::Bishop));
				}
			}
		}

		if (board->DoublePawnPushIndex != -1){
			if (index+1 == board->DoublePawnPushIndex && board->squares[index+1].color != color && (selfBitboard & NotInHFile) > 0){
				LegalMoves.push_back(Move(index, index+9, this, false, true));
			}
			else if (index-1 == board->DoublePawnPushIndex && board->squares[index-1].color != color && (selfBitboard & NotInAFile) > 0){
				LegalMoves.push_back(Move(index, index+7, this, false, true));
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