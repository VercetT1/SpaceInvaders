#include "../include/deathBallPowerUp.hpp"


DeathBall::DeathBall(Vector2 position, float radius)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->radius = radius;
	firstColor = { 255,72,0,240 };
	secondColor = { 242,255,0,240 };
	ballState = INACTIVE;
	color = WHITE;
	colorInterval = 0.25f;
	lastTimeColorChanged = 0.0f;
	colorNum = 0;

}

DeathBall::DeathBall()
{
}


void DeathBall::Draw()
{
	if (ballState == ACTIVE || ballState == LOADING) {
		DrawCircle(position.x, position.y, radius, color);
	}

}

void DeathBall::Update()
{
	if (ballState == ACTIVE) {
		float currentTime = GetTime();
		if (currentTime - lastTimeColorChanged >= colorInterval) {
			lastTimeColorChanged = (float)GetTime();
			if (colorNum == 0) {
				color = GREEN;
				colorNum = 1;
			}
			else {
				color = WHITE;
				colorNum = 0;
			}
		}
		if (position.y >= 0) {
			position.y -= deathBallSpeed;
		}
		else {
			ballState = INACTIVE;
			removeBall();
		}
	}
}

void DeathBall::IncreaseRadius()
{
	if (radius < 50) {
		radius += 1;
	}
	else {
		ballState = ACTIVE;
	}

}

void DeathBall::makeBallActive()
{
	ballState = ACTIVE;
}

void DeathBall::loadBall()
{
	ballState = LOADING;
}

void DeathBall::removeBall()
{
	radius = 3.0f;
	changePosition({ -30,-30 });
	ballState = INACTIVE;
}

void DeathBall::changePosition(Vector2 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

ObjectState DeathBall::GetState()
{
	return ballState;
}

std::vector<Vector2> DeathBall::GetBallPoints()
{
	std::vector<Vector2> points;
	if (ballState == ACTIVE || ballState == LOADING) {
		for (float angle = 0; angle < 360; angle += 1.0f) {
			float theta = angle * DEG2RAD; // Convert degrees to radians
			float x = position.x + radius * cosf(theta);
			float y = position.y + radius * sinf(theta);
			points.push_back({ x, y });
		}
	}
	return points;
}
