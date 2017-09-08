#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

Texture playerTexture;
Sprite playerSprite;
Texture startScreenTexture;
Sprite startScreenSprite;
Texture cursorTexture;
Sprite cursorSprite;
Texture optionsScreenTexture;
Sprite optionsScreenSprite;

RectangleShape startButton;
RectangleShape optionsButton;
RectangleShape quitButton;
RectangleShape res1080Button;
RectangleShape res900Button;
RectangleShape res720Button;
RectangleShape resWindowedButton;
RectangleShape resFullscreenButton;
RectangleShape optionsBackButton;

// The different states of the game
enum class GameStates { START, MENU, OPTIONS, LEVEL_1, LEVEL_2 };

// Method to load in required textures
void Load() {
  
  if (!playerTexture.loadFromFile("res/img/player.png")) {
    throw std::invalid_argument("Loading error!");
  }
	
	if (!startScreenTexture.loadFromFile("res/img/start_screen.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!optionsScreenTexture.loadFromFile("res/img/options.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!cursorTexture.loadFromFile("res/img/cursor.png")) {
		throw std::invalid_argument("Loading error!");
	}
}

// Rescale all sprites when window resolution is changed
void RescaleStart(RenderWindow &window) {
	startScreenSprite.setTexture(startScreenTexture);
	startScreenSprite.setScale(Vector2f(float(window.getSize().x) / float(startScreenTexture.getSize().x), float(window.getSize().y) / float(startScreenTexture.getSize().y)));
	//startScreenSprite.setScale(Vector2f(1280 / 1920.f, 720 / 1080.f));

	cursorSprite.setTexture(cursorTexture);

	startButton.setSize(Vector2f(window.getSize().x * 0.17, window.getSize().y * 0.06));
	startButton.setPosition(window.getSize().x * 0.4, window.getSize().y * 0.55);
	startButton.setFillColor(Color::Blue);

	optionsButton.setSize(Vector2f(window.getSize().x * 0.17, window.getSize().y * 0.06));
	optionsButton.setPosition(window.getSize().x * 0.4, window.getSize().y * 0.61);
	optionsButton.setFillColor(Color::Green);

	quitButton.setSize(Vector2f(window.getSize().x * 0.17, window.getSize().y * 0.06));
	quitButton.setPosition(window.getSize().x * 0.4, window.getSize().y * 0.67);
	quitButton.setFillColor(Color::Red);
}

// Rescales the options menu
void RescaleOptions(RenderWindow &window) {
	optionsScreenSprite.setTexture(optionsScreenTexture);
	optionsScreenSprite.setScale(Vector2f(float(window.getSize().x) / float(startScreenTexture.getSize().x), float(window.getSize().y) / float(startScreenTexture.getSize().y)));

	res1080Button.setSize(Vector2f(window.getSize().x * 0.22, window.getSize().y * 0.13));
	res1080Button.setPosition(window.getSize().x * 0.38, window.getSize().y * 0.08);
	res1080Button.setFillColor(Color::Cyan);

	res900Button.setSize(Vector2f(window.getSize().x * 0.22, window.getSize().y * 0.13));
	res900Button.setPosition(window.getSize().x * 0.38, window.getSize().y * 0.21);
	res900Button.setFillColor(Color::Yellow);

	res720Button.setSize(Vector2f(window.getSize().x * 0.22, window.getSize().y * 0.13));
	res720Button.setPosition(window.getSize().x * 0.38, window.getSize().y * 0.34);
	res720Button.setFillColor(Color::Red);

	resWindowedButton.setSize(Vector2f(window.getSize().x * 0.22, window.getSize().y * 0.13));
	resWindowedButton.setPosition(window.getSize().x * 0.38, window.getSize().y * 0.47);
	resWindowedButton.setFillColor(Color::Blue);

	resFullscreenButton.setSize(Vector2f(window.getSize().x * 0.22, window.getSize().y * 0.13));
	resFullscreenButton.setPosition(window.getSize().x * 0.38, window.getSize().y * 0.60);
	resFullscreenButton.setFillColor(Color::Green);

	optionsBackButton.setSize(Vector2f(window.getSize().x * 0.13, window.getSize().y * 0.12));
	optionsBackButton.setPosition(window.getSize().x * 0.42, window.getSize().y * 0.81);
	optionsBackButton.setFillColor(Color::Magenta);
}

Vector2f CurrentPlayerPosition(RenderWindow &window) {
	Vector2f playerPosRatio = Vector2f(float(playerSprite.getPosition().x) / window.getSize().x, float(playerSprite.getPosition().y) / window.getSize().y);
	std::cout << "\n Ratio x: " << playerPosRatio.x << " \t Ratio y: " << playerPosRatio.y << " \t Window res: " << window.getSize().x << " x " << window.getSize().y << "\t x pos: " << playerSprite.getPosition().x << "\t y pos: " << playerSprite.getPosition().y;
	return playerPosRatio;
}

void RepositionPlayer(RenderWindow &window, Vector2f playerPosRatio) {
	playerSprite.setPosition(Vector2f(float(window.getSize().x) * playerPosRatio.x, float(window.getSize().y) * playerPosRatio.y));
	std::cout << "\n x pos = " << playerSprite.getPosition().x << " ---- y pos = " << playerSprite.getPosition().y;
}

void RescaleLevel1(RenderWindow &window) {
	// Set sprite textures and positons **NEEDS UPDATING**
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin((playerTexture.getSize().x / 2), (playerTexture.getSize().y / 2));
	playerSprite.setScale(Vector2f(float(window.getSize().x) / 3840.f, float(window.getSize().y) / 2160.f));
	
} 

// Method to use time to continuously update the game
void Update(Vector2f &mousePos, RenderWindow &window) {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  Vector2f move;
	Vector2f rotate;
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

	Vector2f playerPos = playerSprite.getPosition();
	float ang = atan2((playerPos.y - mousePos.y), (playerPos.x - mousePos.x)) * (180 / M_PI);
	playerSprite.setRotation(ang+180);
  playerSprite.move(move * float(window.getSize().x) * 300.f / 1920.f * dt);

	cursorSprite.setPosition(mousePos.x - cursorSprite.getGlobalBounds().width / 2, mousePos.y - cursorSprite.getGlobalBounds().height / 2);
}

// Methods to render desired game states
void RenderLevel(RenderWindow &window) { window.draw(playerSprite), window.draw(cursorSprite); }
void RenderStart(RenderWindow &window) { window.draw(startScreenSprite), window.draw(cursorSprite)/*, window.draw(startButton), window.draw(optionsButton), window.draw(quitButton)*/; }
void RenderOptions(RenderWindow &window) { window.draw(optionsScreenSprite), window.draw(cursorSprite)/*, window.draw(res1080Button), window.draw(res900Button), window.draw(res720Button), window.draw(resWindowedButton), window.draw(resFullscreenButton), window.draw(optionsBackButton)*/; }

int main() {
  
	// Initial game state
  GameStates gameState = GameStates::START;
	// Last game state (used for "back" buttons)
	GameStates lastGameState = GameStates::START;
  
	// Initial window
  RenderWindow window(VideoMode(1280, 720), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
	
	// Try to run load method
  try {
    Load();
  } catch (const std::exception &) {
    std::cerr << "Load error" << std::endl;
    return 1;
  }

	// Game running while loop
  while (window.isOpen()) {
		window.setMouseCursorVisible(false);

		int mouseX = Mouse::getPosition(window).x;
		int mouseY = Mouse::getPosition(window).y;
		Vector2f playerPosRatio;


		// Game state switches with each state's running methods within
		switch (gameState) {
			case GameStates::START:
				window.clear();
				RescaleStart(window);
				Update(Vector2f(mouseX,mouseY), window);
				RenderStart(window);
				window.display();

				Event startEvent;
				while (window.pollEvent(startEvent)) {
					if (startEvent.type == Event::Closed) {
						window.close();
					}
					else if (startEvent.type == Event::MouseButtonPressed) {
						// If start button is clicked, go to LEVEL_1 game state
						if (startButton.getGlobalBounds().contains(mouseX, mouseY)) {
							gameState = GameStates::LEVEL_1;
							lastGameState = gameState;
						}
						// If options button is clicked, go to OPTIONS game state
						else if (optionsButton.getGlobalBounds().contains(mouseX, mouseY)) {
							gameState = GameStates::OPTIONS;
						}
						// If quit button is clicked, exit the game
						else if (quitButton.getGlobalBounds().contains(mouseX, mouseY)) {
							window.close();
						}
					}
					else if (startEvent.type == Event::KeyPressed) {
						if (startEvent.key.code == Keyboard::P) {
							window.create(sf::VideoMode(640, 480, 32), "640 x 480 Screen");
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
				RescaleOptions(window);
				Update(Vector2f(mouseX, mouseY), window);
				cursorSprite.setPosition(mouseX - cursorSprite.getGlobalBounds().width / 2, mouseY - cursorSprite.getGlobalBounds().height / 2);
				RenderOptions(window);
				window.display();

				playerPosRatio = CurrentPlayerPosition(window);

				Event optionsEvent;
				while (window.pollEvent(optionsEvent)) {
					if (optionsEvent.type == Event::Closed) {
						window.close();
					}
					else if (optionsEvent.type == Event::MouseButtonPressed) {
						// Choose resolution and windowed or fullscreen
						if (res1080Button.getGlobalBounds().contains(mouseX, mouseY)) {
							window.create(sf::VideoMode(1920, 1080), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							RepositionPlayer(window, playerPosRatio);

						}
						else if (res900Button.getGlobalBounds().contains(mouseX, mouseY)) {
							window.create(sf::VideoMode(1600, 900), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							RepositionPlayer(window, playerPosRatio);
						}
						else if (res720Button.getGlobalBounds().contains(mouseX, mouseY)) {
							window.create(sf::VideoMode(1280, 720), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							RepositionPlayer(window, playerPosRatio);
						}
						else if (resWindowedButton.getGlobalBounds().contains(mouseX, mouseY)) {
							window.create(sf::VideoMode(window.getSize().x, window.getSize().y), "Hotline Scunthorpe", Style::Titlebar | Style::Close);
							RepositionPlayer(window, playerPosRatio);
						}
						else if (resFullscreenButton.getGlobalBounds().contains(mouseX, mouseY)) {
							window.create(sf::VideoMode(window.getSize().x, window.getSize().y), "Hotline Scunthorpe", Style::Fullscreen);
							RepositionPlayer(window, playerPosRatio);
						}

						else if (optionsBackButton.getGlobalBounds().contains(mouseX, mouseY)) {
							gameState = lastGameState;
						}
					}
				}
				break;

			case GameStates::LEVEL_1:
				window.clear();
				RescaleLevel1(window);
				Update(Vector2f(mouseX, mouseY), window);
				cursorSprite.setPosition(mouseX - cursorSprite.getGlobalBounds().width / 2, mouseY - cursorSprite.getGlobalBounds().height / 2);
				RenderLevel(window);
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
		}


    /*window.clear();
    Update();
    Render(window);
    window.display();*/
  }

  return 0;
}