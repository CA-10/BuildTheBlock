#include "raylib.h"
#include "colours.h"
#include "constants.h"
#include "levels.h"

void start();
void update();
void render();
void renderGrid();

Level selectedLevel;

int main()
{
	InitWindow(constants::screenWidth, constants::screenHeight, "Build The Block");
	SetTargetFPS(60);

	start();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(customColours::backgroundGreen);

		update();
		render();

		EndDrawing();
	}

	CloseWindow();
}

void start()
{
	selectedLevel = levels::level1;
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

			Color cellBackgroundColour;

			switch (gridMarker)
			{
				//Empty cell
				case 0:
				{
					cellBackgroundColour = customColours::gridGrey;
				}
				break;

				//Roadworks
				case 1:
				{
					cellBackgroundColour = customColours::roadworksOrange;
				}
				break;

				default:
				{
					cellBackgroundColour = customColours::gridGrey;
				}
				break;
			}
			
			DrawRectangle(actualX, actualY, constants::gridCellSize, constants::gridCellSize, cellBackgroundColour);
			DrawRectangleLines(actualX, actualY, constants::gridCellSize, constants::gridCellSize, BLACK);
			actualX += constants::gridCellSize;
		}

		actualX = startX;
		actualY += constants::gridCellSize;
	}
}