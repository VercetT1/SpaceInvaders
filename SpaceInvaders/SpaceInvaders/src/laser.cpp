#include "../include/laser.hpp"
#include <iostream>


Texture2D Laser::explosionImage;
Sound Laser::machineGunSound;

Laser::Laser(Vector2 position, ObjectState activity, Color color)
{
	this->position = position;
	this->activity = activity;
	explosionTime = 0.25f;
	laserColor = color;
	if (machineGunSound.stream.buffer == 0) {
		machineGunSound = LoadSound("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sounds/MachineGun.mp3");
	}

	if (explosionImage.id == 0) {
		explosionImage = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/explosion.png");
	}

}

Laser::Laser()
{
	this->position = { -1,-1 };
	this->activity = INACTIVE;
	explosionTime = 0.5;
	laserColor = RED;
}

void Laser::UnloadImagesAndSounds()
{
	UnloadTexture(explosionImage);
	UnloadSound(machineGunSound);
}



void Laser::Update()
{
	if (activity == ACTIVE) {
		position.y -= spaceshipLaserSpeed;
		if (position.y <= 0) {
			laserColor = RED;
			SetLaserState(EXPLODING);
		}
	}
	else if (activity == EXPLODING) {
		explosionTime -= GetFrameTime();
		if (explosionTime < 0) {
			SetLaserState(INACTIVE);
		}
	}

}

void Laser::Draw()
{
	if (activity == ACTIVE) {
		DrawRectangle((int)position.x, (int)position.y, 2, 10, laserColor);

	}
	else if (activity == EXPLODING) {
		DrawTextureV(explosionImage, position, laserColor);
	}

}

Rectangle Laser::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 2;
	rect.height = 10;
	return rect;
}

void Laser::ChangeColor(Color color)
{
	laserColor = color;
}




ObjectState Laser::GetActivity() const
{
	return activity;
}

void Laser::SetLaserState(ObjectState state)
{
	activity = state;
	if (activity == INACTIVE) {
		position.x = (float)GetScreenHeight();
		position.y = (float)GetScreenWidth();
	}
}


