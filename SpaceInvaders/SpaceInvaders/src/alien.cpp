#include "../include/alien.hpp"


Texture2D Alien::alienSprites;
Texture2D Alien::alienExplosion;
Sound Alien::alienExplosionSound;

Alien::Alien(int type, Vector2 position)
{
	if (alienSprites.id == 0) {
		alienSprites = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/alienSpritesheet.png");
	}
	if (alienExplosion.id == 0) {
		alienExplosion = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/invaderExplosion.png");
	}
	currentSpriteNum = 0;
	currentSpriteRec = { 0,0,0,0 };
	this->alienSpriteTime = spriteTime;
	this->type = type;
	this->position = position;
	alienState = ACTIVE;
	isExploding = false;
	if (alienExplosionSound.stream.buffer == nullptr) {
		alienExplosionSound = LoadSound("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sounds/alienExplode.mp3");
	}

	//Assigning sprites rectangle according to alienSpritesheet.png locations
	switch (type) {
	case 1:
		sprite0 = { 10,10,23,23 };
		sprite1 = { 53,10,23,23 };
		break;
	case 2:
		sprite0 = { 96,10,30,22 };
		sprite1 = { 146,10,30,22 };
		break;
	case 3:
		sprite0 = { 196,10,30,20 };
		sprite1 = { 246,10,30,20 };
		break;
	default:
		sprite0 = { 10,10,23,23 };
		sprite1 = { 53,10,23,23 };
		break;

	}
}

void Alien::Update()
{
	alienSpriteTime -= GetFrameTime();
	if (alienState == ACTIVE) {
		//position.x += direction;
		if (alienSpriteTime < 0) {
			currentSpriteNum = ~currentSpriteNum;
			currentSpriteRec = (currentSpriteNum == 0) ? sprite0 : sprite1;
			alienSpriteTime = spriteTime;
		}
	}
	else if (!isExploding && alienState == EXPLODING) {
		alienSpriteTime = 0.15f;
		PlaySound(alienExplosionSound);
		isExploding = true;
	}


}

void Alien::Draw()
{
	if (alienState == ACTIVE) {
		DrawTextureRec(alienSprites, currentSpriteRec, position, WHITE);
	}
	else if (alienState == EXPLODING) {
		if (alienSpriteTime > 0) {
			DrawTextureV(alienExplosion, position, WHITE);
		}
		else {
			alienState = INACTIVE;
		}
	}
}

int Alien::GetType() const
{
	return type;
}

Rectangle Alien::getRect()
{
	return { position.x,position.y,float(currentSpriteRec.width),float(currentSpriteRec.height) };
}

void Alien::SetState(ObjectState state)
{
	alienState = state;
}

void Alien::UnloadImagesAndSounds()
{
	UnloadTexture(alienSprites);
	UnloadTexture(alienExplosion);
	UnloadSound(alienExplosionSound);
}

ObjectState Alien::GetState() const
{
	return alienState;
}

