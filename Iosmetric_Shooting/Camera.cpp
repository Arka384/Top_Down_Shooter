#include "Camera.h"

Camera::Camera(sf::Vector2f windowSize)
{
	playerView.setSize(windowSize);
	//playerView.zoom(1.5);
}

void Camera::update(sf::Vector2f playerPos, sf::RenderWindow &window, float dt)
{
	playerView.setCenter(playerPos);
	window.setView(playerView);

	viewQuad.setPosition(playerView.getCenter());
}
