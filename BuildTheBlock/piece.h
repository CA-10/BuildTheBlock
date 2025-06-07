#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "raylib.h"

struct Piece
{
	std::vector<std::vector<int>> pieceLayout;
	Color pieceColour;

	Piece();
	Piece(std::vector<std::vector<int>> pieceLayout, Color pieceColour);
	void rotate90Clockwise();
};

#endif