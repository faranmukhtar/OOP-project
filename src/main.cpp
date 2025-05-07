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

	bool closeWindow = false;

	game.loadAssets();

	closeWindow = game.drawLogo();

	game.drawcontrols();

	int num =0;

	while (!WindowShouldClose() && !closeWindow)
	{
		BeginDrawing();

		ClearBackground(BLACK);
		game.displayScores();

		game.takeInput();

		game.updateGame();

		game.drawScreen();


		if(game.checkGameOver()){
			closeWindow = game.drawGameOver();
		}

		EndDrawing();
	}

	game.unloadAssets();

	CloseWindow();
	return 0;
}
