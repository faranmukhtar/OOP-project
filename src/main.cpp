#include "raylib.h"
#include "resource_dir.h"
#include "game.h"

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 800, "Shadow Sprint");

	SearchAndSetResourceDir("resources");
	
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Hello from Hammad", 200,200,20,WHITE);
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
