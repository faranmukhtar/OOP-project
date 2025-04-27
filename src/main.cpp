#include "raylib.h"
#include "resource_dir.h"
#include "game.h"

int main ()
{
	srand(time(0));
	Game game;
	
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shadow Sprint");

	SetTargetFPS(60);

	SearchAndSetResourceDir("resources");
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		
		ClearBackground(BLACK);

		game.takeInput();

		game.updateGame();
		game.displaygameover();
		game.displayscores();
		
		game.drawScreen();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
