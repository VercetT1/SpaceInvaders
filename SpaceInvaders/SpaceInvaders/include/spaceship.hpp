#pragma once

#include<raylib.h>
#include "laser.hpp"
#include<vector>
#include "deathBallPowerUp.hpp"

class Spaceship {
public: // public methods
	Spaceship();
	~Spaceship();
	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	void FireDeathBall();
	void Reset();
	void SetState(ObjectState state);
	PowerUps GetPowerUp();
	void SetPowerUp(PowerUps powerUp);
	Rectangle getRect();
	std::vector<Laser> spaceShipLasers;
	DeathBall deathBall;
	ObjectState spaceShipState;
	Texture2D spaceshipImage;

private: // private member variables
	PowerUps powerUp;
	Vector2 position;
	Texture2D spaceShipDestructionSprites[2];
	float lastSpriteChange;
	int currentSpriteIndex;
	float machineGunSoundTime;

	


};
