#include <stdio.h>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Includes/Bot.h"
#include "Includes/Board.h"
#include "Includes/Move.h"

void Clean(SDL_Window* window, SDL_Renderer* renderer);
void DestroyPieceTextures(SDL_Texture** PieceTextures);
void DrawBoard(Board* board, SDL_Renderer* renderer);
void DrawPieces(Board* board, SDL_Texture** PieceTextures, SDL_Renderer* renderer);
void DrawBitboard(Bitboard bitboard, SDL_Color color, SDL_Renderer* renderer);
Piece* GetPieceClicked(Board* board, int mouseX, int mouseY);
int GetIndexClicked(Board* board, int mouseX, int mouseY);
void Perft(Board* board, int depth);
int CountPlySub(Board* board, int depth, int maxDepth);

const char* window_title = "Chess C++";
const int window_width = 400;
const int window_height = 400;

const float squareWidth = (float)window_width/(float)8;
const float squareHeight = (float)window_height/(float)8;

SDL_Color lightSquareColor = {209, 163, 113, 255};
SDL_Color darkSquareColor = {128, 100, 70, 255};
SDL_Color legalMoveColor = {245, 211, 61, 255};
SDL_Color attackedSquareColor = {255, 0, 0, 255};

Board* currentBoard;
Piece* currentPiece;

SDL_Surface* img = nullptr;

SDL_Texture* PieceTextures[32];

int main(int argc, char* argv[]){
	// Initialize and Create everything

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	img = IMG_Load("Img/whitepawn.png");
	PieceTextures[1] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/whiteknight.png");
	PieceTextures[2] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/whitebishop.png");
	PieceTextures[3] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/whiterook.png");
	PieceTextures[4] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/whitequeen.png");
	PieceTextures[5] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/whiteking.png");
	PieceTextures[6] = SDL_CreateTextureFromSurface(renderer, img);
	
	img = IMG_Load("Img/blackpawn.png");
	PieceTextures[9] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/blackknight.png");
	PieceTextures[10] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/blackbishop.png");
	PieceTextures[11] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/blackrook.png");
	PieceTextures[12] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/blackqueen.png");
	PieceTextures[13] = SDL_CreateTextureFromSurface(renderer, img);

	img = IMG_Load("Img/blackking.png");
	PieceTextures[14] = SDL_CreateTextureFromSurface(renderer, img);

	SDL_FreeSurface(img);


	currentBoard = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	currentBoard->color = 0;

	Bot blackBot = Bot(Piece::Black, currentBoard);

	currentPiece = nullptr;
	
	// Make a event variable to read into 
	SDL_Event event;
	bool running = true;

	while (running){		
		if (currentBoard->color == blackBot.color){
			blackBot.board = currentBoard;
			Move move = blackBot.GetMove(4);
			currentBoard->MovePiece(move);
		}
		

		// Get events
		if (SDL_PollEvent(&event)){
			// Decide what to do with each event type
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					
					currentPiece  = GetPieceClicked(currentBoard, event.motion.x, event.motion.y);

					if (currentPiece->piecetype == Piece::None){
						currentPiece = nullptr;
					}

					else if (currentPiece->color != currentBoard->color){
						currentPiece = nullptr;
					}

					break;
				
				default:
					break;
				}

				break;
			
			case SDL_MOUSEBUTTONUP:
				
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					
					if (currentPiece != nullptr){
						int target_index = GetIndexClicked(currentBoard, event.motion.x, event.motion.y);

						if ((Piece::MoveListToBitboard(currentPiece->GetFullyLegalMoves(currentBoard)) & (1ULL << target_index)) > 0){

							if (target_index != currentPiece->index){
								Move move;
								if (currentPiece->piecetype == Piece::Pawn && (abs(target_index-currentPiece->index)%16 == 0)){
									move = Move(currentPiece->index, target_index, currentPiece, true, false);
								}

								//				If the piece is a pawn		and				it is a diagonal move			and						the diagonal move square is free
								else if (currentPiece->piecetype == Piece::Pawn && ((target_index-currentPiece->index)%8 != 0) && currentBoard->squares[target_index].piecetype == Piece::None){
									move = Move(currentPiece->index, target_index, currentPiece, false, true);
								}

								else if(currentPiece->piecetype == Piece::Pawn && (target_index/8 == 7 || target_index/8 == 0)){
									move = Move(currentPiece->index, target_index, currentPiece, false, false, false, Piece::Queen);
								}

								else if (currentPiece->piecetype == Piece::King && abs(currentPiece->index - target_index) == 2){
									move = Move(currentPiece->index, target_index, currentPiece, false, false, true);
								}

								else{
									move = Move(currentPiece->index, target_index, currentPiece, false, false);
								}
								currentBoard->MovePiece(move);
							}
						
						}
						currentPiece = nullptr;
					}

					break;
				
				default:
					break;
				}
			
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					currentBoard->BoardBack();
					break;
				
				case SDLK_RIGHT:
					currentBoard->BoardForward();
					break;
				
				default:
					break;
				}

			default:
				break;
			}
		}
		

		SDL_RenderClear(renderer); 							// Clear the Renderer 

															// Do all of the drawing functions

		DrawBoard(currentBoard, renderer); 					// Draw the board

		if (currentPiece != nullptr){
			DrawBitboard(Piece::MoveListToBitboard(currentPiece->GetFullyLegalMoves(currentBoard)), legalMoveColor, renderer);
		}

		//DrawBitboard(currentBoard->GetAllAttackedSquares(currentBoard->OppositeColor(currentBoard->color)), attackedSquareColor, renderer);

		DrawPieces(currentBoard, PieceTextures, renderer);	// Draw the pieces on the board

		SDL_RenderPresent(renderer);						// Show the final render

	}

	// The main loop exits. Clean everything up

	// Clean up SDL2

	Clean(window, renderer); 	// Delete the window and renderer

	DestroyPieceTextures(PieceTextures);

	SDL_Quit();					// Quit SDL2
	IMG_Quit();

	delete currentBoard;		// Delete the board pointer


	return 0; 					// Exit
}


