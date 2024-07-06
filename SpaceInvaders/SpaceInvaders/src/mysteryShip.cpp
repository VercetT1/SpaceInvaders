#include "../include/mysteryShip.hpp"

MysteryShip::MysteryShip()
{
	image = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/mysteryShip.png");
	destructionImage = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/mysteryShipExplosion.png");
	mysteryShipState = INACTIVE;
	position = { -30,-30 };
	explodingTime = 0.25f;
	speed = 0;
}

MysteryShip::~MysteryShip()
{
	UnloadTexture(image);
	UnloadTexture(destructionImage);
}

void MysteryShip::Update()
{
	if (mysteryShipState == ACTIVE) {
		position.x += speed;
		if (position.x  > GetScreenWidth() || position.x < 0) {
			mysteryShipState = INACTIVE;
		}
	}
	if (mysteryShipState == EXPLODING) {
		explodingTime -= GetFrameTime();
		if (explodingTime < 0) {
			mysteryShipState = INACTIVE;
			explodingTime = 0.25f;
			position = { -30,-30 };
		}
	}
}

void MysteryShip::Draw()
{
	if (mysteryShipState == ACTIVE) {
		DrawTextureV(image, position, WHITE);
	}
	else if (mysteryShipState == EXPLODING) {
		DrawTextureV(destructionImage, position, RED);
	}
}

void MysteryShip::Spawn()
{
	position.y = 60;
	int side = GetRandomValue(0, 1);
	if (side == 0) {
		position.x = 0;
		speed = mysteryShipSpeed;
	}
	else {
		position.x = float(GetScreenWidth() - image.width);
		speed = -mysteryShipSpeed;
	}
	mysteryShipState = ACTIVE;
}

Rectangle MysteryShip::getRect()
{
	if (mysteryShipState == ACTIVE) {
		return { position.x,position.y,float(image.width),float(image.height) };
	}
	else if(mysteryShipState == INACTIVE) {
		return { position.x,position.y,0,0 };
	}
}

void MysteryShip::SetState(ObjectState state)
{
	mysteryShipState = state;
}

ObjectState MysteryShip::GetState()
{
	return mysteryShipState;
}
