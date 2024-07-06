#include "../include/menu.hpp"

Menu::Menu(Font& font)
{
	logo = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/Logo.png");
	alienA = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/alienA.png");
	alienB = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/alienB.png");
	alienC = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/alienC.png");
	mysteryShip = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/mysteryShip.png");
	this->font = font;
	keysInstructions = "D - DEATHBALL (LONG PRESS!)\n\nM - Machine Gun\n\nS - Snipe aliens with your mouse!";
	ShowMessageTime = 0.5f;
	ShowMessage = false;
}

Menu::~Menu()
{
	UnloadTexture(logo);
	UnloadTexture(alienA);
	UnloadTexture(alienB);
	UnloadTexture(alienC);
	UnloadTexture(mysteryShip);
}

void Menu::Draw()
{
	//BeginDrawing();
	DrawTexture(logo, (GetScreenWidth() - logo.width) / 2, 50, WHITE);
	DrawTexture(alienA, (GetScreenWidth() - alienA.width) / 2 - 50, 140, WHITE);
	DrawTextEx(font, " = 30", { (float)(GetScreenWidth() - alienA.width) / 2 + 45 - 50, 135 }, 39, 0, WHITE);
	DrawTexture(alienB, (GetScreenWidth() - alienB.width) / 2 - 50, 200, WHITE);
	DrawTextEx(font, " = 20", { (float)(GetScreenWidth() - alienB.width) / 2 + 45 - 50, 190 }, 39, 0, WHITE);
	DrawTexture(alienC, (GetScreenWidth() - alienC.width) / 2 - 50, 250, WHITE);
	DrawTextEx(font, " = 10", { (float)(GetScreenWidth() - alienC.width) / 2 + 45 - 50, 240 }, 39, 0, WHITE);
	DrawTexture(mysteryShip, (GetScreenWidth() - mysteryShip.width) / 2 - 50, 310, WHITE);
	DrawTextEx(font, " = ?", { (float)(GetScreenWidth() - mysteryShip.width) / 2 + 45 - 37, 300 }, 39, 1, WHITE);
	DrawTextEx(font, keysInstructions.c_str(), { 60, 360 }, 22, 2, WHITE);
	if (ShowMessage) {
		DrawTextEx(font, "PRESS ENTER TO START!", { (float)GetScreenWidth()/4 - 20,(float)GetScreenHeight() - 50}, 25, 3, WHITE);
	}

	//EndDrawing();
}

void Menu::Update()
{
	ShowMessageTime -= GetFrameTime();
	if (ShowMessageTime <= 0) {
		if (ShowMessage == true) {
			ShowMessage = false;
		}
		else {
			ShowMessage = true;
		}
		ShowMessageTime = 0.5f;
	}
}

void Menu::HandleInput()
{
	if (IsKeyReleased(KEY_ENTER)) {
		SetScreen(GAME_WINDOW);
	}
}
