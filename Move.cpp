#include "Includes/Move.h"
#include <string>

Move::Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant) : start_index(start_index), target_index(target_index), piece(piece), 
DoublePawnPush(DoublePawnPush), isEnPassant(isEnPassant), isCastle(false), PromotionPieceType(Piece::None) {}

Move::Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant, bool isCastle) : start_index(start_index), target_index(target_index), piece(piece), 
DoublePawnPush(DoublePawnPush), isEnPassant(isEnPassant), isCastle(isCastle), PromotionPieceType(Piece::None) {}

Move::Move(int start_index, int target_index, Piece* piece, bool DoublePawnPush, bool isEnPassant, bool isCastle, int PromotionPieceType) : start_index(start_index), target_index(target_index), piece(piece), 
DoublePawnPush(DoublePawnPush), isEnPassant(isEnPassant), isCastle(isCastle), PromotionPieceType(PromotionPieceType) {}

Move::Move() : target_index(-1){}

Move::Move(const Move& other) : start_index(other.start_index), target_index(other.target_index), piece(other.piece), DoublePawnPush(other.DoublePawnPush), isEnPassant(other.isEnPassant), isCastle(other.isCastle), PromotionPieceType(other.PromotionPieceType){}

Move::~Move(){}

bool Move::operator==(const Move& other){
    return (start_index==other.start_index && target_index == other.target_index && piece==other.piece && DoublePawnPush==other.DoublePawnPush && isEnPassant==other.isEnPassant && isCastle==other.isCastle && PromotionPieceType==other.PromotionPieceType);
}

void Move::Print(){
	printf(GetReadableIndex(start_index));
	printf(GetReadableIndex(target_index));
	if (PromotionPieceType != Piece::None){
		printf("%d", PromotionPieceType);
	}
	printf("\n");
}

char* Move::GetReadableIndex(int index){
    char files[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char ranks[8] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    char* res = (char*)malloc(3 * sizeof(char));


    res[0] = files[index % 8];
    res[1] = ranks[(int)(index / 8)];
    res[2] = '\0';

    return res;
}