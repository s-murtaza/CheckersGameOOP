// Checkers.hpp
#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Checkers
{
public:
    Checkers();
    ~Checkers();

    bool init();
    bool loadMedia();
    void close();

    void run();

private:
    // Add any additional member variables and methods for Checkers

    // Example:
    SDL_Texture* loadTexture(std::string path);
    void drawBoard(SDL_Renderer* renderer);
    void handleMouseClick(int x, int y);

    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    SDL_Texture* gTexture;
};

#endif
