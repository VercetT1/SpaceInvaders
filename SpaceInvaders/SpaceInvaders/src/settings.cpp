#include "../include/settings.hpp"

float movementSpeed = 0.03f;
float playerShootIntervalTime = 0.5f;
float machineGunPowerUpCurrentTime = 0.0f;
float alienLaserShootInterval = 1.7f;
//1.7f
int lives = 3;
Screen CurrentScreen;
int highScore = 0;
int NumOfMachineGunBonus = 0;
int NumOfSniperBonus =0;
int NumOfDeathBallBonus=0;


void SetScreen(Screen screen) {
	CurrentScreen = screen;
}

