#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Entity : public sf::RectangleShape {
public:
	bool isColliding(Entity &other) {
		return this->getGlobalBounds().intersects(other.getGlobalBounds());
	}
};