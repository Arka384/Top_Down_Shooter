#pragma once
#include "Bullet.h"
#include <list>

class Weapons
{
private:
	sf::Vector2f windowSize;

public:
	std::list<Bullet> bullets;

	Weapons(sf::Vector2f windowSize);
	void fire(sf::Vector2f mousePos, sf::Vector2f playerPos);
	void update(float dt);
	void draw(sf::RenderWindow &window);
};

