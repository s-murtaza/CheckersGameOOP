#include<SDL.h>
#include<vector>
#include<list>
#include <SDL_image.h>
using namespace std;

class Board {
    protected:
    SDL_Texture * greenDotTexture;
    SDL_Renderer * renderer;
    public:
    Board();
    std::vector<std::vector<int>> checkersBoard = {
        {3, 0, 3, 0, 1, 0, 2, 0},
        {0, 3, 0, 1, 0, 2, 0, 2},
        {3, 0, 3, 0, 1, 0, 2, 0},
        {0, 3, 0, 1, 0, 2, 0, 2},
        {3, 0, 3, 0, 1, 0, 2, 0},
        {0, 3, 0, 1, 0, 2, 0, 2},
        {3, 0, 3, 0, 1, 0, 2, 0},
        {0, 3, 0, 1, 0, 2, 0, 2}
    };
};