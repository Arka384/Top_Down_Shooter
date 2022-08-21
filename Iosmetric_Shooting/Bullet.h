#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <cmath>

class Bullet : public Entity {
private:
	float bulletSize = 8.f;
	float speed = 1000.f;
	float fireAngle = 0.f;
	
public:
	Bullet(sf::Vector2f position);
	void setFireAngle(float angle);
	void update(float dt);
};

