#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Includes/Board.h"

void Clean(SDL_Window* window, SDL_Renderer* renderer);
void DrawBoard(Board* board, SDL_Renderer* renderer);


const char* window_title = "Chess C++";
int window_width = 400;
int window_height = 400;

SDL_Color lightSquareColor = {255, 255, 255, 255};
SDL_Color darkSquareColor = {0, 0, 0, 255};

Board* currentBoard;


SDL_Surface* WhitePawnImg = IMG_Load("Img/whitepawn.png");
SDL_Surface* WhiteKnightImg = IMG_Load("Img/whiteknight.png");
SDL_Surface* WhiteBishopImg = IMG_Load("Img/whitebishop.png");
SDL_Surface* WhiteRookImg = IMG_Load("Img/whiterook.png");
SDL_Surface* WhiteQueenImg = IMG_Load("Img/whitequeen.png");
SDL_Surface* WhiteKingImg = IMG_Load("Img/whiteking.png");

SDL_Surface* BlackPawnImg = IMG_Load("Img/blackpawn.png");
SDL_Surface* BlackKnightImg = IMG_Load("Img/blackknight.png");
SDL_Surface* BlackBishopImg = IMG_Load("Img/blackbishop.png");
SDL_Surface* BlackRookImg = IMG_Load("Img/blackrook.png");
SDL_Surface* BlackQueenImg = IMG_Load("Img/blackqueen.png");
SDL_Surface* BlackKingImg = IMG_Load("Img/blackking.png");

int main(int argc, char* argv[]){
	// Initialize and Create everything

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


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
		

		SDL_RenderClear(renderer); 	// Clear the Renderer 

						// Do all of the drawing functions

		DrawBoard(currentBoard, renderer); 	// Draw the board

						

		SDL_RenderPresent(renderer);	// Show the final render

	}

	// The main loop exits. Clean everything up

	// Clean up SDL2

	Clean(window, renderer); 	// Delete the window and renderer
	SDL_Quit();			// Quit SDL2


	delete currentBoard;		// Delete the board pointer


	return 0; 			// Exit
}


void Clean(SDL_Window* window, SDL_Renderer* renderer){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void DrawBoard(Board* board, SDL_Renderer* renderer){
	SDL_Color squareColor;

	float squareWidth = window_width / board->width;
	float squareHeight = window_height / board->height;

	SDL_Rect r;
	r.w = squareWidth;
	r.h = squareHeight;

	for (int i = 0; i < board->width; i++){
		for (int j = 0; j < board->height; j++){

			if ((i+j) % 2 == 0){ squareColor = lightSquareColor; } // Set the color of the square
			else{ squareColor = darkSquareColor; }

			r.x = i * squareWidth; // Set the position of the square
			r.y = j * squareHeight;

			SDL_SetRenderDrawColor(renderer, squareColor.r, squareColor.g, squareColor.b, squareColor.a); // Draw the square
			SDL_RenderFillRect(renderer, &r);
		}
	}
}

void DrawPieces(Board* board, SDL_Renderer* renderer){
	;
}