#include <SDL2/SDL.h>

const char* window_title = "Chess C++";
int window_width = 400;
int window_height = 400;


int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

    getchar();

    return 0;
}