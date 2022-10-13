#pragma once
#include "Ui.h"

class Camera
{
private:
	int maxPlayerOffset = 300;
	float moveSpeed = 400.f;
	float shakeTime = 0.1f, shakeTimer = 0.f;

public:
	sf::View playerView;
	bool triggerShake = false;

	Camera(sf::Vector2f windowSize);
	void update(sf::Vector2f playerPos, sf::RenderWindow &window, float dt);
	void cameraShake(float dt);
};

