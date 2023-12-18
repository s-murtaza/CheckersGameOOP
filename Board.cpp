#include "Board.hpp"
#include <iostream>
#include <SDL_image.h>

Board::Board () {
    SDL_Surface * greenDotSurface = IMG_Load("assets.png");
    if (!greenDotSurface) {std::cout << "IMG_Load: " << IMG_GetError() << std::endl;}
    greenDotTexture = SDL_CreateTextureFromSurface(renderer, greenDotSurface);
}
