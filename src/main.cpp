#include "raylib.h"
#include "resource_dir.h"
#include "game.h"

int main ()
{
	Game game;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shadow Sprint");

	SetTargetFPS(60);

	SearchAndSetResourceDir("resources");
	
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		game.drawScreen();
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
