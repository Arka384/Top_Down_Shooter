#pragma once
#include "Entity.h"
#include <cmath>
static sf::Texture texture;

class Bullet : public Entity {
private:
	float bulletSize = 15.f;
	float speed = 800.f;
	float fireAngle = 0.f;
	
public:
	
	sf::Sprite sprite;

	Bullet();
	Bullet(sf::Vector2f position);
	void setFireAngle(float angle);
	void update(float dt);
};

