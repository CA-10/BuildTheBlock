#include "gameRendering.h"

std::unordered_map<std::string, Texture2D> texturesMap = std::unordered_map<std::string, Texture2D>();

void loadTextures()
{
	texturesMap["maintenanceTileTexture"] = LoadTexture("res\\maintenanceTile.png");
	texturesMap["passengerTileTexture"] = LoadTexture("res\\passengerTile.png");
	texturesMap["destinationTileTexture"] = LoadTexture("res\\destinationTile.png");
	texturesMap["carTileTexture"] = LoadTexture("res\\carTile.png");
	texturesMap["tunnelTileTexture"] = LoadTexture("res\\tunnelTile.png");
}

void renderPieces()
{
	for (Piece piece : activeLevel::pieces)
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
	activeLevel::gridStartX = (int)(constants::screenWidth / 2) - (activeLevel::level.gridCellWidth * (constants::gridCellSize / 2));
	activeLevel::gridStartY = (int)(constants::screenHeight / 2) - (activeLevel::level.gridCellHeight * (constants::gridCellSize / 2));

	int actualX = activeLevel::gridStartX;
	int actualY = activeLevel::gridStartY;

	for (int x = 0; x < activeLevel::level.gridCellHeight; x++)
	{
		if (activeLevel::level.levelGrid.size() <= x)
			continue;

		for (int y = 0; y < activeLevel::level.gridCellWidth; y++)
		{
			if (activeLevel::level.levelGrid[x].size() <= y)
				continue;

			int gridMarker = activeLevel::level.levelGrid[x][y];

			DrawRectangle(actualX, actualY, constants::gridCellSize, constants::gridCellSize, customColours::gridGrey);

			Texture2D* tileTexture = NULL;

			switch (gridMarker)
			{
				//Roadworks
			case 1:
			{
				tileTexture = &texturesMap["maintenanceTileTexture"];
			}
			break;

			//Passenger
			case 2:
			{
				tileTexture = &texturesMap["passengerTileTexture"];
			}
			break;

			//Car
			case 3:
			{
				float width = texturesMap["carTileTexture"].width;
				float height = texturesMap["carTileTexture"].height;

				DrawTexturePro(texturesMap["carTileTexture"],
					Rectangle{ 0.0f, 0.0f, width, height },
					{ (float)actualX + width / 2.0f, (float)actualY + height / 2.0f, (float)width, (float)height },
					Vector2{ width / 2.0f, height / 2.0f },
					activeLevel::level.carRotation,
					WHITE);
			}
			break;

			//Destination
			case 4:
			{
				tileTexture = &texturesMap["destinationTileTexture"];
			}
			break;

			//Tunnel
			case 5:
			{
				tileTexture = &texturesMap["tunnelTileTexture"];
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

		actualX = activeLevel::gridStartX;
		actualY += constants::gridCellSize;
	}
}

void unloadTextures()
{
	for (auto it = texturesMap.begin(); it != texturesMap.end(); ++it)
	{
		UnloadTexture(it->second);
	}
}