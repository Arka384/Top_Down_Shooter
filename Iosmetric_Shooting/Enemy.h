#pragma once
#include "Weapons.h"

class Enemy : public Entity {
private:
	sf::Vector2f position;
	int health = 100;

public:
	Enemy(sf::Vector2f pos, sf::Vector2f size);
	int getHealth(void);
	void update(float dt, Weapons &w);
	void draw(sf::RenderWindow &window);
};

