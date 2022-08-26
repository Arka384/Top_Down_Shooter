#pragma once
#include "Camera.h"
#include <list>
#include <iostream>

class Weapons
{
private:
	sf::Vector2f windowSize;

public:
	std::list<Bullet> bullets;

	Weapons(sf::Vector2f windowSize);
	void fire(sf::Vector2f mousePos, sf::Vector2f playerPos);
	void update(float dt, Camera view);
	bool ifOutsideView(Bullet b, Camera view);
	void draw(sf::RenderWindow &window);
};

