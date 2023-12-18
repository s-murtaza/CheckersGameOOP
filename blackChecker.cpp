#include "blackChecker.hpp"
// pigeon implementation will go here.


// in project implementation this draw function should only be in superclass
void blackChecker::draw(){
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
}


// fly() is overrided from the superclass
void blackChecker::fly(int x, int y){
    
    // moverRect.x += x;
    // moverRect.y += y;

}

blackChecker::blackChecker(int x, int y){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {230,14, 179, 179};

    // it will display pigeon on x = 30, y = 40 location, the size of pigeon is 50 width, 60 height
    moverRect = {x, y, 50, 50};
}
