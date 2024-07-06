#include "../include/alienLaser.hpp"


Texture2D AlienLaser::alienLaserShot_A;
Texture2D AlienLaser::alienLaserShot_B;

AlienLaser::AlienLaser(Vector2 position, ObjectState activity, Color color, int laserType) :Laser(position, activity, color)
{
	if (alienLaserShot_A.id == 0) {
		alienLaserShot_A = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/AlienLaserShots/shot1/shot1.png");
	}
	if (alienLaserShot_B.id == 0) {
		alienLaserShot_B = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/AlienLaserShots/shot2/shot2.png");
	}

	this->laserType = laserType;
	currentSpriteNum = 0;
	alienLaserSpriteTime = 0;
	//laserColor = color;
	switch (laserType) {
	case 1:
		shotsSprites[0] = { 2,2,8,19 };
		shotsSprites[1] = { 14,2,8,19 };
		shotsSprites[2] = { 26,2,8,19 };
		shotsSprites[3] = { 38,2,8,19 };
		break;
	case 2:
		shotsSprites[0] = { 2,2,8,16 };
		shotsSprites[1] = { 14,2,8,16 };
		shotsSprites[2] = { 26,2,8,16 };
		shotsSprites[3] = { 38,2,8,16 };
		break;
	default:
		shotsSprites[0] = { 2,2,8,19 };
		shotsSprites[1] = { 14,2,8,19 };
		shotsSprites[2] = { 26,2,8,19 };
		shotsSprites[3] = { 38,2,8,19 };
		break;
	}
}

void AlienLaser::Update()
{
	if (activity == ACTIVE) {
		position.y += alienLaserSpeed;
		if (position.y >= (GetScreenHeight() - 160)) {
			laserColor = LIME;
		}
		if (position.y >= (GetScreenWidth() - 25)) {
			activity = EXPLODING;
		}
	}
	else if (activity == EXPLODING) {
		explosionTime -= GetFrameTime();
		if (explosionTime < 0) {
			activity = INACTIVE;
		}
	}

}

void AlienLaser::Draw()
{
	Texture2D alienLaserImage = (laserType == 1) ? alienLaserShot_A : alienLaserShot_B;

	if (activity == ACTIVE) {
		DrawTextureRec(alienLaserImage, shotsSprites[currentSpriteNum], position, laserColor);
		alienLaserSpriteTime += GetFrameTime();
		if (alienLaserSpriteTime > 0.07f) {
			currentSpriteNum++;
			alienLaserSpriteTime = 0.0f;
			if (currentSpriteNum > 3) {
				currentSpriteNum = 0;
			}
		}
	}
	else if (activity == EXPLODING) {
		DrawTextureV(explosionImage, { position.x , position.y - 7.1f }, laserColor);
	}

}

Rectangle AlienLaser::getRect()
{
	return { position.x,position.y,float(shotsSprites[currentSpriteNum].width),float(shotsSprites[currentSpriteNum].height) };
}

int AlienLaser::GetAlienLaserType()
{
	return laserType;
}

void AlienLaser::UnloadImages()
{
	UnloadTexture(alienLaserShot_A);
	UnloadTexture(alienLaserShot_B);
}


