#pragma once
#include "Player.h"

class Camera
{
private:
	int maxPlayerOffset = 300;
	float moveSpeed = 400.f;

public:
	sf::View playerView;

	Camera(sf::Vector2f windowSize);
	void update(Player player, sf::RenderWindow &window, float dt);
};

