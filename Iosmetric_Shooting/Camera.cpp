#include "Camera.h"
#include <iostream>

Camera::Camera(sf::Vector2f windowSize)
{
	playerView.setSize(windowSize);

	if(windowSize.x <= 1280 && windowSize.y <= 720)
		playerView.zoom(1.4);
	else if (windowSize.x <= 1366 && windowSize.y <= 768)
		playerView.zoom(1.25);

}

void Camera::update(sf::Vector2f playerPos, sf::RenderWindow &window, float dt)
{
	playerView.setCenter(playerPos);

	if (triggerShake)
		cameraShake(dt);

	window.setView(playerView);
}

void Camera::cameraShake(float dt)
{
	shakeTimer += dt;
	if (shakeTimer >= shakeTime) {
		shakeTimer = 0;
		triggerShake = false;
		return;
	}

	float offset = 5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10 - 5)));
	float direction = rand() % 2;
	float newCenterX = playerView.getCenter().x + ((direction == 0) ? offset : -offset);
	float newCenterY = playerView.getCenter().y + ((direction == 0) ? offset : -offset);
	playerView.setCenter(newCenterX, newCenterY);

}
