#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "levelTracker.h"
#include "pieces.h"
#include "constants.h"

void resetSolutionGrid();
void loadPieces();
void updateSelectedPiece();
bool checkOverlappingPieces(int pieceToGridX, int pieceToGridY);
void updateSolutionGrid();
void checkPieceSelection();
bool checkSolution();

#endif