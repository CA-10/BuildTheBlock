#include "gameLogic.h"
#include "gameRendering.h"
#include "levels.h"

void start();
void update();
void render();

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
	activeLevel::level = levels::level1;

	resetSolutionGrid();
	loadPieces();
}

void update()
{
	checkPieceSelection();
	updateSelectedPiece();
}

void render()
{
	renderGrid();
	renderPieces();
}