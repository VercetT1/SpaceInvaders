#pragma once
#include "raylib.h"
#include <string>
#include "../include/settings.hpp"
class Menu{
public:
	Menu(Font& font);
	~Menu();
	void Draw();
	void Update();
	void HandleInput();

private:
	Texture2D logo;
	Texture2D alienA;
	Texture2D alienB;
	Texture2D alienC;
	Texture2D mysteryShip;
	Font font;
	std::string keysInstructions;
	float ShowMessageTime;
	bool ShowMessage;
	
};
