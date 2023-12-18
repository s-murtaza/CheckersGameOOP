#include<SDL.h>
#include "drawing.hpp"
class blackChecker{

    SDL_Rect srcRect, moverRect;
    int frame = 0;

public:
    // add the fly function here as well.
    void draw();
    void fly(int x, int y);
    blackChecker(int x, int y); 
    // may add other overloaded constructors here... 
};
