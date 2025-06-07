#include "raylib.h"
#include "colours.h"
#include "constants.h"
#include "levels.h"

void start();
void loadTextures();
void update();
void render();
void renderGrid();
void unloadTextures();

Level selectedLevel;

namespace textures
{
	Texture2D maintenanceTileTexture;
	Texture2D passengerTileTexture;
	Texture2D destinationTileTexture;
	Texture2D carTileTexture;
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
}

void loadTextures()
{
	textures::maintenanceTileTexture = LoadTexture("res\\maintenanceTile.png");
	textures::passengerTileTexture = LoadTexture("res\\passengerTile.png");
	textures::destinationTileTexture = LoadTexture("res\\destinationTile.png");
	textures::carTileTexture = LoadTexture("res\\carTile.png");
}

void update()
{

}

void render()
{
	renderGrid();
}

void renderGrid()
{
	int startX = (int)(constants::screenWidth / 2) - (selectedLevel.gridCellWidth * (constants::gridCellSize / 2));
	int startY = (int)(constants::screenHeight / 2) - (selectedLevel.gridCellHeight * (constants::gridCellSize / 2));

	int actualX = startX;
	int actualY = startY;

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
					tileTexture = &textures::maintenanceTileTexture;
				}
				break;

				//Passenger
				case 2:
				{
					tileTexture = &textures::passengerTileTexture;
				}
				break;

				//Car
				case 3:
				{
					float width = textures::carTileTexture.width;
					float height = textures::carTileTexture.height;

					DrawTexturePro(	textures::carTileTexture, 
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
					tileTexture = &textures::destinationTileTexture;
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

		actualX = startX;
		actualY += constants::gridCellSize;
	}
}

void unloadTextures()
{
	UnloadTexture(textures::maintenanceTileTexture);
	UnloadTexture(textures::passengerTileTexture);
	UnloadTexture(textures::destinationTileTexture);
	UnloadTexture(textures::carTileTexture);
}