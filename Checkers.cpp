// Checkers.cpp
#include "Checkers.hpp"


void Checkers::handleMove(int mouseX, int mouseY)
{
    // Assuming an 8x8 Checkers board
    const int BOARD_SIZE = 8;

    // Assuming the board is drawn starting from position (0, 0)
    const int SQUARE_SIZE = SCREEN_WIDTH / BOARD_SIZE;

    // Calculate the row and column based on mouse coordinates
    int row = mouseY / SQUARE_SIZE;
    int col = mouseX / SQUARE_SIZE;

    // Check if the clicked square is a valid position on the board
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        // Example: Print the selected square to the console (you can replace this with your logic)
        std::cout << "Clicked on square (" << row << ", " << col << ")\n";

        // Example: Check if there is a piece at the selected position
        if (board[row][col] != 0)
        {
            std::cout << "Piece found at (" << row << ", " << col << ")\n";

            // Example: Implement logic for moving the piece
            // You need to add your own logic for validating moves and updating the game state
            // For instance, check if the move is valid, update the board, handle capturing, etc.
        }
        else
        {
            std::cout << "No piece at (" << row << ", " << col << ")\n";
        }
    }
}


bool Checkers::performMove(int startRow, int startCol, int endRow, int endCol)
{
    // Check if the destination square is within the bounds of the board
    if (endRow < 0 || endRow >= BOARD_SIZE || endCol < 0 || endCol >= BOARD_SIZE)
    {
        std::cout << "Invalid move: Destination out of bounds\n";
        return false;
    }

    // Check if the destination square is empty
    if (board[endRow][endCol] != EMPTY)
    {
        std::cout << "Invalid move: Destination is not empty\n";
        return false;
    }

    // Check if the move is within one square diagonally
    if (abs(endRow - startRow) != 1 || abs(endCol - startCol) != 1)
    {
        std::cout << "Invalid move: Piece can only move one square diagonally\n";
        return false;
    }

    // Check if the piece is a king (you may have additional logic for kings)
    if (board[startRow][startCol] == PLAYER_ONE_PIECE && endRow == BOARD_SIZE - 1)
    {
        crownPiece(endRow, endCol);
    }
    else if (board[startRow][startCol] == PLAYER_TWO_PIECE && endRow == 0)
    {
        crownPiece(endRow, endCol);
    }

    // Perform the move
    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = EMPTY;

    // Switch the current player
    currentPlayer = (currentPlayer == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;

    return true;
}

bool Checkers::canCapture(int player, int row, int col)
{
    // Check if the piece at the specified position belongs to the current player
    if (board[row][col] != player)
    {
        std::cout << "Invalid position: No player piece at (" << row << ", " << col << ")\n";
        return false;
    }

    // Check if the piece is a king (you may have additional logic for kings)
    bool isKing = (player == PLAYER_ONE_PIECE && row == BOARD_SIZE - 1) || (player == PLAYER_TWO_PIECE && row == 0);

    // Check possible capturing moves diagonally
    int captureRows[] = {2, 2, -2, -2};
    int captureCols[] = {2, -2, 2, -2};

    for (int i = 0; i < 4; ++i)
    {
        int captureRow = row + captureRows[i];
        int captureCol = col + captureCols[i];

        // Check if the capture move is within bounds
        if (captureRow >= 0 && captureRow < BOARD_SIZE && captureCol >= 0 && captureCol < BOARD_SIZE)
        {
            // Check if the destination square is empty and has an opponent's piece
            if (board[captureRow][captureCol] == EMPTY &&
                (board[row + captureRows[i] / 2][col + captureCols[i] / 2] == (3 - player) || isKing))
            {
                return true;
            }
        }
    }

    return false;
}

void Checkers::crownPiece(int row, int col)
{
    // Assuming a basic crown representation using a different value or identifier
    const int KING_VALUE = 3;

    // Check if the piece is a player one piece reaching the bottom row
    if (board[row][col] == PLAYER_ONE_PIECE && row == BOARD_SIZE - 1)
    {
        // Crown the piece (you may use a different identifier for kings)
        board[row][col] = KING_VALUE;

        std::cout << "Player One's piece crowned at (" << row << ", " << col << ")\n";
    }
    // Check if the piece is a player two piece reaching the top row
    else if (board[row][col] == PLAYER_TWO_PIECE && row == 0)
    {
        // Crown the piece (you may use a different identifier for kings)
        board[row][col] = KING_VALUE;

        std::cout << "Player Two's piece crowned at (" << row << ", " << col << ")\n";
    }
}


// Implement other necessary functions for the game logic
