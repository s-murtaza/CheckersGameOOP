#include <iostream>
#include "Checker.hpp"
#include <SDL_image.h>

void Checker::drawObjects()
{
    // std::vector<std::vector<int>> checkersBoard = {
    //     {1, 0, 1, 0, 1, 0, 1, 0},
    //     {0, 1, 0, 1, 0, 1, 0, 1},
    //     {1, 0, 1, 0, 1, 0, 1, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 2, 0, 2, 0, 2, 0, 2},
    //     {2, 0, 2, 0, 2, 0, 2, 0},
    //     {0, 2, 0, 2, 0, 2, 0, 2}
    // };

    std::vector<blackChecker*> black_checkers; // Vector to store pointers to Checker objects
    std::vector<redChecker*> red_checkers;

    int x = 20;
    int y = 20;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (checkersBoard[i][j] == 3)
            {
                blackChecker* p = new blackChecker(x, y);
                p->draw();
                black_checkers.push_back(p);
            }
            else if (checkersBoard[i][j] == 2)
            {
                redChecker* p2 = new redChecker(x, y);
                p2->draw();
                red_checkers.push_back(p2);
            }
            x = x + 80;
        }
        x = 20;
        y = y + 80;

    }
}

void Checker::ValidMove(int x, int y) {
    int xCord = x / 80;
    int yCord = y / 80;
    int currentNode = Board::checkersBoard[yCord][xCord];
    // SDL_Rect dstRect = {xCord*80, (yCord-1)*80, 80, 80};
    // cout<<currentNode<<'\n';
    if (currentNode == 3) 
    {
        if (yCord-1 >= 0 && xCord+1 < 8 && checkersBoard[yCord-1][xCord+1] == 1) //northeast
        {
            // cout<<"green on southeast\n";
            SDL_Rect dstRect = {(xCord+1)*80, (yCord-1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            // SDL_RenderCopy(renderer, greenDotTexture, NULL, &dstRect);
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
        }
        if (yCord-1 >= 0 && xCord-1 >= 0 &&checkersBoard[yCord-1][xCord-1] == 1) 
        {
            // moverRect = {x, y, 25, 25};
            // cout<<"green on southwest\n";
            SDL_Rect dstRect = {(xCord-1)*80, (yCord-1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
            // return true;
        }
        if (yCord+1 < 8 && xCord+1 < 8 &&checkersBoard[yCord+1][xCord+1] == 1) 
        {
            // cout<<"green on northeast\n";
            SDL_Rect dstRect = {(xCord+1)*80, (yCord+1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
            // return true;
        }
        if (yCord+1 < 8 && xCord-1 >= 0 &&checkersBoard[yCord+1][xCord-1] == 1)
        {
            // cout<<"green on northwest\n";
            SDL_Rect dstRect = {(xCord-1)*80, (yCord+1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
        }
        
    }
    else if (currentNode == 2)
    {
        if (yCord-1 >= 0 && xCord+1 < 8 &&checkersBoard[yCord-1][xCord+1] == 1) //northeast
        {
            // cout<<"green on southeast\n";
            SDL_Rect dstRect = {(xCord+1)*80, (yCord-1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            // SDL_RenderCopy(renderer, greenDotTexture, NULL, &dstRect);
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
        }
        if (yCord-1 >= 0 && xCord-1 >= 0 &&checkersBoard[yCord-1][xCord-1] == 1) 
        {
            // moverRect = {x, y, 25, 25};
            // cout<<"green on southwest\n";
            SDL_Rect dstRect = {(xCord-1)*80, (yCord-1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
            // return true;
        }
        if (yCord+1 < 8 && xCord+1 < 8 &&checkersBoard[yCord+1][xCord+1] == 1) 
        {
            // cout<<"green on northeast\n";
            SDL_Rect dstRect = {(xCord+1)*80, (yCord+1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
            // return true;
        }
        if (yCord+1 < 8 && xCord-1 >= 0 &&checkersBoard[yCord+1][xCord-1] == 1)
        {
            // cout<<"green on northwest\n";
            SDL_Rect dstRect = {(xCord-1)*80, (yCord+1)*80, 80, 80}; // adjust size and position as needed
            SDL_Rect dstSrc = {790,292,257,211}; 
            SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &dstSrc, &dstRect);
            SDL_DestroyTexture(greenDotTexture);
        }
    }

}

// creates new objects 
void Checker::createObject(int x, int y)
{
    
}
