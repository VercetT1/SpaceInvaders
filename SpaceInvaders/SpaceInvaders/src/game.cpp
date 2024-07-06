#include "../include/game.hpp"
#include "../include/obstacle.hpp"
#include "../include/enums.hpp"
#include "../include/deathBallPowerUp.hpp"

Game::Game(Font& font)
{
	InitGame();
	this->font = font;
	sniperImage = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sniper.png");
	machineGunIcon = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/icons/machineGun.png");
	sniperIcon = LoadTexture("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/icons/sniperMark.png");

	//Sounds
	//alienExplodeSound = LoadSound("resources/sounds/alienExplode.mp3");
	laserSound = LoadSound("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sounds/laser.mp3");
	deathBallSound = LoadSound("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sounds/DeathBall.mp3");
	//machineGunSound = LoadSound("resources/sounds/MachineGun.mp3");
	sniperSound = LoadSound("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sounds/sniper.mp3");
	playerExplosion = LoadSound("C:/Users/Shalo/Desktop/SpaceInvaders/SpaceInvaders/resources/sounds/explosion.mp3");

	cheatCode = { KEY_W,KEY_A,KEY_N,KEY_T,KEY_C,KEY_V };
}

Game::~Game()
{
	AlienLaser::UnloadImages();
	Laser::UnloadImagesAndSounds();
	Alien::UnloadImagesAndSounds();
	UnloadTexture(sniperImage);
	UnloadTexture(machineGunIcon);
	UnloadTexture(sniperIcon);
	//UnloadSound(alienExplodeSound);
	UnloadSound(laserSound);
	UnloadSound(deathBallSound);
	UnloadSound(sniperSound);
	UnloadSound(playerExplosion);
}

void Game::Draw()
{
	if (cheatActivated == true) {
		DrawText("CHEAT ACTIVATED! WANT CV? :)", 320, GetScreenHeight() - 20, 9, GREEN);

	}
	if (IsGameRunning == false) {
		mysteryShip.SetState(ObjectState::INACTIVE);
		DrawTextEx(font, "GAME OVER!\n\n", { (float)GetScreenWidth() / 2 - 60,40 }, 20, 3, WHITE);
		DrawTextEx(font, "Press ENTER TO RESTART", { (float)GetScreenWidth() / 2 - 120,70 }, 20, 3, WHITE);
	}
	DrawUserInterface();
	spaceship.Draw();

	for (auto& spaceshipLaser : spaceship.spaceShipLasers) {
		spaceshipLaser.Draw();
	}
	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& alien : aliens) {
		alien.Draw();
	}


	for (auto& alienLaser : alienLasers) {
		alienLaser.Draw();
	}

	mysteryShip.Draw();

	if (spaceship.GetPowerUp() == PowerUps::SNIPER) {
		DrawTextureV(sniperImage, GetMousePosition(), GREEN);
		HideCursor();
		//DisableCursor();
	}
	/*else {
		ShowCursor();
	}*/

	//present mysteryship score on the screen
	if (mysteryShipScore > 0 && numOfMysteriousShipScoreTime > 0) {
		std::string str = std::to_string(mysteryShipScore);
		DrawTextEx(font, str.c_str(), mysteryShipExplosion, 30, 3, WHITE);
	}

	spaceship.deathBall.Draw();

}

