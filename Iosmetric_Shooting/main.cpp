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
	Ui gameUi(windowSize);
	gameUi.setGameState(4);

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
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		//update actions
		tempMousePos = sf::Mouse::getPosition(window);
		mousePos = window.mapPixelToCoords(tempMousePos);
		
		switch (gameUi.getGameState())
		{
		case 0:	//if in main menu
			gameUi.updateMainMenu(mousePos, mousePressed);
			break;
		case 1:	//if in character select state
			gameUi.updateCharacterSelect(mousePos, mousePressed);
			if (gameUi.playerType != player.getCharacterType())
				player.setCharacterType(gameUi.playerType);
			player.animateIdle(dt, sf::Vector2f(0.25, 0.25));
			break;
		case 2:	//how to 
			gameUi.updateHowToState(mousePos, mousePressed);
			break;
		case 3:	//if in countDown state
			gameUi.updateCountDown(dt);
			break;
		case 4:	//if play state
			player.update(dt, keyPressed, mousePos, enemyManager.enemyBullets, weapon);
			weapon.update(mousePressed, mousePos, player.getPosition(), player, dt, playerCam);
			enemyManager.update(dt, weapon, player.getPosition(), playerCam);
			playerCam.update(player.getPosition(), window, dt);
			map.update(playerCam, keyPressed, player.getPosition());
			gameUi.updatePlayState(playerCam.playerView.getSize(), playerCam.playerView.getCenter(), player.getHealth());
			
			if (player.isDead && player.deathAnimEnd)
				gameUi.setGameState(5);
			break;
		case 5:	//score state
			if (!gameUi.scoresLoaded)
				gameUi.loadScoreState(playerCam.playerView.getSize(), playerCam.playerView.getCenter(), enemyManager.killScores);
			gameUi.updateScoreState(playerCam.playerView.getSize(), playerCam.playerView.getCenter(), mousePos, mousePressed);
			break;
		case 6:
		default:
			break;
		}


		
		//////////////////////////////////////////////////////////////////////////
		//render functions
		window.clear(map.backgroundColor);

		switch (gameUi.getGameState())
		{
		case 0:	//main menu state
			gameUi.renderMainMenu(window);
			break;
		case 1:	//character select state
			gameUi.renderCharacterSelect(window);
			player.draw(window, weapon);
			break;
		case 2:	//how to 
			gameUi.renderHowToState(window);
			break;
		case 3:	//countDown
			gameUi.renderCountDown(window);
			break;
		case 4:	//if play state
			map.draw(window);
			if (!player.isDead)
				weapon.draw(window);
			player.draw(window, weapon);
			enemyManager.drawEnemies(window);
			gameUi.renderPlayState(window);
			break;
		case 5:	//score
			gameUi.renderScoreState(window);
			break;
		default:
			break;
		}

		window.display();
	}
}