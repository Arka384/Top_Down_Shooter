#pragma once
#include "Weapons.h"

class Enemy : public Entity {
private:
	sf::Vector2f position;
	int health = 100;

public:
	sf::Sprite sprite, shadowSprite;
	int currWalkTex = 0, maxWalkTex = 8;
	float walkAnimTime = 0.08f, walkAnimTimer = 0.f;
	bool flipped = false;
	bool inNearestPoint = false;
	int enemyType;	//for the record of sprite type
	sf::Color deathShadowColor;

	Enemy(sf::Vector2f pos, sf::Vector2f size, sf::Sprite sprite, sf::Sprite shaodw, int type);
	int getHealth(void);
	void update(float dt, sf::Vector2f playerPos, Weapons &w, Camera &camera);
	void draw(sf::RenderWindow &window);
};

