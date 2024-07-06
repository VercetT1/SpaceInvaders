#pragma once
#include "laser.hpp"
#include "raylib.h"
class AlienLaser :public Laser {
public:
	AlienLaser(Vector2 position, ObjectState activity, Color color,int laserType);
	void Update();
	void Draw();
	Rectangle getRect();
	int GetAlienLaserType();
	static void UnloadImages();

private:

	int currentSpriteNum;
	float alienLaserSpriteTime;
	Rectangle shotsSprites[4];

public:
	int laserType;
	static Texture2D alienLaserShot_A;
	static Texture2D alienLaserShot_B;
};
