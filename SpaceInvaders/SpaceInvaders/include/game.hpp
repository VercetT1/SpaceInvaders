#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "alienLaser.hpp"
#include "mysteryShip.hpp"
#include <string>

class Game {
public: // public methods
	Game(Font& font);
	~Game();
	void Draw();
	void Update();
	void HandleInput();
	void MoveAliens();
	void MoveDownAliens(float distance);
	void CheckForCollisions();
	void HandleObstacleCollisions(Obstacle& obstacle, Block& block);
	void MoveAliensHorizontally(float distance);
	//void LoadSpriteSheets();

// private variables
private:
	Spaceship spaceship;
	MysteryShip mysteryShip;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;
	std::vector<AlienLaser> alienLasers;
	std::vector<int> inputSequence;
	std::vector<int> cheatCode;
	float aliensSpeed;
	float timeLastAlienFired;
	float mysteryShipSpawnInterval;
	float timeLastSpawn;
	float timePlayerLastFired;
	float inactiveTime;
	bool IsGameRunning;
	bool StopUpdating;
	Font font;
	float numOfMysteriousShipScoreTime;
	Vector2 mysteryShipExplosion;
	Texture2D sniperImage;
	Texture2D machineGunIcon;
	Texture2D sniperIcon;
	int NumOfSniperAliens;
	bool cheatActivated;
	float cheatActivatedTime;
	float numberOfDownPixels;

	//Sounds
	//Sound alienExplodeSound;
	Sound deathBallSound;
	Sound laserSound;
	//Sound machineGunSound;
	Sound sniperSound;
	Sound playerExplosion;

	//Score variables
	int score;
	int mysteryShipScore;


private: // private methods
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
	void AlienShootLasers();
	void DeleteInactiveLasers();
	void DeleteDeadAliens();
	void RaiseDifficulty();
	void DeleteInactiveBlock();
	void DecreasePowerUpTime();
	void EnablePowerUps();
	void CheckIfLost();
	void GameOver();
	void Reset();
	void InitGame();
	bool CheckIfWin();
	void GetAlienScore(Alien& alien);
	void GetMysteryShipScore(MysteryShip& mysteryShip);
	void StartNextLevel();
	void DrawUserInterface();
	void IncreaseAliensMovementSpeed();
	void CheckForHighScore();


	void WinLevel();
	bool CheckCheatCode(std::vector<int>& inputSequence, const std::vector<int>& cheatCode);

};
