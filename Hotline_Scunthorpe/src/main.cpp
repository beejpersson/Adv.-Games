#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <algorithm>

using namespace sf;

// Textures and sprites
Texture startScreenTexture;
Texture startScreen2Texture;
Sprite startScreenSprite;
Texture cursorTexture;
Sprite cursorSprite;
Texture highScoresScreenTexture;
Sprite highScoresSprite;
Texture optionsScreenTexture;
Sprite optionsScreenSprite;
Texture creditsScreenTexture;
Sprite creditsScreenSprite;
Texture level1BackgroundTexture, level2BackgroundTexture, playerTexture, playerRifleTexture, enemyTurretBaseTexture, enemyTurretATexture, enemyTurretBTexture, rifleTexture, bulletTexture;
Sprite level1BackgroundSprite, level2BackgroundSprite, playerSprite, enemyTurretBaseSprite, enemyTurretASprite, enemyTurretBSprite, rifleSprite, bulletSprite;
Texture gameOverTexture;
Sprite gameOverSprite;


// Start screen buttons
RectangleShape startButton, optionsButton, quitButton, highScoresButton, creditsButton;
// Options screen buttons
RectangleShape res1080Button, res900Button, res720Button, resWindowedButton, resFullscreenButton, optionsBackButton;
//Highscores screen text
Text scoreTitle;
// Level 1 rects
RectangleShape rifleLocation, level1Exit;
// level 2 rects
RectangleShape level2Exit;
// Game over score text
Font alienFont;
Text scoreText;

// Sounds
SoundBuffer buzzBuffer, gunCockBuffer, gunShotBuffer, pistolBuffer, rifleBuffer, turretDeathBuffer, playerDeathBuffer, winBuffer;
Sound turretGunSound, gunSounds, turretDeathSound, buzzSound, playerDeathSound, gunCockSound, winSound;

// Start screen timer
int startTimer = 0;
int startRate = 60;

// Update timers for firing rates
int firingTimer = 0;
int enemyFiringTimer = 0;
int playerFiringRate = 10;
int enemyTurretAFiringRate = 15;
int enemyTurretBFiringRate = 30;

// Shooting bools
bool isShooting = false;
bool isEnemyTurretAShooting = false;
bool isEnemyTurretBShooting = false;

// Scoring
std::vector<int> scoreList;
int currentScore;
int printableScore;

// The different states of the game
enum class GameStates { START, OPTIONS, CREDITS, SCORES, LEVEL_1, LEVEL_2, GAME_OVER };

// Initial game state
GameStates gameState = GameStates::START;
// Last game state (used for "back" buttons)
GameStates lastGameState = GameStates::START;

