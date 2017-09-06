#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

using namespace sf;

Texture playerTexture;
Sprite playerSprite;
Texture startScreenTexture;
Sprite startScreenSprite;
Texture cursorTexture;
Sprite cursorSprite;

RectangleShape startButton;

// The different states of the game
enum class GameStates { START, MENU, OPTIONS, LEVEL_1, LEVEL_2 };

// Method to load in required textures
void Load() {
  
  if (!playerTexture.loadFromFile("res/img/spaceship1.png")) {
    throw std::invalid_argument("Loading error!");
  }
	
	if (!startScreenTexture.loadFromFile("res/img/start_screen.png")) {
		throw std::invalid_argument("Loading error!");
	}

	if (!cursorTexture.loadFromFile("res/img/cursor.png")) {
		throw std::invalid_argument("Loading error!");
	}

  // Setting ship's initial position
  //sprite.setPosition(100, 200);

}

// Rescale all sprites when window resolution is changed
void Rescale(RenderWindow &window) {
	startScreenSprite.setTexture(startScreenTexture);

	startScreenSprite.setScale(Vector2f(float(window.getSize().x) / float(startScreenTexture.getSize().x), float(window.getSize().y) / float(startScreenTexture.getSize().y)));
	//startScreenSprite.setScale(Vector2f(1280 / 1920.f, 720 / 1080.f));

	cursorSprite.setTexture(cursorTexture);

	startButton.setSize(Vector2f(window.getSize().x * 0.17, window.getSize().y * 0.06));
	startButton.setPosition(window.getSize().x * 0.4, window.getSize().y * 0.55);
	startButton.setFillColor(Color::Blue);
}

// Method to use time to continuously update the game
void Update() {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  Vector2f move;
  if (Keyboard::isKeyPressed(Keyboard::Left)) {
    move.x--;
  }
  if (Keyboard::isKeyPressed(Keyboard::Right)) {
    move.x++;
  }
  playerSprite.move(move*300.0f*dt);
}

// Methods to render desired game states
void RenderLevel(RenderWindow &window) { window.draw(playerSprite); }
void RenderStart(RenderWindow &window) { window.draw(startScreenSprite); }

int main() {
  
	// Initial game state
  GameStates gameState = GameStates::START;
  
	// Initial window
  RenderWindow window(VideoMode(1280, 720), "SFML works!"/*, Style::Resize, Style::Fullscreen*/);
	window.setMouseCursorVisible(false);
	
	// Try to run load method
  try {
    Load();
  } catch (const std::exception &) {
    std::cerr << "Load error" << std::endl;
    return 1;
  }

	// Set sprite textures and positons **NEEDS UPDATING**
  playerSprite.setTexture(playerTexture);
  playerSprite.setScale(Vector2f(2.f, 2.f));

	

	// Game running while loop
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

		int mouseX = Mouse::getPosition(window).x;
		int mouseY = Mouse::getPosition(window).y;

		// Game state switches with each state's running methods within
		switch (gameState) {
			case GameStates::START:
				window.clear();
				Rescale(window);
				Update();
				RenderStart(window);
				window.draw(cursorSprite);
				cursorSprite.setPosition(mouseX - cursorSprite.getGlobalBounds().width/2, mouseY - cursorSprite.getGlobalBounds().height/2);
				window.display();

				// If start button is clicked, go to LEVEL_1 game state
				Event startEvent;
				while (window.pollEvent(startEvent)) {
					if (startEvent.type == Event::MouseButtonPressed) {
						if (startButton.getGlobalBounds().contains(mouseX, mouseY)) {
							gameState = GameStates::LEVEL_1;
						}
					}
					else if (startEvent.type == Event::KeyPressed) {
						if (startEvent.key.code == sf::Keyboard::P) {
							Rescale(window);
							window.create(sf::VideoMode(640, 480, 32), "640 x 480 Screen");
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
				break;

			case GameStates::LEVEL_1:
				window.clear();
				Update();
				RenderLevel(window);
				window.display();
				break;
		}


    /*window.clear();
    Update();
    Render(window);
    window.display();*/
  }

  return 0;
}