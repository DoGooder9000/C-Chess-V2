#include <SDL2/SDL.h>
#include "../Include/Board.h"

void Clean(SDL_Window* window, SDL_Renderer* renderer);
void DrawBoard(Board* board, SDL_Renderer* renderer);


const char* window_title = "Chess C++";
int window_width = 400;
int window_height = 400;

SDL_Color lightSquareColor = {255, 255, 255, 255};
SDL_Color darkSquareColor = {0, 0, 0, 255};

Board* b;


int main(int argc, char* argv[]){
	// Initialize and Create everything

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


	b = new Board();

	

	SDL_RenderClear(renderer);

	DrawBoard(b, renderer);

	SDL_RenderPresent(renderer);


	// Clean everything up

	Clean(window, renderer);

	delete b;


	return 0;
}


void Clean(SDL_Window* window, SDL_Renderer* renderer){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
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
