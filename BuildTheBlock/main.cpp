#include "raylib.h"

const int screenWidth = 1600;
const int screenHeight = 800;

void start();
void update();
void render();

int main()
{
	InitWindow(screenWidth, screenHeight, "Build The Block");
	SetTargetFPS(60);

	start();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		update();
		render();

		EndDrawing();
	}

	CloseWindow();
}

void start()
{

}

void update()
{

}

void render()
{

}