void Game::Update()
{
	CheckForHighScore();
	if (cheatActivated == true) {
		cheatActivatedTime -= GetFrameTime();
		if (cheatActivatedTime < 0) {
			cheatActivatedTime = 3.0f;
			cheatActivated = false;
		}
	}

	if (StopUpdating) {
		CheckIfLost();
		return;
	}
	if (IsGameRunning == false && IsKeyDown(KEY_ENTER)) {
		Reset();
		InitGame();
		SetScreen(Screen::MENU);
	}
	if (IsGameRunning == false) {
		for (auto& alien : aliens) {
			alien.Update();
		}
		return;
	}



	//Mysteryship spawn
	double currentTime = GetTime();
	if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
		mysteryShip.Spawn();
		timeLastSpawn = (float)currentTime;
		mysteryShipSpawnInterval = (float)GetRandomValue(10, 20);
	}

	//Spaceship laser movement
	for (auto& spaceshipLaser : spaceship.spaceShipLasers) {
		spaceshipLaser.Update();
	}

	//Aliens movement
	MoveAliens();

	//Aliens lasers creation
	AlienShootLasers();

	//Alien lasers update
	for (auto& alienLaser : alienLasers) {
		alienLaser.Update();

	}

	spaceship.deathBall.Update();
	if (spaceship.deathBall.GetState() == INACTIVE && spaceship.GetPowerUp() == PowerUps::DEATH_BALL) {
		spaceship.SetPowerUp(PowerUps::NONE);
	}

	DeleteInactiveLasers();
	mysteryShip.Update();

	if (mysteryShip.GetState() == ObjectState::INACTIVE && mysteryShipScore > 0) {
		numOfMysteriousShipScoreTime -= GetFrameTime();
		if (numOfMysteriousShipScoreTime < 0) {
			mysteryShipScore = 0;
			numOfMysteriousShipScoreTime = 1;
		}
	}

	CheckForCollisions();
	DeleteDeadAliens();
	DeleteInactiveBlock();
	DecreasePowerUpTime();
	EnablePowerUps();
	CheckIfLost();
	if (CheckIfWin()) {
		StartNextLevel();
	}

}

void Game::HandleInput()
{
	if (IsGameRunning == false) {
		return;
	}

	if (IsKeyReleased(KEY_M) && spaceship.GetPowerUp() == PowerUps::NONE && NumOfMachineGunBonus > 0) {
		NumOfMachineGunBonus--;
		spaceship.SetPowerUp(PowerUps::MACHINE_GUN);
		timePlayerLastFired = 0.0f;
	}
	else if (IsKeyDown(KEY_LEFT) && spaceship.GetPowerUp() != PowerUps::DEATH_BALL) {
		spaceship.MoveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT) && spaceship.GetPowerUp() != PowerUps::DEATH_BALL) {

		spaceship.MoveRight();
	}
	else if (IsKeyReleased(KEY_SPACE) && spaceship.GetPowerUp() == PowerUps::NONE) {
		float currentTime = (float)GetTime();
		if (currentTime - timePlayerLastFired > playerShootIntervalTime) {
			PlaySound(laserSound);
			spaceship.FireLaser();
			timePlayerLastFired = (float)GetTime();
		}
	}
	else if (IsKeyDown(KEY_D)) {

		if (spaceship.deathBall.GetState() == ObjectState::INACTIVE && spaceship.GetPowerUp() == PowerUps::NONE && NumOfDeathBallBonus > 0) {
			PlaySound(deathBallSound);
			NumOfDeathBallBonus--;
			spaceship.FireDeathBall();
			spaceship.SetPowerUp(PowerUps::DEATH_BALL);
		}
		else if (spaceship.deathBall.GetState() == ObjectState::LOADING) {
			spaceship.deathBall.IncreaseRadius();
		}

	}
	else if (IsKeyReleased(KEY_D) && spaceship.GetPowerUp() == PowerUps::DEATH_BALL) {
		spaceship.deathBall.makeBallActive();
	}
	else if (IsKeyPressed(KEY_S) && spaceship.GetPowerUp() == PowerUps::NONE && NumOfSniperBonus > 0) {
		//PlaySound(sniperSound);
		NumOfSniperBonus--;
		spaceship.SetPowerUp(PowerUps::SNIPER);
	}
	else {
		int pressedKey = GetKeyPressed();
		if (pressedKey != 0) {
			inputSequence.push_back(pressedKey);
			if (CheckCheatCode(inputSequence, cheatCode)) {
				WinLevel();
			}
		}
	}
}

void Game::MoveAliens()
{
	MoveAliensHorizontally(movementSpeed);

	for (auto& alien : aliens) {
		if (alien.position.x + alien.currentSpriteRec.width > GetScreenWidth()) {
			movementSpeed = -movementSpeed;
			MoveAliensHorizontally(-2);
			MoveDownAliens(3);
			break;

		}
		else if (alien.position.x < 0) {
			movementSpeed = -movementSpeed;
			MoveAliensHorizontally(2);
			MoveDownAliens(3);
			break;

		}
		alien.Update();
	}

}