// Method to load in required textures
void Load() {

	if (!cursorTexture.loadFromFile("res/img/cursor.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!startScreenTexture.loadFromFile("res/img/start_screen.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!startScreen2Texture.loadFromFile("res/img/start_screen2.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!highScoresScreenTexture.loadFromFile("res/img/highscores.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!optionsScreenTexture.loadFromFile("res/img/options.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!creditsScreenTexture.loadFromFile("res/img/credits.png")) {
		throw std::invalid_argument("Loading error!");
	}
	
	if (!level1BackgroundTexture.loadFromFile("res/img/level1.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!level2BackgroundTexture.loadFromFile("res/img/level2.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!playerTexture.loadFromFile("res/img/player.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!enemyTurretBaseTexture.loadFromFile("res/img/turretBase.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!enemyTurretATexture.loadFromFile("res/img/turretA.png")) {
		throw std::invalid_argument("Loading error!");
	}
	
	if(!enemyTurretBTexture.loadFromFile("res/img/turretB.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!playerRifleTexture.loadFromFile("res/img/playerRifle.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!rifleTexture.loadFromFile("res/img/rifle.png")) {
		throw std::invalid_argument("Loading error!");
	}
	if (!bulletTexture.loadFromFile("res/img/bullet.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!gameOverTexture.loadFromFile("res/img/gameover.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!alienFont.loadFromFile("res/font/Alien-Encounters-Regular.ttf"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!gunCockBuffer.loadFromFile("res/sound/GunCock.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!gunShotBuffer.loadFromFile("res/sound/GunShot.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!buzzBuffer.loadFromFile("res/sound/buzz.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!pistolBuffer.loadFromFile("res/sound/pistol.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!rifleBuffer.loadFromFile("res/sound/rifle.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!turretDeathBuffer.loadFromFile("res/sound/turretDeath.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!playerDeathBuffer.loadFromFile("res/sound/playerDeath.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}

	if (!winBuffer.loadFromFile("res/sound/win.wav"))
	{
		throw std::invalid_argument("Loading error!");
	}


}

class Bullet {
public:
	Bullet() {};

	Bullet(Vector2f size) {
		bullet.setSize(size);
	}

	void setTex(Texture &bulletTexture) {
		bullet.setTexture(&bulletTexture);
	}
	void speed(Vector2f speed) {
		bullet.move(speed);
	}
	void draw(RenderWindow &window) {
		window.draw(bullet);
	}
	void setPos(float posx, float posy) {
		bullet.setPosition(posx, posy);
	}
	void setRot(float ang) {
		bullet.setRotation(ang);
	}
	float getRot() {
		return bullet.getRotation();
	}
	Vector2f getPos() {
		return bullet.getPosition();
	}

	// Collision check getters
	int getRight() {
		return bullet.getPosition().x + bullet.getSize().x;
	}

	int getLeft() {
		return bullet.getPosition().x;
	}

	int getTop() {
		return bullet.getPosition().y;
	}

	int getBottom() {
		return bullet.getPosition().y + bullet.getSize().y;
	}

	FloatRect getBounds() {
		return bullet.getGlobalBounds();
	}

private:
	RectangleShape bullet;
};

class Enemy {
public:
	Enemy() {};

	Enemy(Vector2f size) {
		enemy.setSize(size);
	}

	void setType(int enemyType) {
		type = enemyType;
	}

	int getType() {
		return type;
	}

	void setTex(Texture &enemyTexture) {
		enemy.setTexture(&enemyTexture);
	}
	void draw(RenderWindow &window) {
		window.draw(enemy);
	}
	void setPos(float posx, float posy) {
		enemy.setPosition(posx, posy);
	}
	void setOrigin(Vector2f origin) {
		enemy.setOrigin(origin);
	}
	void rot(float ang) {
		enemy.rotate(ang);
	}
	void setRot(float ang) {
		enemy.setRotation(ang);
	}
	float getRot() {
		return enemy.getRotation();
	}
	Vector2f getPos() {
		return enemy.getPosition();
	}
	void setTimer() {
		firingTimer = 0;
	}
	void incrementTimer(float rate) {
		firingTimer += rate;
	}
	int getTimer() {
		return firingTimer;
	}
	bool checkCollision(Bullet bullet) {
		if (bullet.getBounds().intersects(enemy.getGlobalBounds())) {
			enemy.setPosition(sf::Vector2f(-500, -500));
			return true;
		}
		return false;
	}

private:
	RectangleShape enemy;
	int firingTimer = 0;
	int type;
};

std::vector<Bullet> playerBulletList;
std::vector<Bullet> enemyBulletList;

std::vector<Enemy> enemyList;

// Set all sprites and buttons in start screen
void setStart() {

	cursorSprite.setTexture(cursorTexture);

	startButton.setSize(Vector2f(420, 120));
	startButton.setPosition(760, 460);
	startButton.setFillColor(Color::Blue);

	optionsButton.setSize(Vector2f(420, 120));
	optionsButton.setPosition(760, 600);
	optionsButton.setFillColor(Color::Green);

	creditsButton.setSize(Vector2f(420, 120));
	creditsButton.setPosition(760, 740);
	creditsButton.setFillColor(Color::Magenta);

	quitButton.setSize(Vector2f(420, 120));
	quitButton.setPosition(760, 880);
	quitButton.setFillColor(Color::Red);


	highScoresButton.setSize(Vector2f(380, 240));
	highScoresButton.setPosition(1380, 680);	
	highScoresButton.setFillColor(Color::Cyan);
}

// Set the highscore screen
void setHighScores() {
	highScoresSprite.setTexture(highScoresScreenTexture);

	optionsBackButton.setSize(Vector2f(250, 140));
	optionsBackButton.setPosition(805, 930);
	optionsBackButton.setFillColor(Color::Magenta);

	scoreTitle.setFont(alienFont);
	scoreTitle.setCharacterSize(48);
	scoreTitle.setColor(Color::Magenta);
	scoreTitle.setPosition(900, 400);
}

void drawScoreList(RenderWindow &window) {


	sort(scoreList.begin(), scoreList.end());
	reverse(scoreList.begin(), scoreList.end());

	for (int i = 0; i < scoreList.size(); i++) {
		Text highScoresText;
		Text positionText;
		highScoresText.setFont(alienFont);
		positionText.setFont(alienFont);
		highScoresText.setCharacterSize(48);
		positionText.setCharacterSize(48);
		highScoresText.setColor(Color::Cyan);
		positionText.setColor(Color::Magenta);
		highScoresText.setString(std::to_string(scoreList[i]));
		positionText.setString(std::to_string(i + 1) + ".");

		if (scoreList.size() > 20) {
			if (i > 19) {
				highScoresText.setPosition(1600, 300 + (60 * (i - 20)));
				positionText.setPosition(1300, 300 + (60 * (i - 20)));
			}
			else if (i > 9) {
				highScoresText.setPosition(1100, 300 + (60 * (i - 10)));
				positionText.setPosition(800, 300 + (60 * (i - 10)));
			}
			else {
				highScoresText.setPosition(600, 300 + (60 * i));
				positionText.setPosition(300, 300 + (60 * i));
			}
		}

		else if (scoreList.size() > 10) {
			if (i > 9) {
				highScoresText.setPosition(1400, 300 + (60 * (i - 10)));
				positionText.setPosition(1100, 300 + (60 * (i - 10)));
			}
			else {
				highScoresText.setPosition(800, 300 + (60 * i));
				positionText.setPosition(500, 300 + (60 * i));
			}
		}
		else {
			highScoresText.setPosition(1100, 300 + (60 * i));
			positionText.setPosition(800, 300 + (60 * i));
		}

		window.draw(highScoresText);
		window.draw(positionText);
	}
}

void setCredits() {
	creditsScreenSprite.setTexture(creditsScreenTexture);

	optionsBackButton.setSize(Vector2f(250, 140));
	optionsBackButton.setPosition(820, 930);
	optionsBackButton.setFillColor(Color::Magenta);
}

// Rescales the options menu
void setOptions() {
	optionsScreenSprite.setTexture(optionsScreenTexture);

	res1080Button.setSize(Vector2f(420, 140));
	res1080Button.setPosition(730, 86);
	res1080Button.setFillColor(Color::Cyan);

	res900Button.setSize(Vector2f(420, 140));
	res900Button.setPosition(730, 226);
	res900Button.setFillColor(Color::Yellow);

	res720Button.setSize(Vector2f(420, 140));
	res720Button.setPosition(730, 366);
	res720Button.setFillColor(Color::Red);

	resWindowedButton.setSize(Vector2f(420, 140));
	resWindowedButton.setPosition(730, 506);
	resWindowedButton.setFillColor(Color::Blue);

	resFullscreenButton.setSize(Vector2f(420, 140));
	resFullscreenButton.setPosition(730, 646);
	resFullscreenButton.setFillColor(Color::Green);

	optionsBackButton.setSize(Vector2f(250, 140));
	optionsBackButton.setPosition(805, 875);
	optionsBackButton.setFillColor(Color::Magenta);
}

void setLevel1() {
	playerFiringRate = 10;
	gunCockSound.setBuffer(gunCockBuffer);
	gunCockSound.setVolume(30);
	gunCockSound.play();
	level1BackgroundSprite.setTexture(level1BackgroundTexture);

	// Set player sprite texture and scale
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin(60, 80);
	playerSprite.setScale(Vector2f(0.5f, 0.5f));
	playerSprite.setPosition(0, 480);

	Enemy enemyA1(Vector2f(186, 78));
	enemyA1.setType(1);
	enemyA1.setTex(enemyTurretATexture);
	enemyA1.setPos(1020, 900);
	enemyA1.setRot(90);
	enemyA1.setOrigin(Vector2f(56, 39));
	enemyList.push_back(enemyA1);

	Enemy enemyA2(Vector2f(186, 78));
	enemyA2.setType(1);
	enemyA2.setTex(enemyTurretATexture);
	enemyA2.setPos(120, 120);
	enemyA2.setRot(180);
	enemyA2.setOrigin(Vector2f(56, 39));
	enemyList.push_back(enemyA2);

	Enemy enemyA3(Vector2f(186, 78));
	enemyA3.setType(1);
	enemyA3.setTex(enemyTurretATexture);
	enemyA3.setPos(1320, 180);
	enemyA3.setRot(270);
	enemyA3.setOrigin(Vector2f(56, 39));
	enemyList.push_back(enemyA3);

	Enemy enemyA4(Vector2f(186, 78));
	enemyA4.setType(1);
	enemyA4.setTex(enemyTurretATexture);
	enemyA4.setPos(1500, 960);
	enemyA4.setRot(0);
	enemyA4.setOrigin(Vector2f(56, 39));
	enemyList.push_back(enemyA4);

	rifleSprite.setTexture(rifleTexture);
	rifleSprite.setScale(0.75f, 0.75f);
	rifleSprite.setPosition(-40, 860);

	rifleLocation.setSize(Vector2f(120, 120));
	rifleLocation.setPosition(0, 880);
	rifleLocation.setFillColor(Color::Green);

	level1Exit.setSize(Vector2f(10, 240));
	level1Exit.setPosition(1910, 240);
}

void setLevel2() {
	gunCockSound.setBuffer(gunCockBuffer);
	gunCockSound.setVolume(30);
	gunCockSound.play();
	level2BackgroundSprite.setTexture(level2BackgroundTexture);

	playerSprite.setPosition(0, 360);

	Enemy enemyA1(Vector2f(186, 78));
	enemyA1.setType(1);
	enemyA1.setTex(enemyTurretATexture);
	enemyA1.setPos(600, 180);
	enemyA1.setRot(90);
	enemyA1.setOrigin(Vector2f(56, 39));
	enemyList.push_back(enemyA1);

	Enemy enemyA2(Vector2f(186, 78));
	enemyA2.setType(1);
	enemyA2.setTex(enemyTurretATexture);
	enemyA2.setPos(1560, 900);
	enemyA2.setRot(180);
	enemyA2.setOrigin(Vector2f(56, 39));
	enemyList.push_back(enemyA2);

	Enemy enemyBase1(Vector2f(192, 192));
	enemyBase1.setType(0);
	enemyBase1.setTex(enemyTurretBaseTexture);
	enemyBase1.setPos(1640, 360);
	enemyBase1.setOrigin(Vector2f(96, 96));
	enemyList.push_back(enemyBase1);

	Enemy enemyBase2(Vector2f(192, 192));
	enemyBase2.setType(0);
	enemyBase2.setTex(enemyTurretBaseTexture);
	enemyBase2.setPos(840, 900);
	enemyBase2.setOrigin(Vector2f(96, 96));
	enemyList.push_back(enemyBase2);

	Enemy enemyB1(Vector2f(256, 256));
	enemyB1.setType(2);
	enemyB1.setTex(enemyTurretBTexture);
	enemyB1.setPos(1640, 360);
	enemyB1.setRot(0);
	enemyB1.setOrigin(Vector2f(128, 128));
	enemyList.push_back(enemyB1);

	Enemy enemyB2(Vector2f(256, 256));
	enemyB2.setType(2);
	enemyB2.setTex(enemyTurretBTexture);
	enemyB2.setPos(840, 900);
	enemyB2.setRot(90);
	enemyB2.setOrigin(Vector2f(128, 128));
	enemyList.push_back(enemyB2);

	level2Exit.setSize(Vector2f(240, 10));
	level2Exit.setPosition(240, 1070);

}

void setGameOver() {
	gameOverSprite.setTexture(gameOverTexture);

	optionsBackButton.setSize(Vector2f(580, 140));
	optionsBackButton.setPosition(660, 630);
	optionsBackButton.setFillColor(Color::Magenta);

	quitButton.setSize(Vector2f(320, 140));
	quitButton.setPosition(795, 780);
	quitButton.setFillColor(Color::Red);

	scoreText.setFont(alienFont);
	scoreText.setString(std::to_string(printableScore));
	scoreText.setPosition(1050, 420);
	scoreText.setCharacterSize(108);
	scoreText.setColor(Color::Cyan);
}

void UpdateStart(Vector2f &mousePos, RenderWindow &window) {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	window.setFramerateLimit(60);
	startTimer += (60 * dt);

	if (startTimer > startRate) {
		buzzSound.setBuffer(buzzBuffer);
		buzzSound.setVolume(10);
		buzzSound.play();
		startScreenSprite.setTexture(startScreen2Texture);
		window.draw(startScreenSprite);
		if (startTimer > startRate+5) {
			buzzSound.stop();
			startScreenSprite.setTexture(startScreenTexture);
			window.draw(startScreenSprite);
			startTimer = 0;
		}
	}

	cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
}

// Method to use time to continuously update the game levels
void Update(Vector2f &mousePos, RenderWindow &window) {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
	window.setFramerateLimit(60);
  Vector2f move;
	Vector2f playerPos = playerSprite.getPosition();
	Vector2f turretPos = enemyTurretASprite.getPosition();

	firingTimer += (60 * dt);

	if (isShooting == true) {
		if (playerFiringRate == 5) {
			gunSounds.setBuffer(rifleBuffer);
			gunSounds.setVolume(10);
			gunSounds.play();
		}
		else if (playerFiringRate == 10) {
			gunSounds.setBuffer(pistolBuffer);
			gunSounds.setVolume(10);
			gunSounds.play();
		}
		Bullet newBullet(Vector2f(132, 9));
		newBullet.setTex(bulletTexture);
		newBullet.setPos(playerPos.x, playerPos.y);
		newBullet.setRot(playerSprite.getRotation());
		playerBulletList.push_back(newBullet);
		isShooting = false;
	}

	for (int i = 0; i < enemyList.size(); i++) {
		if (enemyList[i].getType() != 0) {
			enemyList[i].rot(90.f * dt);
		}
		enemyList[i].draw(window);
		enemyList[i].incrementTimer(60 * dt);
		for (int j = 0; j < playerBulletList.size(); j++) {
			if (enemyList[i].checkCollision(playerBulletList[j])) {
				currentScore++;
				turretDeathSound.setBuffer(turretDeathBuffer);
				turretDeathSound.setVolume(10);
				turretDeathSound.play();
			}
		}
		if (enemyList[i].getTimer() > enemyTurretAFiringRate && enemyList[i].getType() == 1 && enemyList[i].getPos().x > 0) {
			isEnemyTurretAShooting = true;
			enemyList[i].setTimer();
		}
		else if (enemyList[i].getTimer() > enemyTurretBFiringRate && enemyList[i].getType() == 2 && enemyList[i].getPos().x > 0) {
			isEnemyTurretBShooting = true;
			enemyList[i].setTimer();
		}

		if (isEnemyTurretAShooting == true) {
			turretGunSound.setBuffer(gunShotBuffer);
			turretGunSound.setVolume(10);
			turretGunSound.play();
			Bullet newBullet(Vector2f(132, 9));
			newBullet.setTex(bulletTexture);
			newBullet.setPos(enemyList[i].getPos().x, enemyList[i].getPos().y);
			newBullet.setRot(enemyList[i].getRot());
			enemyBulletList.push_back(newBullet);
			isEnemyTurretAShooting = false;
		}

		if (isEnemyTurretBShooting == true) {
			turretGunSound.setBuffer(gunShotBuffer);
			turretGunSound.setVolume(10);
			turretGunSound.play();
			Bullet firstBullet(Vector2f(132, 9));
			firstBullet.setTex(bulletTexture);
			firstBullet.setPos(enemyList[i].getPos().x, enemyList[i].getPos().y);
			firstBullet.setRot(enemyList[i].getRot());
			enemyBulletList.push_back(firstBullet);

			Bullet secondBullet(Vector2f(132, 9));
			secondBullet.setTex(bulletTexture);
			secondBullet.setPos(enemyList[i].getPos().x, enemyList[i].getPos().y);
			secondBullet.setRot(enemyList[i].getRot() + 90.f);
			enemyBulletList.push_back(secondBullet);


			Bullet thirdBullet(Vector2f(132, 9));
			thirdBullet.setTex(bulletTexture);
			thirdBullet.setPos(enemyList[i].getPos().x, enemyList[i].getPos().y);
			thirdBullet.setRot(enemyList[i].getRot() + 180.f);
			enemyBulletList.push_back(thirdBullet);

			Bullet fourthBullet(Vector2f(132, 9));
			fourthBullet.setTex(bulletTexture);
			fourthBullet.setPos(enemyList[i].getPos().x, enemyList[i].getPos().y);
			fourthBullet.setRot(enemyList[i].getRot() + 270.f);
			enemyBulletList.push_back(fourthBullet);

			isEnemyTurretBShooting = false;
		}

	}

	for (int i = 0; i < playerBulletList.size(); i++) {
		playerBulletList[i].speed(Vector2f(1000 * dt * cos(playerBulletList[i].getRot() * (M_PI / 180)), 1000 * dt * sin(playerBulletList[i].getRot() * (M_PI / 180))));
		if (playerBulletList[i].getPos().x > 0 && playerBulletList[i].getPos().x < 1920 && playerBulletList[i].getPos().y > 0 && playerBulletList[i].getPos().y < 1080) {
			playerBulletList[i].draw(window);
		}
	}

	for (int i = 0; i < 	enemyBulletList.size(); i++) {
		enemyBulletList[i].speed(Vector2f(1000 * dt * cos(enemyBulletList[i].getRot() * (M_PI / 180)), 1000 * dt * sin(enemyBulletList[i].getRot() * (M_PI / 180))));
		if (enemyBulletList[i].getPos().x > 0 && enemyBulletList[i].getPos().x < 1920 && enemyBulletList[i].getPos().y > 0 && enemyBulletList[i].getPos().y < 1080) {
			enemyBulletList[i].draw(window);
		}
		if (enemyBulletList[i].getBounds().intersects(playerSprite.getGlobalBounds())) {
			playerDeathSound.setBuffer(playerDeathBuffer);
			playerDeathSound.setVolume(30);
			playerDeathSound.play();
			enemyList.clear();
			scoreList.push_back(currentScore);
			printableScore = currentScore;
			currentScore = 0;
			gameState = GameStates::GAME_OVER;
		}
	}

  if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
    move.x--;
  }
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
		move.x++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
		move.y--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
		move.y++;
	}

	float ang = atan2((playerPos.y - mousePos.y), (playerPos.x - mousePos.x)) * (180 / M_PI);
	playerSprite.setRotation(ang+180);
  playerSprite.move(move*300.f*dt);

	if (Mouse::isButtonPressed(Mouse::Left) && firingTimer > playerFiringRate) {
		firingTimer = 0;
		isShooting = true;
	}

	if (rifleLocation.getGlobalBounds().contains(playerPos)) {
		playerSprite.setTexture(playerRifleTexture);
		playerSprite.setOrigin(56, 82);
		rifleSprite.setPosition(-500, -500);
		playerFiringRate = 5;
	}

  if (level1Exit.getGlobalBounds().contains(playerPos) && gameState == GameStates::LEVEL_1) {
		enemyList.clear();
		playerBulletList.clear();
		enemyBulletList.clear();
		setLevel2();
		gameState = GameStates::LEVEL_2;
		lastGameState = gameState;
	}

	if (level2Exit.getGlobalBounds().contains(playerPos) && gameState == GameStates::LEVEL_2) {
		winSound.setBuffer(winBuffer);
		winSound.setVolume(30);
		winSound.play();
		enemyList.clear();
		playerBulletList.clear();
		enemyBulletList.clear();
		scoreList.push_back(currentScore);
		printableScore = currentScore;
		currentScore = 0;
		gameState = GameStates::START;
	}

	cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
}

// Methods to render desired game states
void RenderLevel1(RenderWindow &window) { window.draw(level1BackgroundSprite), window.draw(rifleSprite), window.draw(playerSprite), window.draw(cursorSprite); }
void RenderLevel2(RenderWindow &window) { window.draw(level2BackgroundSprite), window.draw(playerSprite), window.draw(cursorSprite); }
void RenderStart(RenderWindow &window) { window.draw(startScreenSprite), window.draw(cursorSprite); }
void RenderOptions(RenderWindow &window) { window.draw(optionsScreenSprite), window.draw(cursorSprite); }
void RenderGameOver(RenderWindow &window) { window.draw(gameOverSprite), window.draw(cursorSprite), window.draw(scoreText); }
void RenderScores(RenderWindow &window) { window.draw(highScoresSprite), window.draw(cursorSprite); }
void RenderCredits(RenderWindow &window) { window.draw(creditsScreenSprite), window.draw(cursorSprite); }

int main() {
  
	// Initial window
  RenderWindow window(VideoMode(1920, 1080), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
	View view(FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	
	// Try to run load method
  try {
    Load();
  } catch (const std::exception &) {
    std::cerr << "Load error" << std::endl;
    return 1;
  }

	startScreenSprite.setTexture(startScreenTexture);

	// Game running while loop
  while (window.isOpen()) {
		window.setMouseCursorVisible(false);
		Vector2f playerPos;
		Vector2f mousePos;


		// Game state switches with each state's running methods within
		switch (gameState) {
			case GameStates::START:
				window.clear();
				setStart();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				UpdateStart(Vector2f(mousePos.x, mousePos.y), window);
				RenderStart(window);
				window.display();

				Event startEvent;
				while (window.pollEvent(startEvent)) {
					if (startEvent.type == Event::Closed) {
						window.close();
					}
					else if (startEvent.type == Event::MouseButtonPressed) {
						// If start button is clicked, go to LEVEL_1 game state
						if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							setLevel1();
							gameState = GameStates::LEVEL_1;
							lastGameState = gameState;
						}
						// If options button is clicked, go to OPTIONS game state
						else if (optionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = GameStates::OPTIONS;
						}
						// If credits button is clicked, show credits
						else if (creditsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = GameStates::CREDITS;
						}
						// If highscore button is clicked, show high scores
						else if (highScoresButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = GameStates::SCORES;
						}
						// If quit button is clicked, exit the game
						else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.close();
						}
					}
					else if (startEvent.type == Event::KeyPressed) {
						if (startEvent.key.code == Keyboard::Escape) {
							window.close();
						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					gameState = GameStates::LEVEL_1;
				}
				break;
				
			case GameStates::SCORES:
				window.clear();
				setHighScores();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
				RenderScores(window);
				drawScoreList(window);
				window.display();
				Event scoresEvent;
				while (window.pollEvent(scoresEvent)) {
					if (scoresEvent.type == Event::Closed) {
						window.close();
					}
					else if (scoresEvent.type == Event::MouseButtonPressed) {
						// Choose resolution and windowed or fullscreen
						if (optionsBackButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = GameStates::START;
							lastGameState = gameState;
						}
					}
				}
				break;
			case GameStates::CREDITS:
				window.clear();
				setCredits();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
				RenderCredits(window);
				window.display();
				Event creditsEvent;
				while (window.pollEvent(creditsEvent)) {
					if (creditsEvent.type == Event::Closed) {
						window.close();
					}
					else if (creditsEvent.type == Event::MouseButtonPressed) {
						// Choose resolution and windowed or fullscreen
						if (optionsBackButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = GameStates::START;
							lastGameState = gameState;
						}
					}
				}
				break;

			case GameStates::OPTIONS:
				window.clear();
				setOptions();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
				RenderOptions(window);
				window.display();

				Event optionsEvent;
				while (window.pollEvent(optionsEvent)) {
					if (optionsEvent.type == Event::Closed) {
						window.close();
					}
					else if (optionsEvent.type == Event::MouseButtonPressed) {
						// Choose resolution and windowed or fullscreen
						if (res1080Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.create(sf::VideoMode(1920, 1080), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							window.setView(view);
						}
						else if (res900Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.create(sf::VideoMode(1600, 900), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							window.setView(view);
						}
						else if (res720Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.create(sf::VideoMode(1280, 720), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							window.setView(view);
						}
						else if (resWindowedButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.create(sf::VideoMode(window.getSize().x, window.getSize().y), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							window.setView(view);
						}
						else if (resFullscreenButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.create(sf::VideoMode(window.getSize().x, window.getSize().y), "Hotline Scunthorpe", Style::Fullscreen);
							window.setView(view);
						}

						else if (optionsBackButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = lastGameState;
						}
					}
					else if (optionsEvent.type == Event::KeyPressed) {
						if (optionsEvent.key.code == Keyboard::Escape) {
							gameState = lastGameState;
						}
					}
				}
				break;

			case GameStates::LEVEL_1:
				window.clear();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				RenderLevel1(window);
				Update(Vector2f(mousePos.x, mousePos.y), window);
				window.display();
				Event level1Event;
				while (window.pollEvent(level1Event)) {
					if (level1Event.type == Event::Closed) {
						window.close();
					}
					else if (level1Event.type == Event::KeyPressed) {
						if (level1Event.key.code == Keyboard::Escape) {
							gameState = GameStates::OPTIONS;
						}
					}
				}
				break;
			case GameStates::LEVEL_2:
				window.clear();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				RenderLevel2(window);
				Update(Vector2f(mousePos.x, mousePos.y), window);
				window.display();
				Event level2Event;
				while (window.pollEvent(level2Event)) {
					if (level2Event.type == Event::Closed) {
						window.close();
					}
					else if (level2Event.type == Event::KeyPressed) {
						if (level2Event.key.code == Keyboard::Escape) {
							gameState = GameStates::OPTIONS;
						}
					}
				}
				break;
			case GameStates::GAME_OVER:
				window.clear();
				setGameOver();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
				RenderGameOver(window);
				window.display();

				Event gameOverEvent;
				while (window.pollEvent(gameOverEvent)) {
					if (gameOverEvent.type == Event::Closed) {
						window.close();
					}
					else if (gameOverEvent.type == Event::MouseButtonPressed) {
						// Choose resolution and windowed or fullscreen
						if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.close();
						}
						else if (optionsBackButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							gameState = GameStates::START;
							lastGameState = gameState;
						}
					}
				}
				break;
		}
  }

  return 0;
}