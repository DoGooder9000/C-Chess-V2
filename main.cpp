#include <SDL2/SDL.h>
#include "Board.h"

void Clean(SDL_Window* window, SDL_Renderer* renderer);
void DrawBoard(Board* board, SDL_Renderer* renderer);


const char* window_title = "Chess C++";
int window_width = 400;
int window_height = 400;

SDL_Color lightSquareColor = {255, 255, 255, 255};
SDL_Color darkSquareColor = {0, 0, 0, 255};

Board* currentBoard;


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
