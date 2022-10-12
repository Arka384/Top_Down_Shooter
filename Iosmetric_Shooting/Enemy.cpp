#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size, sf::Sprite sprite)
{
	position = pos;
	this->setSize(size);
	this->setOrigin(this->getSize().x / 2, this->getSize().y / 2);
	this->setPosition(position);
	this->sprite = sprite;
	this->inNearestPoint = false;
}

int Enemy::getHealth(void)
{
	return health;
}

void Enemy::update(float dt, sf::Vector2f playerPos, Weapons &w, Camera& camera)
{
	flipped = (playerPos.x < this->getPosition().x) ? true : false;

	auto i = w.bullets.begin();
	while(i != w.bullets.end()) {
		if (this->isColliding(*i)) {
			this->health -= 50;
			camera.triggerShake = true;
			i = w.bullets.erase(i);
		}
		else
			i++;
	}
}

void Enemy::draw(sf::RenderWindow &window)
{
	window.draw(*this);
}
