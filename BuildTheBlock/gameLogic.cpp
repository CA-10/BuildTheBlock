#include "gameLogic.h"

void resetSolutionGrid()
{
	activeLevel::activeSolutionGrid = std::vector<std::vector<int>>();

	for (int x = 0; x < activeLevel::level.levelGrid.size(); x++)
	{
		std::vector<int> row = std::vector<int>();

		for (int y = 0; y < activeLevel::level.levelGrid[0].size(); y++)
		{
			row.push_back(0);
		}

		activeLevel::activeSolutionGrid.push_back(row);
	}
}

void loadPieces()
{
	activeLevel::pieces = std::vector<Piece>();

	int offsetY = 0;

	for (std::string pieceName : activeLevel::level.levelPieces)
	{
		Piece* piece = &pieces::piecesMap[pieceName];

		piece->startPosition = Vector2{ piece->position.x, piece->position.y + offsetY };
		piece->position = piece->startPosition;

		activeLevel::pieces.push_back(*piece);

		offsetY += (piece->pieceLayout.size() * constants::gridCellSize) + constants::gridCellSize;
	}
}

void updateSelectedPiece()
{
	if (activeLevel::selectedPiece == NULL)
		return;

	activeLevel::selectedPiece->position.x = GetMousePosition().x - activeLevel::dragOffset.x;
	activeLevel::selectedPiece->position.y = GetMousePosition().y - activeLevel::dragOffset.y;

	int pieceToGridX = (activeLevel::selectedPiece->position.x - activeLevel::gridStartX) / constants::gridCellSize;
	int pieceToGridY = (activeLevel::selectedPiece->position.y - activeLevel::gridStartY) / constants::gridCellSize;

	if (IsKeyPressed(KEY_R))
		activeLevel::selectedPiece->rotate90Clockwise();

	if (IsMouseButtonReleased(0))
	{
		float pieceToGridActualX = activeLevel::gridStartX + (constants::gridCellSize * pieceToGridX);
		float pieceToGridActualY = activeLevel::gridStartY + (constants::gridCellSize * pieceToGridY);

		if ((pieceToGridX >= 0 && pieceToGridX < activeLevel::level.gridCellWidth) && (pieceToGridY >= 0 && pieceToGridY < activeLevel::level.gridCellHeight) && !checkOverlappingPieces(pieceToGridX, pieceToGridY))
		{
			activeLevel::selectedPiece->position.x = pieceToGridActualX;
			activeLevel::selectedPiece->position.y = pieceToGridActualY;
		}
		else
		{
			activeLevel::selectedPiece->position = activeLevel::selectedPiece->startPosition;
		}

		updateSolutionGrid();

		if (checkSolution())
		{
			printf("SUCCESS!\n");
		}

		activeLevel::selectedPiece = NULL;
	}
}

bool checkOverlappingPieces(int pieceToGridX, int pieceToGridY)
{
	int pieceRows = activeLevel::selectedPiece->pieceLayout.size();
	int pieceCols = activeLevel::selectedPiece->pieceLayout[0].size();

	int gridRows = activeLevel::level.levelGrid.size();
	int gridCols = activeLevel::level.levelGrid[0].size();

	for (int row = 0; row < pieceRows; row++)
	{
		for (int col = 0; col < pieceCols; col++)
		{
			//Only the filled parts of the grid
			if (activeLevel::selectedPiece->pieceLayout[row][col] != 1)
				continue;

			int gridX = pieceToGridX + col;
			int gridY = pieceToGridY + row;

			//Check if it's outside the grid
			if (gridY < 0 || gridY >= gridRows || gridX < 0 || gridX >= gridCols)
				return true;

			//Check if overlapping with another piece in activeSolutionGrid
			if (activeLevel::activeSolutionGrid[gridY][gridX] == 1)
				return true;

			//Check if on an invalid tile in levelGrid, only allowed on empty cells and roadworks
			int tileValue = activeLevel::level.levelGrid[gridY][gridX];

			if (tileValue != 0 && tileValue != 1)
				return true;
		}
	}

	return false;
}


void updateSolutionGrid()
{
	resetSolutionGrid();

	for (int i = 0; i < activeLevel::pieces.size(); i++)
	{
		Piece* piece = &activeLevel::pieces[i];

		int pieceToGridX = (piece->position.x - activeLevel::gridStartX) / constants::gridCellSize;
		int pieceToGridY = (piece->position.y - activeLevel::gridStartY) / constants::gridCellSize;

		if ((pieceToGridX >= 0 && pieceToGridX < activeLevel::level.gridCellWidth) && (pieceToGridY >= 0 && pieceToGridY < activeLevel::level.gridCellHeight))
		{
			for (int x = 0; x < piece->pieceLayout.size(); x++)
			{
				for (int y = 0; y < piece->pieceLayout[0].size(); y++)
				{
					if (activeLevel::activeSolutionGrid[pieceToGridX + y][pieceToGridY + x] == 0)
						activeLevel::activeSolutionGrid[pieceToGridX + y][pieceToGridY + x] = piece->pieceLayout[x][y];
				}
			}
		}
	}
}

void checkPieceSelection()
{
	for (int i = 0; i < activeLevel::pieces.size(); i++)
	{
		Piece* piece = &activeLevel::pieces[i];

		int startX = piece->position.x;
		int startY = piece->position.y;

		int endX = piece->position.x + (piece->pieceLayout[0].size() * constants::gridCellSize);
		int endY = piece->position.y + (piece->pieceLayout.size() * constants::gridCellSize);

		if ((GetMousePosition().x >= startX && GetMousePosition().x <= endX) && (GetMousePosition().y >= startY && GetMousePosition().y <= endY))
		{
			if (activeLevel::hoveredPiece == NULL || activeLevel::hoveredPiece == piece)
			{
				piece->isHighlighted = true;
				activeLevel::hoveredPiece = piece;

				if (IsMouseButtonDown(0) && activeLevel::selectedPiece == NULL)
				{
					activeLevel::selectedPiece = piece;
					activeLevel::dragOffset.x = GetMousePosition().x - activeLevel::selectedPiece->position.x;
					activeLevel::dragOffset.y = GetMousePosition().y - activeLevel::selectedPiece->position.y;
				}
			}
		}
		else if (piece != activeLevel::selectedPiece)
		{
			piece->isHighlighted = false;
			activeLevel::hoveredPiece = NULL;
		}
	}
}

bool checkSolution()
{
	for (int x = 0; x < activeLevel::activeSolutionGrid.size(); x++)
	{
		for (int y = 0; y < activeLevel::activeSolutionGrid[0].size(); y++)
		{
			if (activeLevel::level.solutionGrid[y][x] != activeLevel::activeSolutionGrid[x][y])
				return false;
		}
	}

	return true;
}