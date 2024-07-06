#include "../include/spaceship.hpp"
#include "../include/settings.hpp"


Spaceship::Spaceship()
{
	spaceshipImage = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/spaceship.png");
	spaceShipDestructionSprites[0] = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/playerExplosionA.png");
	spaceShipDestructionSprites[1] = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/playerExplosionB.png");
	position.x = (float)(GetScreenWidth() - spaceshipImage.width) / 2;
	position.y = (float)(GetScreenHeight() - spaceshipImage.height - 50);
	powerUp = NONE;
	deathBall = DeathBall({ -30, -30 }, 3.0f);
	spaceShipState = ACTIVE;
	lastSpriteChange = 0.0f;
	currentSpriteIndex = 0;
	machineGunSoundTime = 0.001f;

}

Spaceship::~Spaceship()
{
	for (int i = 0; i < 2; i++) {
		UnloadTexture(spaceShipDestructionSprites[i]);
	}
	UnloadTexture(spaceshipImage);
}

void Spaceship::Draw()
{
	if (spaceShipState == ACTIVE) {
		DrawTextureV(spaceshipImage, position, WHITE);
	}
	else if (spaceShipState == INACTIVE) {
		float currentTime = (float)GetTime();
		if (currentTime - lastSpriteChange <= 0.25f) {
			DrawTextureV(spaceShipDestructionSprites[currentSpriteIndex], position, { 44,255,48,255 });
		}
		else {
			currentSpriteIndex = currentSpriteIndex == 1 ? 0 : 1;
			lastSpriteChange = (float)GetTime();
		}
	}

}

void Spaceship::MoveLeft()
{
	if (spaceShipState == ACTIVE) {
		position.x -= moveLeftPixels;
		if (position.x < 0) {
			position.x = 0;
		}
	}


}

void Spaceship::MoveRight()
{
	if (spaceShipState == ACTIVE) {
		position.x += moveRightPixels;
		if (position.x > (GetScreenWidth() - spaceshipImage.width)) {
			position.x = (float)(GetScreenWidth() - spaceshipImage.width);
		}
	}
}

void Spaceship::FireLaser()
{
	if (spaceShipState == ACTIVE) {
		if (powerUp == NONE) {
			spaceShipLasers.push_back(Laser({ position.x + spaceshipImage.width / 2 - 2,position.y }, ACTIVE, WHITE));
		}
		if (powerUp == MACHINE_GUN) {
			if (!IsSoundPlaying(Laser::machineGunSound)) {
				PlaySound(Laser::machineGunSound);
			}
			else {
				if (machineGunSoundTime > 0) {
					machineGunSoundTime -= GetFrameTime();
				}
				else {
					StopSound(Laser::machineGunSound);
					PlaySound(Laser::machineGunSound);
					machineGunSoundTime = 0.001f;
				}
			}
			spaceShipLasers.push_back(Laser({ position.x,position.y }, ACTIVE, RED));
			spaceShipLasers.push_back(Laser({ position.x + spaceshipImage.width / 2 ,position.y }, ACTIVE, RED));
			spaceShipLasers.push_back(Laser({ position.x + spaceshipImage.width,position.y }, ACTIVE, RED));
		}
	}
}

void Spaceship::FireDeathBall()
{
	if (spaceShipState == ACTIVE) {
		deathBall.changePosition({ position.x + spaceshipImage.width / 2, position.y - 50 });
		deathBall.loadBall();
	}

}

void Spaceship::Reset()
{
	position.x = (float)(GetScreenWidth() - spaceshipImage.width) / 2;
	position.y = (float)(GetScreenHeight() - spaceshipImage.height - 50);
	spaceShipLasers.clear();
	deathBall.removeBall();
	SetState(ObjectState::ACTIVE);
}

void Spaceship::SetState(ObjectState state)
{
	spaceShipState = state;
}

PowerUps Spaceship::GetPowerUp()
{
	return powerUp;
}

void Spaceship::SetPowerUp(PowerUps powerUp)
{
	if (spaceShipState == ACTIVE) {
		this->powerUp = powerUp;
	}

}

Rectangle Spaceship::getRect()
{
	return { position.x,position.y,float(spaceshipImage.width), float(spaceshipImage.height) };

}


