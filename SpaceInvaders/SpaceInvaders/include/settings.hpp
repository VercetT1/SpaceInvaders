#pragma once
#include "enums.hpp"
#include "raylib.h"

constexpr int windowHeight = 512;
constexpr int windowWidth = 500;
constexpr int targetFPS = 60;
constexpr float moveLeftPixels = 2.5f;
constexpr float moveRightPixels = 2.5f;
constexpr int spaceshipLaserSpeed = 6;
constexpr float spriteTime = 0.5f;
constexpr int alienLaserSpeed = 3;
extern float alienLaserShootInterval;
constexpr float alienExplosionTime = 0.25f;
constexpr float machineGunPowerUpTotalTime = 4.5f;
constexpr float mysteryShipSpeed = 2.5f;
constexpr float deathBallSpeed = 3.5f;
extern float playerShootIntervalTime;
extern float movementSpeed;
extern float machineGunPowerUpCurrentTime;
extern int lives;
extern int highScore;
extern int NumOfMachineGunBonus;
extern int NumOfSniperBonus;
extern int NumOfDeathBallBonus;
extern Screen CurrentScreen;
void SetScreen(Screen screen);

