#include "Includes/Bot.h"

Bot::Bot(int color, Board* board) : color(color), board(board){}

Move Bot::GetMove(int depth){
	Move bestMove;
	int bestEval = NegativeInfinity;

	numPositions = 0;

	int eval;

	for (Move move : board->GetAllLegalMoves(color)){
		board->MovePiece(move);
		eval = -NegaMax(NegativeInfinity, PositiveInfinity, depth);
		board->UndoBoardMove();

		if (eval > bestEval){
			bestEval = eval;
			bestMove = move;
		}
	}

	printf("%d\n", numPositions);

	return bestMove;
}

int Bot::NegaMax(int alpha, int beta, int depth){
	if (depth == 0){return Evaluate();}

	int eval;

	for (Move move : board->GetAllLegalMoves(board->color)){
		numPositions++;

		board->MovePiece(move);
		eval = NegaMax(-beta, -alpha, depth-1) * -1;
		board->UndoBoardMove();

		if (eval >= beta){
			return beta;
		}
		if (eval > alpha){
			alpha = eval;
		}
	}

	return alpha;
}

int Bot::Evaluate(){
	int score = 0;

	for (int i=0; i<6; i++){
		score += PieceValues[i+1]*board->PieceCount[0][i];
	}
	for (int i=0; i<6; i++){
		score -= PieceValues[i+1]*board->PieceCount[1][i];
	}
	
	if (board->color == Piece::Black){
		score *= -1;
	}

	return score;
}

std::list<Move> Bot::OrderMoves() {
    std::list<Move> moves = board->GetAllLegalMoves(board->color);
    moves.sort([&](const Move &a, const Move &b) {
        return PieceValues[board->squares[a.target_index].piecetype] > PieceValues[board->squares[b.target_index].piecetype];
    });
    return moves;
}