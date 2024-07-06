#pragma once
#include "raylib.h"
#include "../include/settings.hpp"
#include "../include/enums.hpp"
class Alien {
	//public methods
public:
	Alien(int type, Vector2 position);
	void Update();
	void Draw();
	int GetType() const;
	Rectangle getRect();
	ObjectState alienState;
	void SetState(ObjectState state);
	static void UnloadImagesAndSounds();
	ObjectState GetState() const;

//public variables
public:
	int type;
	Vector2 position;
	Rectangle currentSpriteRec;
	static Texture2D alienSprites;
	static Texture2D alienExplosion;
	static Sound alienExplosionSound;

//private variables
private:
	float alienSpriteTime;
	char currentSpriteNum;
	Rectangle sprite0;
	Rectangle sprite1;
	bool isExploding;


};