void Game::MoveAliensHorizontally(float distance)
{
	for (auto& alien : aliens) {
		//alien.Update(distance);
		alien.position.x += distance;

	}
}

void Game::MoveDownAliens(float distance)
{
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

void Game::CheckForCollisions()
{
	//Spaceship lasers with aliens collsions
	for (auto& alien : aliens) {
		for (auto& spaceShipLaser : spaceship.spaceShipLasers) {
			if (CheckCollisionRecs(alien.getRect(), spaceShipLaser.getRect())) {
				alien.SetState(ObjectState::EXPLODING);
				spaceShipLaser.SetLaserState(ObjectState::INACTIVE);
				GetAlienScore(alien);
				IncreaseAliensMovementSpeed();
				//PlaySound(alienExplodeSound);
			}

		}
	}

	//Spaceship lasers with mystery ship
	for (auto& spaceShipLaser : spaceship.spaceShipLasers) {
		if (CheckCollisionRecs(mysteryShip.getRect(), spaceShipLaser.getRect())) {
			spaceShipLaser.SetLaserState(ObjectState::INACTIVE);
			mysteryShip.SetState(ObjectState::EXPLODING);
			GetMysteryShipScore(mysteryShip);
			//PlaySound(alienExplodeSound);
		}
	}

	//Spaceship lasers with obstacles
	for (auto& obstacle : obstacles) {
		for (auto& block : obstacle.blocks) {
			for (auto& spaceShipLaser : spaceship.spaceShipLasers) {
				if (CheckCollisionRecs(spaceShipLaser.getRect(), block.getRect())) {
					HandleObstacleCollisions(obstacle, block);
					block.blockState = ObjectState::INACTIVE;
					spaceShipLaser.SetLaserState(ObjectState::INACTIVE);

				}
			}
		}
	}

	//Alien lasers with obstacles
	for (auto& obstacle : obstacles) {
		for (auto& block : obstacle.blocks) {
			for (auto& alienLaser : alienLasers) {
				if (CheckCollisionRecs(alienLaser.getRect(), block.getRect())) {
					HandleObstacleCollisions(obstacle, block);
					block.blockState = ObjectState::INACTIVE;
					alienLaser.SetLaserState(ObjectState::INACTIVE);

				}
			}
		}
	}

	//Alien lasers with player spaceship laser
	for (auto& alienLaser : alienLasers) {
		for (auto& spaceShipLaser : spaceship.spaceShipLasers) {
			if (CheckCollisionRecs(alienLaser.getRect(), spaceShipLaser.getRect())) {
				spaceShipLaser.ChangeColor(WHITE);
				alienLaser.ChangeColor(WHITE);
				spaceShipLaser.SetLaserState(ObjectState::EXPLODING);
				alienLaser.SetLaserState(ObjectState::EXPLODING);
				PlaySound(playerExplosion);

			}
		}
	}

	//Deathball with aliens
	for (auto& alien : aliens) {
		for (auto& point : spaceship.deathBall.GetBallPoints()) {
			if (CheckCollisionPointRec(point, alien.getRect()) && alien.GetState() == ObjectState::ACTIVE) {
				alien.SetState(ObjectState::EXPLODING);
				GetAlienScore(alien);
				IncreaseAliensMovementSpeed();
				//PlaySound(alienExplodeSound);
			}
		}

	}

	//Deathball with mysteryship
	for (auto& point : spaceship.deathBall.GetBallPoints()) {
		if (CheckCollisionPointRec(point, mysteryShip.getRect())) {
			mysteryShip.SetState(ObjectState::EXPLODING);
			GetMysteryShipScore(mysteryShip);
			//PlaySound(alienExplodeSound);
		}
	}

	//Alien lasers with spaceship
	for (auto& alienLaser : alienLasers) {
		if (CheckCollisionRecs(alienLaser.getRect(), spaceship.getRect())) {
			spaceship.SetState(ObjectState::INACTIVE);
			alienLaser.SetLaserState(ObjectState::INACTIVE);
			PlaySound(playerExplosion);
		}
	}

	//spaceship with aliens
	for (auto& alien : aliens) {
		if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
			spaceship.SetState(ObjectState::INACTIVE);
			PlaySound(playerExplosion);
			GameOver();

		}
	}

	//aliens with lower screen edge
	for (auto& alien : aliens) {
		if (alien.getRect().y >= ((float)GetScreenWidth() - 50)) {
			PlaySound(playerExplosion);
			GameOver();
		}
	}

	//Sniper aim with aliens
	if (spaceship.GetPowerUp() == PowerUps::SNIPER && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && NumOfSniperAliens > 0) {
		for (auto& alien : aliens) {
			if (CheckCollisionRecs({ GetMousePosition().x, GetMousePosition().y, (float)sniperImage.width,(float)sniperImage.height }, alien.getRect())) {
				PlaySound(sniperSound);
				alien.SetState(ObjectState::EXPLODING);
				GetAlienScore(alien);
				IncreaseAliensMovementSpeed();

			}
		}
		NumOfSniperAliens--;
		if (NumOfSniperAliens == 0) {
			NumOfSniperAliens = 12;
			spaceship.SetPowerUp(PowerUps::NONE);
		}
	}

	//Sniper aim with mystery spaceship
	if (spaceship.GetPowerUp() == PowerUps::SNIPER && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && NumOfSniperAliens > 0) {
		for (auto& alien : aliens) {
			if (CheckCollisionRecs({ GetMousePosition().x, GetMousePosition().y, (float)sniperImage.width,(float)sniperImage.height }, mysteryShip.getRect())) {
				mysteryShip.SetState(ObjectState::EXPLODING);
				GetMysteryShipScore(mysteryShip);
				PlaySound(sniperSound);
			}
		}
		NumOfSniperAliens--;
		if (NumOfSniperAliens == 0) {
			NumOfSniperAliens = 12;
			spaceship.SetPowerUp(PowerUps::NONE);
		}
	}
}

