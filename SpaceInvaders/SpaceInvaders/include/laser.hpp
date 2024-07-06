#pragma once
#include "raylib.h"
#include "enums.hpp"
#include "settings.hpp"

class Laser {
public:
	Laser(Vector2 position, ObjectState activity, Color color);
	Laser();
	static Sound machineGunSound;
	static void UnloadImagesAndSounds();
	virtual void Update();
	virtual void Draw();
	virtual Rectangle getRect();
	void ChangeColor(Color color);

	//Checks if the laser is currently on the screen or is being exploded.
	ObjectState GetActivity() const;
	void SetLaserState(ObjectState state);
	

protected:
	static Texture2D explosionImage;
	Vector2 position;
	ObjectState activity;
	float explosionTime;
	Color laserColor;

private:
	
	
	
};

