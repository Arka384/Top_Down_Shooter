#pragma once
#include "EnemyManager.h"

class Player : public Entity {
private:
	sf::Vector2f position;
	sf::Vector2f movementDir;
	sf::Vector2f windowSize;

	float moveSpeed = 500.f;
	int health = 100;

public:
	Player(sf::Vector2f startingPos, sf::Vector2f size, sf::Vector2f windowSize);
	void update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets);
	void draw(sf::RenderWindow &window);

};

