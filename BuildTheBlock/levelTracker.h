#ifndef LEVEL_TRACKER_H
#define LEVEL_TRACKER_H

#include "level.h"
#include "piece.h"

namespace activeLevel
{
	extern Level level;
	extern std::vector<Piece> pieces;
	extern Piece* selectedPiece;
	extern Piece* hoveredPiece;
	extern std::vector<std::vector<int>> activeSolutionGrid;
	extern Vector2 dragOffset;
	extern int gridStartX;
	extern int gridStartY;
}

#endif