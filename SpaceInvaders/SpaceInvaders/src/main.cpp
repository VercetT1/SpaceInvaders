
#include"../include/settings.hpp"
#include "../include/game.hpp"
#include "../include/menu.hpp"


int main() {
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE|FLAG_VSYNC_HINT);
	InitWindow(windowWidth, windowHeight, "SPACE INVADERS++");
	InitAudioDevice();
	//SetWindowMaxSize(windowWidth, windowHeight);
	SetTargetFPS(targetFPS);

	Font font = LoadFontEx("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/Font/monogram.ttf", 64, 0, 0);

	Menu menu = Menu(font);
	Game game = Game(font);

	SetScreen(Screen::MENU);


	//Game loop

	while (WindowShouldClose() == false) {

		BeginDrawing();
		switch (CurrentScreen) {

		case Screen::MENU:
			menu.Update();
			menu.HandleInput();
			ClearBackground(BLACK);
			menu.Draw();

			break;
		

		case Screen::GAME_WINDOW:
			game.HandleInput();
			game.Update();

			ClearBackground(BLACK);

			game.Draw();

			break;

		}
		EndDrawing();
	}

	UnloadFont(font);
	CloseWindow();
	CloseAudioDevice();
	return 0;
}