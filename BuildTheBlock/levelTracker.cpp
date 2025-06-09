#include "levelTracker.h"

namespace activeLevel
{
	Level level;
	std::vector<Piece> pieces;
	Piece* selectedPiece = NULL;
	Piece* hoveredPiece = NULL;
	std::vector<std::vector<int>> activeSolutionGrid;
	Vector2 dragOffset = Vector2();
	int gridStartX = 0;
	int gridStartY = 0;
}