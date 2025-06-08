#include "raylib.h"
#include "colours.h"
#include "constants.h"
#include "levels.h"
#include <unordered_map>
#include "pieces.h"

void start();
void resetSolutionGrid();
void loadTextures();
void loadPieces();
void update();
void updateSolutionGrid();
void checkPieceSelection();
void updateSelectedPiece();
bool checkSolution();
bool checkOverlappingPieces(int pieceToGridX, int pieceToGridY);
void render();
void renderGrid();
void renderPieces();
void unloadTextures();

Level selectedLevel;
std::vector<Piece> activePieces;
Piece* selectedPiece = NULL;
Piece* hoveredPiece = NULL;
Vector2 dragOffset = Vector2();
std::vector<std::vector<int>> activeSolutionGrid;

int gridStartX = 0;
int gridStartY = 0;

namespace textures
{
	std::unordered_map<std::string, Texture2D> texturesMap = std::unordered_map<std::string, Texture2D>();
}

int main()
{
	InitWindow(constants::screenWidth, constants::screenHeight, "Build The Block");
	SetTargetFPS(60);

	start();
	loadTextures();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(customColours::backgroundGreen);

		update();
		render();

		EndDrawing();
	}

	unloadTextures();
	CloseWindow();
}

void start()
{
	selectedLevel = levels::level1;

	resetSolutionGrid();
	loadPieces();
}

void resetSolutionGrid()
{
	activeSolutionGrid = std::vector<std::vector<int>>();

	for (int x = 0; x < selectedLevel.levelGrid.size(); x++)
	{
		std::vector<int> row = std::vector<int>();

		for (int y = 0; y < selectedLevel.levelGrid[0].size(); y++)
		{
			row.push_back(0);
		}

		activeSolutionGrid.push_back(row);
	}
}

void loadTextures()
{
	textures::texturesMap["maintenanceTileTexture"] = LoadTexture("res\\maintenanceTile.png");
	textures::texturesMap["passengerTileTexture"] = LoadTexture("res\\passengerTile.png");
	textures::texturesMap["destinationTileTexture"] = LoadTexture("res\\destinationTile.png");
	textures::texturesMap["carTileTexture"] = LoadTexture("res\\carTile.png");
	textures::texturesMap["tunnelTileTexture"] = LoadTexture("res\\tunnelTile.png");
}

void loadPieces()
{
	activePieces = std::vector<Piece>();

	int offsetY = 0;

	for (std::string pieceName : selectedLevel.levelPieces)
	{
		Piece* piece = &pieces::piecesMap[pieceName];

		piece->startPosition = Vector2{ piece->position.x, piece->position.y + offsetY };
		piece->position = piece->startPosition;

		activePieces.push_back(*piece);

		offsetY += (piece->pieceLayout.size() * constants::gridCellSize) + constants::gridCellSize;
	}
}

void update()
{
	checkPieceSelection();
	updateSelectedPiece();
}

void updateSelectedPiece()
{
	if (selectedPiece == NULL)
		return;

	selectedPiece->position.x = GetMousePosition().x - dragOffset.x;
	selectedPiece->position.y = GetMousePosition().y - dragOffset.y;

	int pieceToGridX = (selectedPiece->position.x - gridStartX) / constants::gridCellSize;
	int pieceToGridY = (selectedPiece->position.y - gridStartY) / constants::gridCellSize;

	if (IsKeyPressed(KEY_R))
		selectedPiece->rotate90Clockwise();

	if (IsMouseButtonReleased(0))
	{
		float pieceToGridActualX = gridStartX + (constants::gridCellSize * pieceToGridX);
		float pieceToGridActualY = gridStartY + (constants::gridCellSize * pieceToGridY);

		if ((pieceToGridX >= 0 && pieceToGridX < selectedLevel.gridCellWidth) && (pieceToGridY >= 0 && pieceToGridY < selectedLevel.gridCellHeight) && !checkOverlappingPieces(pieceToGridX, pieceToGridY))
		{
			selectedPiece->position.x = pieceToGridActualX;
			selectedPiece->position.y = pieceToGridActualY;

			if (checkSolution())
			{
				printf("SUCCESS!\n");
			}
		}
		else
		{
			selectedPiece->position = selectedPiece->startPosition;
		}

		updateSolutionGrid();
		selectedPiece = NULL;
	}
}

bool checkOverlappingPieces(int pieceToGridX, int pieceToGridY)
{
	for (int x = 0; x < selectedPiece->pieceLayout.size(); x++)
	{
		for (int y = 0; y < selectedPiece->pieceLayout[0].size(); y++)
		{
			//Check if piece is actually fully on the grid. If not, return false because same behaviour as overlapping
			if ((pieceToGridX + y < 0 || pieceToGridX + y >= selectedLevel.solutionGrid.size()) || (pieceToGridY + x < 0 || pieceToGridY + x >= selectedLevel.solutionGrid[0].size()))
				return true;

			if (activeSolutionGrid[pieceToGridX + y][pieceToGridY + x] == 1 && selectedPiece->pieceLayout[x][y] == 1)
			{
				return true;
			}
		}
	}

	return false;
}

