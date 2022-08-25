#include "Camera.h"
#include <ctime>
#include <cstdlib>

int main() 
{
	srand(static_cast<unsigned>(std::time(0)));

	sf::Vector2f windowSize = sf::Vector2f(1920, 1080);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Boii", sf::Style::Close);

	window.setFramerateLimit(60);
	sf::Time tm;
	sf::Clock clk;
	float dt = 0.f;
	sf::Vector2f mousePos;
	sf::Vector2i tempMousePos;
	bool keyPressed = false;

	Player player(sf::Vector2f(100, 100), sf::Vector2f(32, 32), windowSize);
	EnemyManager enemyManager(windowSize);
	Weapons weapon(windowSize);
	Camera playerCam(windowSize);


	while (window.isOpen()) {
		tm = clk.restart();
		dt = tm.asSeconds();

		sf::Event e;
		while (window.pollEvent(e)){
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseButtonPressed:
				weapon.fire(mousePos, player.getPosition());
				break;
			case sf::Event::KeyPressed:
				keyPressed = true;
				break;
			case sf::Event::KeyReleased:
				keyPressed = false;
			default:
				break;
			}
		}

		tempMousePos = sf::Mouse::getPosition(window);
		mousePos = window.mapPixelToCoords(tempMousePos);

		player.update(dt, keyPressed, mousePos, enemyManager.enemyBullets);
		weapon.update(dt);
		enemyManager.update(dt, weapon, player.getPosition());
		playerCam.update(player, window, dt);


		window.clear();
		weapon.draw(window);
		player.draw(window);
		enemyManager.drawEnemies(window);

		window.display();
	}
}