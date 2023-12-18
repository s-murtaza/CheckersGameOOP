
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Checker.hpp"

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 640;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    SDL_Texture* black_texture = NULL;
    SDL_Texture* red_texture = NULL;

    unsigned state = 0;
public:



    bool init();
    bool loadMedia();
    void close();
    bool isEmpty(int num, Checker checker);
    bool blackWin();
    bool redWin();
    SDL_Texture* loadTexture( std::string path );
    void run();
};

