#include "Map.h"
#include <ctime>
#include <cstdlib>

int main()
{
	srand(static_cast<unsigned>(std::time(0)));

	//std::cout << sf::VideoMode::getDesktopMode().width << " " << sf::VideoMode::getDesktopMode().height;
	sf::Vector2f windowSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Boii", sf::Style::Close);

	window.setFramerateLimit(120);
	sf::Time tm;
	sf::Clock clk;
	float dt = 0.f;
	sf::Vector2f mousePos;
	sf::Vector2i tempMousePos;
	bool keyPressed = false;
	bool mousePressed = false;

	Map map(windowSize);
	Bullet b;
	Player player(sf::Vector2f(windowSize.x/2, windowSize.y/2), windowSize);
	EnemyManager enemyManager(windowSize);
	Weapons weapon(windowSize);
	Camera playerCam(windowSize);

	map.initMap(playerCam);


	while (window.isOpen()) {
		tm = clk.restart();
		dt = tm.asSeconds();

		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();

			case sf::Event::MouseButtonPressed:
				mousePressed = true;
				weapon.fire(mousePos);
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;

			case sf::Event::KeyPressed:
				keyPressed = true;
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					weapon.changeWeapon(1);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
					weapon.changeWeapon(2);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
					weapon.changeWeapon(3);
				break;
			case sf::Event::KeyReleased:
				keyPressed = false;
				break;

			default:
				break;
			}
		}

		tempMousePos = sf::Mouse::getPosition(window);
		mousePos = window.mapPixelToCoords(tempMousePos);

		player.update(dt, keyPressed, mousePos, enemyManager.enemyBullets, weapon);
		weapon.update(mousePressed, mousePos, player.getPosition(), dt, playerCam);
		enemyManager.update(dt, weapon, player.getPosition(), playerCam);
		playerCam.update(player.getPosition(), window, dt);
		map.update(playerCam, keyPressed, player.getPosition());


		window.clear(map.backgroundColor);

		map.draw(window);
		if (!player.isDead)
			weapon.draw(window);
		player.draw(window, weapon);
		enemyManager.drawEnemies(window);

		window.display();
	}
}