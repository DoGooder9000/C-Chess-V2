#include <stdio.h>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Includes/Board.h"

void Clean(SDL_Window* window, SDL_Renderer* renderer);
void DestroyPieceTextures(SDL_Texture** PieceTextures);
void DrawBoard(Board* board, SDL_Renderer* renderer);
void DrawPieces(Board* board, SDL_Texture** PieceTextures, SDL_Renderer* renderer);


const char* window_title = "Chess C++";
const int window_width = 500;
const int window_height = 500;

const float squareWidth = (float)window_width/(float)8;
const float squareHeight = (float)window_height/(float)8;

SDL_Color lightSquareColor = {255, 255, 255, 255};
SDL_Color darkSquareColor = {0, 0, 0, 255};

Board* currentBoard;

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


	currentBoard = new Board();

	// Make a event variable to read into 
	SDL_Event event;

	while (true){
		// Get events
		if (SDL_PollEvent(&event)){
			// Decide what to do with each event type
			
			if (event.type == SDL_QUIT){ // If the user closes the window
				break; // Break out of the while loop
			}
		}
		

		SDL_RenderClear(renderer); 							// Clear the Renderer 

															// Do all of the drawing functions

		DrawBoard(currentBoard, renderer); 					// Draw the board

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

			r.x = round(i * squareWidth); // Set the position of the square
			r.y = round(j * squareHeight);

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
		if (board->squares[i] == Piece::None){continue;}

		std::tie(destRect.x, destRect.y) = board->BoardPosFromIndex(i);

		destRect.x *= squareWidth;
		destRect.y *= squareHeight;

		SDL_RenderCopy(renderer, PieceTextures[board->squares[i]], NULL, &destRect);
	}
}