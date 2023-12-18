#include <cmath>
#include "game.hpp"
//#include "Checker.hpp"
#include "drawing.hpp"

using namespace std;

SDL_Renderer* Drawing::gRenderer = NULL;
SDL_Texture* Drawing::assets = NULL;

bool Game::init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			Drawing::gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( Drawing::gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( Drawing::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
	Drawing::assets = loadTexture("assets.png");
    gTexture = loadTexture("startScreen.png");
	if(Drawing::assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

bool Game::redWin()
{
    //Loading success flag
    bool success = true;

//    Drawing::assets = loadTexture("assets.png");
    gTexture = loadTexture("redWin.png");
    if(Drawing::assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
    return success;
}

bool Game::blackWin()
{
    //Loading success flag
    bool success = true;

    gTexture = loadTexture("blackWin.png");
    if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
    return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(Drawing::assets);
	Drawing::assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( Drawing::gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	Drawing::gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Drawing::gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool Game::isEmpty(int num, Checker checker)
{
    // Check if the number exists in the checker. checkboard array. If it does not exist then return true
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8 ; j++)
        {
            if (checker.checkersBoard[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

void Game::run()
{
    bool quit = false;
    SDL_Event e;
    Checker checker;
	int selectedPieceX = -1;
	int selectedPieceY = -1;
    bool mousePressed = false;
    bool selected = false;
    // Call blackWin
    while (!quit)
    {
//        Game::blackWin();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (state == 0 && e.type == SDL_MOUSEBUTTONDOWN)
            {
                int xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                std::cout << xMouse << " : " << yMouse << '\n';

                if (xMouse >= 258 && xMouse <= 408 && yMouse >= 406 && yMouse <= 433)
                {
                    // Change the background when the click is within the specified coordinates
                    SDL_DestroyTexture(gTexture);
                    gTexture = loadTexture("Board.png");
//                    red_texture = loadTexture("redWin.png");
//                    black_texture = loadTexture("blackWin.png");
//                    SDL_RenderCopy(Drawing::gRenderer, black_texture, NULL, NULL);
                    state = 1; // Change the state after the background is changed
                }
            }
        }

        // Render
        SDL_RenderClear(Drawing::gRenderer);
        SDL_RenderCopy(Drawing::gRenderer, gTexture, NULL, NULL);
//        SDL_RenderCopy(Drawing::gRenderer, black_texture, NULL, NULL);
        // Render objects
        if (state == 1)
        {
            checker.drawObjects();
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && !mousePressed) {
//				if () {
					int x = e.button.x;
					int y = e.button.y;
//					std::cout << x << " : " << y << '\n';
					// checker.ValidMove(x,y);
					int xCord = ceil(x / 80);
					int yCord = ceil(y / 80);
                    std::cout << xCord << " : " << yCord << '\n';
					if (selectedPieceX != -1 && selectedPieceY != -1) {
						// If the clicked square is a valid destination, move the piece
						if (checker.checkersBoard[yCord][xCord] == 1) {
                            if (checker.checkersBoard[selectedPieceY][selectedPieceX] == 2)
                            {
                                // Check if the move is valid
                                if ((yCord == selectedPieceY - 1 || yCord == selectedPieceY + 1) && (xCord == selectedPieceX - 1)) {
                                    cout << "Entered single jump black position\n";
                                    checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
                                    checker.checkersBoard[yCord][xCord] = 2; // Move the piece to the new square
//                                    checker.ValidMove(x, y);
//                                    selectedPieceX = -1; // Reset the selected piece
//                                    selectedPieceY = -1;
                                }
                                // Check if 3 is in between
                                else if ((yCord == selectedPieceY - 2) && (xCord == selectedPieceX - 2)) {
                                    cout << "Entered double jump black position\n";
                                    // Check if the piece in between is an opponent
                                    // Also check if the piece is not out of bounds
                                    if (selectedPieceY - 1 >= 0 && selectedPieceX - 1 >= 0 &&
                                        checker.checkersBoard[selectedPieceY - 1][selectedPieceX - 1] == 3) {
                                        cout << "Entered checker.checkersBoard[selectedPieceY - 1][selectedPieceX - 1] == 3\n";
                                        checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
                                        checker.checkersBoard[selectedPieceY - 1][selectedPieceX -
                                                                                  1] = 1; // Empty the square of the opponent
                                        checker.checkersBoard[yCord][xCord] = 2; // Move the piece to the new square
//                                        checker.ValidMove(x, y);
                                    }
//                                    else if (selectedPieceY + 1 < 8 && selectedPieceX - 1 >= 0 &&
//                                            checker.checkersBoard[selectedPieceY + 1][selectedPieceX - 1] == 3) {
//                                        cout << "Entered checker.checkersBoard[selectedPieceY + 1][selectedPieceX - 1] == 3\n";
//                                        checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
//                                        checker.checkersBoard[selectedPieceY + 1][selectedPieceX -
//                                                                                  1] = 1; // Empty the square of the opponent
//                                        checker.checkersBoard[yCord][xCord] = 2; // Move the piece to the new square
////                                        checker.ValidMove(x, y);
//                                    }
//                                    selectedPieceX = -1; // Reset the selected piece
//                                    selectedPieceY = -1;
                                }
                                else if ((yCord == selectedPieceY + 2) && (xCord == selectedPieceX - 2)) {
                                    if (selectedPieceY + 1 < 8 && selectedPieceX - 1 >= 0 &&
                                        checker.checkersBoard[selectedPieceY + 1][selectedPieceX - 1] == 3) {
                                        cout << "Entered checker.checkersBoard[selectedPieceY + 1][selectedPieceX - 1] == 3\n";
                                        checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
                                        checker.checkersBoard[selectedPieceY + 1][selectedPieceX -
                                                                                  1] = 1; // Empty the square of the opponent
                                        checker.checkersBoard[yCord][xCord] = 2; // Move the piece to the new square
//                                        checker.ValidMove(x, y);
                                    }
//                                    selectedPieceX = -1; // Reset the selected piece
//                                    selectedPieceY = -1;
                                }


//                                checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
//                                checker.checkersBoard[yCord][xCord] = 2; // Move the piece to the new square
////                                checker.ValidMove(x, y);
                                selectedPieceX = -1; // Reset the selected piece
                                selectedPieceY = -1;
                            }
                            else if (checker.checkersBoard[selectedPieceY][selectedPieceX] == 3)
                            {
                                if ((yCord == selectedPieceY - 1 || yCord == selectedPieceY + 1) && (xCord == selectedPieceX + 1)) {
                                checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
                                checker.checkersBoard[yCord][xCord] = 3; // Move the piece to the new square
//                                checker.ValidMove(x, y);
//                                selectedPieceX = -1; // Reset the selected piece
//                                selectedPieceY = -1;
                                }
                                // Check if 3 is in between
                                else if ((yCord == selectedPieceY - 2) && (xCord == selectedPieceX + 2)) {
                                    cout << "Entered double jump white position\n";
                                    // Check if the piece in between is an opponent
                                    // Also check if the piece is not out of bounds
                                    if (selectedPieceY - 1 >= 0 && selectedPieceX + 1 < 8 &&
                                        checker.checkersBoard[selectedPieceY - 1][selectedPieceX + 1] == 2) {
                                        cout << "Entered checker.checkersBoard[selectedPieceY - 1][selectedPieceX + 1] == 2\n";
                                        checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
                                        checker.checkersBoard[selectedPieceY - 1][selectedPieceX +
                                                                                  1] = 1; // Empty the square of the opponent
                                        checker.checkersBoard[yCord][xCord] = 3; // Move the piece to the new square
//                                        checker.ValidMove(x, y);
                                    }
//                                    else if (selectedPieceY + 1 < 8 && selectedPieceX + 1 < 8 &&
//                                            checker.checkersBoard[selectedPieceY + 1][selectedPieceX + 1] == 2) {
//                                        cout << "Entered checker.checkersBoard[selectedPieceY + 1][selectedPieceX + 1] == 2\n";
//                                        checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
//                                        checker.checkersBoard[selectedPieceY + 1][selectedPieceX +
//                                                                                  1] = 1; // Empty the square of the opponent
//                                        checker.checkersBoard[yCord][xCord] = 3; // Move the piece to the new square
////                                        checker.ValidMove(x, y);
//                                    }
//                                    selectedPieceX = -1; // Reset the selected piece
//                                    selectedPieceY = -1;
                                }
                                else if ((yCord == selectedPieceY + 2) && (xCord == selectedPieceX + 2)) {
                                    if (selectedPieceY + 1 < 8 && selectedPieceX + 1 < 8 &&
                                        checker.checkersBoard[selectedPieceY + 1][selectedPieceX + 1] == 2) {
                                        cout << "Entered checker.checkersBoard[selectedPieceY + 1][selectedPieceX + 1] == 2\n";
                                        checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
                                        checker.checkersBoard[selectedPieceY + 1][selectedPieceX +
                                                                                  1] = 1; // Empty the square of the opponent
                                        checker.checkersBoard[yCord][xCord] = 3; // Move the piece to the new square
//                                        checker.ValidMove(x, y);
                                    }
                                }

                                selectedPieceX = -1; // Reset the selected piece
                                selectedPieceY = -1;
                            }

//                            // Call isEmpty, if it returns true for 2, then call redWin
                            if (isEmpty(2, checker))
                            {
                                SDL_RenderClear(Drawing::gRenderer);
                                // Clear assets
                                SDL_DestroyTexture(Drawing::assets);
                                Game::redWin();
//                                red_texture = loadTexture("redWin.png");
//                                SDL_RenderCopy(Drawing::gRenderer, red_texture, NULL, NULL);
                            }

                            // Call isEmpty, if it returns true for 3, then call blackWin
                            if (isEmpty(3, checker))
                            {
                                SDL_RenderClear(Drawing::gRenderer);
                                SDL_DestroyTexture(Drawing::assets);
                                Game::blackWin();
//                                black_texture = loadTexture("blackWin.png");
//                                SDL_RenderCopy(Drawing::gRenderer, black_texture, NULL, NULL);
                            }

//							checker.checkersBoard[selectedPieceY][selectedPieceX] = 1; // Empty the original square
//							checker.checkersBoard[yCord][xCord] = 3; // Move the piece to the new square
//                          checker.ValidMove(x, y);
//							selectedPieceX = -1; // Reset the selected piece
//							selectedPieceY = -1;
							}
                    }
					else {
                        // If a piece is not selected and the clicked square has a piece, select it
                        if (checker.checkersBoard[yCord][xCord] == 3 || checker.checkersBoard[yCord][xCord] == 2) {
                            checker.ValidMove(x, y);
                            selectedPieceX = xCord;
                            selectedPieceY = yCord;
                        }
                    }
//					}
                mousePressed = true; // Set the flag when the button is pressed
            }
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && mousePressed) { // Check for button release
//                if (e.button.button == SDL_BUTTON_LEFT) {
                    // Reset any necessary variables or perform actions related to button release
                    mousePressed = false; // Reset the flag when the button is released
//                }
            }
        }
//        SDL_Delay(100);
        SDL_RenderPresent(Drawing::gRenderer);

//        // Delay (if necessary)
//        SDL_Delay(10);
    }
}
