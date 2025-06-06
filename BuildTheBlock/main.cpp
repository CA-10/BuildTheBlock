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
	int actualX = 100;
	int actualY = 100;

	for (int x = 0; x < selectedLevel.gridCellHeight; x++)
	{
		for (int y = 0; y < selectedLevel.gridCellWidth; y++)
		{
			DrawRectangleLines(actualX, actualY, constants::gridCellSize, constants::gridCellSize, BLACK);
			actualX += constants::gridCellSize;
		}

		actualX = 100;
		actualY += constants::gridCellSize;
	}
}