#pragma once
#include "raylib.h"
#include "settings.hpp"
#include "enums.hpp"
#include <vector>

class DeathBall {

public:
	DeathBall(Vector2 position, float radius);
	DeathBall();
	void Draw();
	void Update();
	void IncreaseRadius();
	void makeBallActive();
	void loadBall();
	void removeBall();
	void changePosition(Vector2 position);
	float radius;
	ObjectState GetState();
	std::vector<Vector2> GetBallPoints();

private:
	Vector2 position;
	Color firstColor;
	Color secondColor;
	ObjectState ballState;
	Color color;
	float colorInterval;
	float lastTimeColorChanged;
	int colorNum;

};