void Game::HandleObstacleCollisions(Obstacle& obstacle, Block& block)
{
	bool toDestroy = true;
	int radius = 8;
	int radiusAddition = radius + 4;

	//Destryoing block inside radius range
	for (Block& craterBlock : obstacle.blocks) {
		float dist = (float)sqrt(pow(craterBlock.getRect().x - block.getRect().x, 2) +
			pow(craterBlock.getRect().y - block.getRect().y, 2));
		if (dist <= radius) {
			craterBlock.blockState = INACTIVE;
		}
	}

	//Destroying block outside radius range
	for (Block& outsideBlock : obstacle.blocks) {
		toDestroy = !toDestroy;
		float dist = (float)sqrt(pow(outsideBlock.getRect().x - block.getRect().x, 2) +
			pow(outsideBlock.getRect().y - block.getRect().y, 2));
		if (toDestroy && dist <= radiusAddition) {
			outsideBlock.blockState = INACTIVE;
		}
	}
}




std::vector<Obstacle> Game::CreateObstacles()
{
	//Calculating obstacle width
	int obstacleWidth = (int)Obstacle::grid[0].size() * 3;

	//Calculating the gap between 4 obstacles
	float gap = (float)(GetScreenWidth() - (4 * obstacleWidth)) / 5;

	//Creating 4 obstacles
	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX,(float)(GetScreenHeight() - 130) }));
	}

	return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
	std::vector<Alien> aliens;

	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 11; column++) {
			int alienType;
			float x;
			if (row == 0) {
				alienType = 1;
			}
			else if (row == 1 || row == 2) {
				alienType = 2;
			}
			else {
				alienType = 3;
			}
			if (alienType == 1) {
				x = float(GetScreenWidth() / 11 + column * 38) + 3;
			}
			else {
				x = float(GetScreenWidth() / 11 + column * 38);
			}
			float y = 100 + (float)row * 38;
			aliens.push_back(Alien(alienType, { x,y }));
		}
	}

	return aliens;
}

void Game::AlienShootLasers()
{
	double currentTime = GetTime();
	if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, (int)aliens.size() - 1);
		int randomShotSprite = GetRandomValue(1, 2);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(AlienLaser({ alien.position.x + alien.currentSpriteRec.width / 2 ,alien.position.y + alien.currentSpriteRec.height }, ACTIVE, WHITE, randomShotSprite));
		timeLastAlienFired = (float)GetTime();
	}

}

