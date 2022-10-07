#include "Bullet.h"
#include <iostream>
//sf::Texture Bullet::texture;

Bullet::Bullet()
{
	texture.loadFromFile("Assets/Extras/bullet.png");
}

Bullet::Bullet(sf::Vector2f position)
{
	this->setSize(sf::Vector2f(bulletSize, bulletSize));
	this->setOrigin(bulletSize / 2, bulletSize / 2);
	this->setFillColor(sf::Color::Red);
	this->setPosition(position);
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setScale(0.018, 0.018);
	this->sprite.setPosition(position);
}

void Bullet::setFireAngle(float angle)
{
	fireAngle = angle;
}

void Bullet::update(float dt)
{
	this->move(std::cos(fireAngle)*dt*speed, 0);
	this->move(0, std::sin(fireAngle)*dt*speed);
	this->sprite.move(std::cos(fireAngle) * dt * speed, 0);
	this->sprite.move(0, std::sin(fireAngle) * dt * speed);

}
