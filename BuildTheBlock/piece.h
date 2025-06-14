#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "raylib.h"

struct Piece
{
	std::vector<std::vector<int>> pieceLayout;
	Color pieceColour;
	Vector2 position;
	Vector2 startPosition;
	bool isHighlighted;

	Piece();
	Piece(std::vector<std::vector<int>> pieceLayout, Color pieceColour, Vector2 startPosition);
	void rotate90Clockwise();
	void flipPiece();
};

#endif