void Clean(SDL_Window* window, SDL_Renderer* renderer){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void DestroyPieceTextures(SDL_Texture** PieceTextures){
	for (int i = 0; i < 32; i++){
		SDL_DestroyTexture(PieceTextures[i]);
	}
}

void DrawBoard(Board* board, SDL_Renderer* renderer){
	SDL_Color squareColor;

	SDL_Rect r;
	r.w = squareWidth;
	r.h = squareHeight;

	for (int i = 0; i < board->width; i++){
		for (int j = 0; j < board->height; j++){

			if ((i+j) % 2 == 0){ squareColor = lightSquareColor; } // Set the color of the square
			else{ squareColor = darkSquareColor; }

			r.x = ceil(i * squareWidth); // Set the position of the square
			r.y = ceil(j * squareHeight);

			SDL_SetRenderDrawColor(renderer, squareColor.r, squareColor.g, squareColor.b, squareColor.a); // Draw the square
			SDL_RenderFillRect(renderer, &r);
		}
	}
}

void DrawPieces(Board* board, SDL_Texture** PieceTextures, SDL_Renderer* renderer){
	SDL_Rect destRect;
	destRect.w = squareWidth;
	destRect.h = squareHeight;

	for (int i=0; i < board->size; i++){
		if (board->squares[i].piecetype == Piece::None){continue;}

		std::tie(destRect.x, destRect.y) = board->BoardPosFromIndex(i);

		destRect.x *= squareWidth;
		destRect.y *= squareHeight;

		SDL_RenderCopy(renderer, PieceTextures[board->squares[i].GetPieceID()], NULL, &destRect);
	}
}

void DrawBitboard(Bitboard bitboard, SDL_Color color, SDL_Renderer* renderer){
	SDL_Rect r;
	r.w = squareWidth;
	r.h = squareHeight;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (int i=0; i<64; i++){
		if ((bitboard & (1ULL << i)) > 1){
			std::tie(r.x, r.y) = Board::BoardPosFromIndex(i);

			r.x = ceil(squareWidth*r.x);
			r.y = ceil(squareHeight*r.y);

			SDL_RenderFillRect(renderer, &r);
		}
	}
}

int GetIndexClicked(Board* board, int mouseX, int mouseY){
	int col = mouseX / squareWidth;
    int row = mouseY / squareHeight;
    int index = board->IndexFromBoardPos(std::make_tuple(col, row));

	return index;
}

Piece* GetPieceClicked(Board* board, int mouseX, int mouseY){
	int index = GetIndexClicked(board, mouseX, mouseY);

	return &(board->squares[index]);
}

void Perft(Board* board, int depth){
	for (int i=0; i<depth; i++){
		printf("depth: %d, Perft: %d\n", i, CountPlySub(board, i, depth-1));
	}
}

int CountPlySub(Board* board, int depth, int maxDepth){
	int moveCount = 0;
	
	if (depth == 0){
		return 1;
	}

	else{
		/*
		for (Move move : board->GetAllLegalMoves(board->color)){
			board->MovePiece(move);

			int _ = CountPlySub(board, depth-1, maxDepth);

			moveCount += _;

			board->UndoBoardMove();

			if (depth == maxDepth){
				move.Print();
				printf("%d\n\n", _);
			}
		}
		*/
		for (int i=0; i<64; i++){
			if (board->squares[i].color == board->color){
				for (Move move : board->squares[i].GetFullyLegalMoves(board)){
					board->MovePiece(move);

					int _ = CountPlySub(board, depth-1, maxDepth);

					moveCount += _;

					board->UndoBoardMove();

					/*
					if (depth == maxDepth){
						move.Print();
						printf("%d\n\n", _);
					}
					*/
				}
			}
		}
	}


	return moveCount;
}