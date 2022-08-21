#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position)
{
	this->setSize(sf::Vector2f(bulletSize, bulletSize));
	this->setFillColor(sf::Color::Red);
	this->setPosition(position);
}

void Bullet::setFireAngle(float angle)
{
	fireAngle = angle;
}

void Bullet::update(float dt)
{
	this->move(std::cos(fireAngle)*dt*speed, 0);
	this->move(0, std::sin(fireAngle)*dt*speed);
}
