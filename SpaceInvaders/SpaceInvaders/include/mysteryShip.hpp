#pragma once
#include "raylib.h"
#include "settings.hpp"
#include "enums.hpp"

class MysteryShip {
public:
	MysteryShip();
	~MysteryShip();
	void Update();
	void Draw();
	void Spawn();
	Rectangle getRect();
	void SetState(ObjectState state);
	ObjectState GetState();

private:
	Vector2 position;
	Texture2D image;
	float speed;
	float explodingTime;
	ObjectState mysteryShipState;
	Texture2D destructionImage;
};