void Game::DeleteInactiveLasers()
{
	for (auto it = alienLasers.begin(); it != alienLasers.end();) {
		if (it->GetActivity() == INACTIVE) {
			it = alienLasers.erase(it);
		}
		else {
			it++;
		}
	}

	for (auto it = spaceship.spaceShipLasers.begin(); it != spaceship.spaceShipLasers.end(); ) {
		if (it->GetActivity() == INACTIVE) {
			it = spaceship.spaceShipLasers.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::DeleteDeadAliens()
{
	for (auto it = aliens.begin(); it != aliens.end();) {
		if (it->alienState == ObjectState::INACTIVE) {
			aliens.erase(it);
			break;
		}
		else {
			it++;
		}
	}
}

void Game::RaiseDifficulty()
{
	if (alienLaserShootInterval >= 0.45f) {
		alienLaserShootInterval -= 0.2f;
	}
	numberOfDownPixels += 2;
	if (numberOfDownPixels < 110) {
		MoveDownAliens(numberOfDownPixels);
	}

}

void Game::DeleteInactiveBlock()
{
	for (auto& obstacle : obstacles) {
		for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();) {
			if (it->blockState == ObjectState::INACTIVE) {
				it = obstacle.blocks.erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void Game::DecreasePowerUpTime()
{
	if (spaceship.GetPowerUp() == PowerUps::MACHINE_GUN) {
		machineGunPowerUpCurrentTime += GetFrameTime();
		if (machineGunPowerUpCurrentTime >= machineGunPowerUpTotalTime) {
			machineGunPowerUpCurrentTime = 0.0f;
			spaceship.SetPowerUp(PowerUps::NONE);
		}
	}
}

void Game::EnablePowerUps()
{
	if (spaceship.GetPowerUp() == PowerUps::MACHINE_GUN) {
		float currentTime = (float)GetTime();
		if (currentTime - timePlayerLastFired >= 0.25f) {
			timePlayerLastFired = (float)GetTime();
			spaceship.FireLaser();

		}
	}
}

void Game::CheckIfLost()
{
	if (IsGameRunning && spaceship.spaceShipState == ObjectState::INACTIVE) {
		inactiveTime += GetFrameTime();
		StopUpdating = true;
		if (lives > 0 && inactiveTime > 1.5f) {
			lives--;
			alienLasers.clear();
			inactiveTime = 0.0f;
			if (lives > 0) {
				StopUpdating = false;
				spaceship.SetState(ObjectState::ACTIVE);
				spaceship.SetPowerUp(PowerUps::NONE);
				spaceship.deathBall.removeBall();
			}
			else {
				GameOver();
			}
		}
	}
}

void Game::GameOver()
{
	IsGameRunning = false;
	StopUpdating = false;
	//highScore = (score > highScore) ? score : highScore;
	movementSpeed = 0.03f;
	alienLaserShootInterval = 1;
	NumOfMachineGunBonus = 0;
	NumOfDeathBallBonus = 0;
	NumOfSniperBonus = 0;
}

void Game::Reset()
{
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
	spaceship.SetPowerUp(PowerUps::NONE);
	lives = 3;
	movementSpeed = 0.03f;
}

void Game::InitGame()
{
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensSpeed = movementSpeed;
	timeLastAlienFired = 0.0f;
	timeLastSpawn = 0.0f;
	mysteryShipSpawnInterval = (float)GetRandomValue(10, 20);
	timePlayerLastFired = 0.0f;
	inactiveTime = 0.0f;
	IsGameRunning = true;
	StopUpdating = false;
	numOfMysteriousShipScoreTime = 1;
	score = 0;
	mysteryShipScore = 0;
	mysteryShipExplosion.x = -1;
	mysteryShipExplosion.y = -1;
	NumOfSniperAliens = 12;
	cheatActivated = false;
	cheatActivatedTime = 3.0f;
	numberOfDownPixels = 0;
}

bool Game::CheckIfWin()
{

	return aliens.size() == 0;
}

void Game::GetAlienScore(Alien& alien)
{
	switch (alien.GetType()) {
	case 1:
		score += 30;
		break;
	case 2:
		score += 20;
		break;
	case 3:
		score += 10;
		break;
	default:
		score += 10;
		break;

	}
}

void Game::GetMysteryShipScore(MysteryShip& mysteryShip)
{
	int scoreTemp = GetRandomValue(100, 200);
	mysteryShipExplosion.x = mysteryShip.getRect().x;
	mysteryShipExplosion.y = mysteryShip.getRect().y;
	mysteryShipScore = scoreTemp;
	score += scoreTemp;
}

void Game::StartNextLevel()
{
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
	spaceship.SetPowerUp(PowerUps::NONE);
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	lives++;
	NumOfSniperAliens = 12;
	RaiseDifficulty();
	movementSpeed = 0.03f;
	int randNum = GetRandomValue(1, 3);
	if (randNum == 1) {
		NumOfDeathBallBonus++;
	}
	else if (randNum == 2) {
		NumOfSniperBonus++;
	}
	else if (randNum == 3) {
		NumOfMachineGunBonus++;
	}
}

void Game::DrawUserInterface()
{
	//---User interface---//

	//Lower screen border
	DrawLine(0, GetScreenWidth() - 20, GetScreenWidth(), GetScreenWidth() - 20, LIME);

	//lives indicator
	DrawTextureV(spaceship.spaceshipImage, { 10, (float)GetScreenHeight() - 25 }, WHITE);
	std::string livesString = "X" + std::to_string(lives);
	DrawTextEx(font, livesString.c_str(), { 40, (float)GetScreenHeight() - 25 }, 20, 3, WHITE);

	//machine gun bonus indicator
	DrawTextureV(machineGunIcon, { 90, (float)GetScreenHeight() - 24 }, WHITE);
	std::string mgString = "X" + std::to_string(NumOfMachineGunBonus);
	DrawTextEx(font, mgString.c_str(), { 120, (float)GetScreenHeight() - 25 }, 20, 3, WHITE);

	//sniper indicator
	DrawTextureV(sniperIcon, { 160, (float)GetScreenHeight() - 24 }, WHITE);
	std::string sniperString = "X" + std::to_string(NumOfSniperBonus);
	DrawTextEx(font, sniperString.c_str(), { 190, (float)GetScreenHeight() - 25 }, 20, 3, WHITE);

	//Deathball indicator
	DrawCircleGradient(240, (float)GetScreenHeight() - 15, 10, WHITE, GREEN);
	std::string ballString = "X" + std::to_string(NumOfDeathBallBonus);
	DrawTextEx(font, ballString.c_str(), { 260, (float)GetScreenHeight() - 25 }, 20, 3, WHITE);

	//Score
	std::string scoreString = "<" + std::to_string(score) + ">";
	DrawTextEx(font, "SCORE", { 0, 5 }, 25, 3, WHITE);
	DrawTextEx(font, scoreString.c_str(), { 0, 30 }, 25, 0, WHITE);

	//High Score
	std::string highScoreString = "<" + std::to_string(highScore) + ">";
	DrawTextEx(font, "HI-SCORE", { (float)GetScreenWidth() - 120 , 5 }, 25, 3, WHITE);
	DrawTextEx(font, highScoreString.c_str(), { (float)GetScreenWidth() - MeasureText(highScoreString.c_str(),25) - 10, 30 }, 25, 0, WHITE);


	//-------------------//
}

void Game::IncreaseAliensMovementSpeed()
{
	if (movementSpeed > 0) {
		movementSpeed += 0.04f;
	}
	else {
		movementSpeed -= 0.04f;
	}
}

void Game::CheckForHighScore()
{
	if (score > highScore) {
		highScore = score;
	}
}

void Game::WinLevel()
{
	cheatActivated = true;
	aliens.clear();
}



bool Game::CheckCheatCode(std::vector<int>& inputSequence, const std::vector<int>& cheatCode) {
	if (inputSequence.size() > cheatCode.size()) {
		inputSequence.clear(); // Reset the sequence if it's longer than the cheat code
		return false;
	}

	for (size_t i = 0; i < inputSequence.size(); ++i) {
		if (inputSequence[i] != cheatCode[i]) {
			inputSequence.clear(); // Reset the sequence if a key is incorrect
			return false;
		}
	}

	// If the input sequence matches the cheat code
	if (inputSequence.size() == cheatCode.size()) {
		inputSequence.clear(); // Clear the sequence after activating the cheat
		return true;
	}

	return false;
}


