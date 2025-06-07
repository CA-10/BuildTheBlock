#include "piece.h"

Piece::Piece()
{
	pieceLayout = std::vector<std::vector<int>>();
	pieceColour = BLACK;
    position = Vector2();
    isHighlighted = false;
}

Piece::Piece(std::vector<std::vector<int>> pieceLayout, Color pieceColour, Vector2 startPosition)
{
	this->pieceLayout = pieceLayout;
	this->pieceColour = pieceColour;
    this->position = startPosition;
    this->isHighlighted = false;
}

void Piece::rotate90Clockwise() 
{
    int rows = this->pieceLayout.size();
    int cols = this->pieceLayout[0].size();
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            rotated[j][rows - 1 - i] = this->pieceLayout[i][j];
        }
    }

    this->pieceLayout = rotated;
}