void updateSolutionGrid()
{
	resetSolutionGrid();

	for (int i = 0; i < activePieces.size(); i++)
	{
		Piece* piece = &activePieces[i];

		int pieceToGridX = (piece->position.x - gridStartX) / constants::gridCellSize;
		int pieceToGridY = (piece->position.y - gridStartY) / constants::gridCellSize;

		if ((pieceToGridX >= 0 && pieceToGridX < selectedLevel.gridCellWidth) && (pieceToGridY >= 0 && pieceToGridY < selectedLevel.gridCellHeight))
		{
			for (int x = 0; x < piece->pieceLayout.size(); x++)
			{
				for (int y = 0; y < piece->pieceLayout[0].size(); y++)
				{
					if (activeSolutionGrid[pieceToGridX + y][pieceToGridY + x] == 0)
						activeSolutionGrid[pieceToGridX + y][pieceToGridY + x] = piece->pieceLayout[x][y];
				}
			}
		}
	}
}

void checkPieceSelection()
{
	for (int i = 0; i < activePieces.size(); i++)
	{
		Piece* piece = &activePieces[i];

		int startX = piece->position.x;
		int startY = piece->position.y;

		int endX = piece->position.x + (piece->pieceLayout[0].size() * constants::gridCellSize);
		int endY = piece->position.y + (piece->pieceLayout.size() * constants::gridCellSize);

		if ((GetMousePosition().x >= startX && GetMousePosition().x <= endX) && (GetMousePosition().y >= startY && GetMousePosition().y <= endY))
		{
			if (hoveredPiece == NULL || hoveredPiece == piece)
			{
				piece->isHighlighted = true;
				hoveredPiece = piece;

				if (IsMouseButtonDown(0) && selectedPiece == NULL)
				{
					selectedPiece = piece;
					dragOffset.x = GetMousePosition().x - selectedPiece->position.x;
					dragOffset.y = GetMousePosition().y - selectedPiece->position.y;
				}
			}
		}
		else if (piece != selectedPiece)
		{
			piece->isHighlighted = false;
			hoveredPiece = NULL;
		}
	}
}

bool checkSolution()
{
	for (int x = 0; x < activeSolutionGrid.size(); x++)
	{
		for (int y = 0; y < activeSolutionGrid[0].size(); y++)
		{
			if (selectedLevel.solutionGrid[y][x] != activeSolutionGrid[x][y])
				return false;
		}
	}

	return true;
}

void render()
{
	renderGrid();
	renderPieces();
}

void renderPieces()
{
	for (Piece piece : activePieces)
	{
		int initialX = piece.position.x;

		int actualX = piece.position.x;
		int actualY = piece.position.y;

		for (int x = 0; x < piece.pieceLayout.size(); x++)
		{
			for (int y = 0; y < piece.pieceLayout[0].size(); y++)
			{
				if (piece.pieceLayout[x][y] == 1)
				{
					DrawRectangle(actualX, actualY, constants::gridCellSize, constants::gridCellSize, piece.pieceColour);

					Color outlineColour = BLACK;

					if (piece.isHighlighted)
						outlineColour = WHITE;
					
					DrawRectangleLines(actualX, actualY, constants::gridCellSize, constants::gridCellSize, outlineColour);
				}

				actualX += constants::gridCellSize;
			}

			actualX = initialX;
			actualY += constants::gridCellSize;
		}
	}
}

void renderGrid()
{
	gridStartX = (int)(constants::screenWidth / 2) - (selectedLevel.gridCellWidth * (constants::gridCellSize / 2));
	gridStartY = (int)(constants::screenHeight / 2) - (selectedLevel.gridCellHeight * (constants::gridCellSize / 2));

	int actualX = gridStartX;
	int actualY = gridStartY;

	for (int x = 0; x < selectedLevel.gridCellHeight; x++)
	{
		if (selectedLevel.levelGrid.size() <= x)
			continue;

		for (int y = 0; y < selectedLevel.gridCellWidth; y++)
		{
			if (selectedLevel.levelGrid[x].size() <= y)
				continue;

			int gridMarker = selectedLevel.levelGrid[x][y];

			DrawRectangle(actualX, actualY, constants::gridCellSize, constants::gridCellSize, customColours::gridGrey);

			Texture2D* tileTexture = NULL;

			switch (gridMarker)
			{
				//Roadworks
				case 1:
				{
					tileTexture = &textures::texturesMap["maintenanceTileTexture"];
				}
				break;

				//Passenger
				case 2:
				{
					tileTexture = &textures::texturesMap["passengerTileTexture"];
				}
				break;

				//Car
				case 3:
				{
					float width = textures::texturesMap["carTileTexture"].width;
					float height = textures::texturesMap["carTileTexture"].height;

					DrawTexturePro(	textures::texturesMap["carTileTexture"],
									Rectangle{ 0.0f, 0.0f, width, height }, 
									{ (float)actualX + width / 2.0f, (float)actualY + height / 2.0f, (float)width, (float)height }, 
									Vector2{ width / 2.0f, height / 2.0f }, 
									selectedLevel.carRotation, 
									WHITE);
				}
				break;

				//Destination
				case 4:
				{
					tileTexture = &textures::texturesMap["destinationTileTexture"];
				}
				break;

				//Tunnel
				case 5:
				{
					tileTexture = &textures::texturesMap["tunnelTileTexture"];
				}
				break;

				default:
				{
					DrawRectangle(actualX, actualY, constants::gridCellSize, constants::gridCellSize, customColours::gridGrey);
				}
				break;
			}
			
			if (tileTexture != NULL)
				DrawTexture(*tileTexture, actualX, actualY, WHITE);

			DrawRectangleLines(actualX, actualY, constants::gridCellSize, constants::gridCellSize, BLACK);
			actualX += constants::gridCellSize;
		}

		actualX = gridStartX;
		actualY += constants::gridCellSize;
	}
}

void unloadTextures()
{
	for (auto it = textures::texturesMap.begin(); it != textures::texturesMap.end(); ++it)
	{
		UnloadTexture(it->second);
	}
}