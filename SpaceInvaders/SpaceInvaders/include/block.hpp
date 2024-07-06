#pragma once
#include "raylib.h"
#include "enums.hpp"

class Block {
public:
	Block(Vector2 position);
	void Draw();
	Rectangle getRect();
	ObjectState blockState;
private:
	Vector2 position;
};