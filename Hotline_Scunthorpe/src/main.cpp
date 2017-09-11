#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

Texture startScreenTexture;
Sprite startScreenSprite;
Texture cursorTexture;
Sprite cursorSprite;
Texture optionsScreenTexture;
Sprite optionsScreenSprite;
Texture level1BackgroundTexture;
Sprite level1BackgroundSprite;
Texture level2BackgroundTexture;
Sprite level2BackgroundSprite;
Texture playerTexture;
Texture playerRifleTexture;
Sprite playerSprite;
Texture enemyTurretATexture;
Sprite enemyTurretASprite;
Texture rifleTexture;
Sprite rifleSprite;
Texture bulletTexture;
Sprite bulletSprite;

RectangleShape startButton;
RectangleShape optionsButton;
RectangleShape quitButton;
RectangleShape res1080Button;
RectangleShape res900Button;
RectangleShape res720Button;
RectangleShape resWindowedButton;
RectangleShape resFullscreenButton;
RectangleShape optionsBackButton;
RectangleShape rifleLocation;
RectangleShape level1Exit;

RectangleShape test;

bool isShooting = false;

// The different states of the game
enum class GameStates { START, MENU, OPTIONS, LEVEL_1, LEVEL_2 };

// Method to load in required textures
void Load() {
	
	if (!cursorTexture.loadFromFile("res/img/cursor.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!startScreenTexture.loadFromFile("res/img/start_screen.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!optionsScreenTexture.loadFromFile("res/img/options.png")) {
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

	if (!enemyTurretATexture.loadFromFile("res/img/turretA.png")) {
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

}

class Bullet {
public:
	Bullet(Vector2f size) {
		bullet.setSize(size);
	}

	void setTex() {
		Texture bulletTexture;
		if (!bulletTexture.loadFromFile("res/img/bullet.png")) {
			throw std::invalid_argument("Loading error!");
		}
		bullet.setTexture(&bulletTexture);
	}
	void speed(Vector2f speed) {
		bullet.move(speed);
		std::cout << "\t speed x = " << speed.x << "\t speed y = " << speed.y;
	}
	void draw(RenderWindow &window) {
		window.draw(bullet);
	}
	void setPos(Vector2f newPos) {
		bullet.setPosition(newPos);
	}
	void setRot(float ang) {
		bullet.setRotation(ang);
	}
	float getRot() {
		return bullet.getRotation();
	}
private:
	RectangleShape bullet;
};

std::vector<Bullet> bulletList;

// Rescale all sprites when window resolution is changed
void setStart() {
	startScreenSprite.setTexture(startScreenTexture);

	cursorSprite.setTexture(cursorTexture);

	startButton.setSize(Vector2f(326, 65));
	startButton.setPosition(768, 594);
	startButton.setFillColor(Color::Blue);

	optionsButton.setSize(Vector2f(326, 65));
	optionsButton.setPosition(768, 659);
	optionsButton.setFillColor(Color::Green);

	quitButton.setSize(Vector2f(326, 65));
	quitButton.setPosition(768, 724);
	quitButton.setFillColor(Color::Red);
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
	level1BackgroundSprite.setTexture(level1BackgroundTexture);

	// Set player sprite texture and scale
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin((playerTexture.getSize().x / 2), (playerTexture.getSize().y / 2));
	playerSprite.setScale(Vector2f(0.5f, 0.5f));
	playerSprite.setPosition(0, 480);

	enemyTurretASprite.setTexture(enemyTurretATexture);
	enemyTurretASprite.setOrigin((enemyTurretATexture.getSize().x / 2), (enemyTurretATexture.getSize().y / 2));
	enemyTurretASprite.setScale(2.f, 2.f);
	enemyTurretASprite.setPosition(1000, 800);

	rifleSprite.setTexture(rifleTexture);
	rifleSprite.setScale(0.75f, 0.75f);
	rifleSprite.setPosition(-40, 920);

	rifleLocation.setSize(Vector2f(120, 120));
	rifleLocation.setPosition(0, 960);
	rifleLocation.setFillColor(Color::Green);

	//bulletSprite.setTexture(bulletTexture);
	//bulletSprite.setPosition(-256, -256);
	//bulletSprite.setOrigin((bulletTexture.getSize().x / 2), (bulletTexture.getSize().y / 2));

	level1Exit.setSize(Vector2f(10, 240));
	level1Exit.setPosition(1910, 240);
}

void setLevel2() {
	level2BackgroundSprite.setTexture(level2BackgroundTexture);

	playerSprite.setPosition(0, 480);

	enemyTurretASprite.setPosition(500, 400);
}

// Method to use time to continuously update the game
void Update(Vector2f &mousePos, RenderWindow &window) {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  Vector2f move;
	Vector2f playerPos = playerSprite.getPosition();
	Vector2f turretPos = enemyTurretASprite.getPosition();
	if (isShooting == true) {
		Bullet newBullet(Vector2f(132, 9));
		newBullet.setTex();
		newBullet.setPos(playerPos);
		newBullet.setRot(playerSprite.getRotation());
		bulletList.push_back(newBullet);
		isShooting = false;
	}
	for (int i = 0; i < bulletList.size(); i++) {
		bulletList[i].draw(window);
		bulletList[i].speed(Vector2f(2000 * dt * cos(bulletList[i].getRot() * (M_PI / 180)), 2000 * dt * sin(bulletList[i].getRot() * (M_PI / 180))));
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

	if (Mouse::isButtonPressed(Mouse::Left)) {
		//bulletSprite.setPosition(playerPos.x, playerPos.y);
		//bulletSprite.setRotation(playerSprite.getRotation());
		isShooting = true;
	}

	bulletSprite.move(2000 * dt * cos(bulletSprite.getRotation()*(M_PI / 180)), 2000 * dt * sin(bulletSprite.getRotation()*(M_PI / 180)));

	if (rifleLocation.getGlobalBounds().contains(playerPos)) {
		playerSprite.setTexture(playerRifleTexture);
		playerSprite.setOrigin(56, 120);
		rifleSprite.setPosition(-500, -500);
	}

	/*if (playerPos.x >= 1920 && playerPos.y >= 240 && playerPos.y <= 480) {
		setLevel2();
		RenderLevel2(window);
	}*/

	//float ang2 = atan2((turretPos.y - playerPos.y), (turretPos.x - playerPos.x)) * (180 / M_PI);

	enemyTurretASprite.rotate(90.f*dt);

	cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
}

// Methods to render desired game states
void RenderLevel1(RenderWindow &window) { window.draw(level1BackgroundSprite), window.draw(rifleSprite), /*window.draw(bulletSprite),*/ window.draw(playerSprite), window.draw(enemyTurretASprite), window.draw(cursorSprite); }
void RenderLevel2(RenderWindow &window) { window.draw(level2BackgroundSprite), window.draw(playerSprite), window.draw(enemyTurretASprite), window.draw(cursorSprite); }
void RenderStart(RenderWindow &window) { window.draw(startScreenSprite), window.draw(cursorSprite)/*, window.draw(startButton), window.draw(optionsButton), window.draw(quitButton)*/; }
void RenderOptions(RenderWindow &window) { window.draw(optionsScreenSprite), window.draw(cursorSprite)/*, window.draw(res1080Button), window.draw(res900Button), window.draw(res720Button), window.draw(resWindowedButton), window.draw(resFullscreenButton), window.draw(optionsBackButton)*/; }

int main() {
  
	// Initial game state
  GameStates gameState = GameStates::START;
	// Last game state (used for "back" buttons)
	GameStates lastGameState = GameStates::START;
  
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

	/*std::vector<Bullet> bulletList;
	bool isShooting = false;*/

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
				Update(Vector2f(mousePos.x, mousePos.y), window);
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
						// If quit button is clicked, exit the game
						else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							window.close();
						}
					}
					else if (startEvent.type == Event::KeyPressed) {
						if (startEvent.key.code == Keyboard::P) {
							window.create(VideoMode(640, 480), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							window.setView(view);
						}
						else if (startEvent.key.code == Keyboard::Escape) {
							window.close();
						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					gameState = GameStates::LEVEL_1;
				}
				break;
				
			case GameStates::MENU:
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
				}
				break;

			case GameStates::LEVEL_1:
				window.clear();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				playerPos = playerSprite.getPosition();
				/*if (isShooting == true) {
					Bullet newBullet(Vector2f(132, 9), bulletTexture);
					newBullet.setPos(playerPos);
					bulletList.push_back(newBullet);
					isShooting = false;
				}
				for (int i = 0; i < bulletList.size(); i++) {
					bulletList[i].draw(window);
					bulletList[i].speed(1);
				}*/
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
						else if (level1Exit.getGlobalBounds().contains(playerPos)) {
							setLevel2();
							gameState = GameStates::LEVEL_2;
							lastGameState = gameState;
						}
					}
					/*else if (level1Event.type == Event::MouseButtonPressed) {
						isShooting = true;
					}*/
				}
				break;
			case GameStates::LEVEL_2:
				window.clear();
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				Update(Vector2f(mousePos.x, mousePos.y), window);
				RenderLevel2(window);
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
		}
  }

  return 0;
}