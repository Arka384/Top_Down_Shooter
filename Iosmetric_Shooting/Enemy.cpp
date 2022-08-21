#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size)
{
	position = pos;
	this->setSize(size);
	this->setPosition(position);
}

int Enemy::getHealth(void)
{
	return health;
}

void Enemy::update(float dt, Weapons &w)
{
	auto i = w.bullets.begin();
	while(i != w.bullets.end()) {
		if (this->isColliding(*i)) {
			this->health -= 50;
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
