#include "Camera.h"

Camera::Camera(sf::Vector2f windowSize)
{
	playerView.setSize(windowSize);
}

void Camera::update(Player player, sf::RenderWindow &window, float dt)
{
	sf::Vector2f diff = player.getPosition() - playerView.getCenter();
	float dist = std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2));

	if (dist > maxPlayerOffset) {
		playerView.move((diff.x / dist)*moveSpeed*dt, (diff.y / dist)*moveSpeed*dt);
		window.setView(playerView);
	}
}
