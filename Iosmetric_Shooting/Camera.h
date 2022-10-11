#pragma once
#include "Bullet.h"
class Camera
{
private:
	int maxPlayerOffset = 300;
	float moveSpeed = 400.f;

public:
	sf::View playerView;
	sf::RectangleShape viewQuad;

	Camera(sf::Vector2f windowSize);
	void update(sf::Vector2f playerPos, sf::RenderWindow &window, float dt);
};

