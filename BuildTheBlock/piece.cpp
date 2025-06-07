#include "piece.h"

Piece::Piece()
{
	pieceLayout = std::vector<std::vector<int>>();
	pieceColour = BLACK;
}

Piece::Piece(std::vector<std::vector<int>> pieceLayout, Color pieceColour)
{
	this->pieceLayout = pieceLayout;
	this->pieceColour = pieceColour;
}