#pragma once
#include "Entity.h"
#include <cmath>
static sf::Texture bulletTexture;
static sf::Texture fireBallTexture;

class Bullet : public Entity {
private:
	float bulletSize = 15.f;
	float speed = 1000.f;
	float fireAngle = 0.f;
	int bulletType = 0;

	int rectY = 0;
	float fireballAnimTime = 0.05f;
	float animTimer = 0.f;
	
public:
	
	sf::Sprite sprite;

	Bullet();
	Bullet(sf::Vector2f position, int bulletType);
	void setFireAngle(float angle);
	void update(float dt);
	void animateFireball(float dt);
};

