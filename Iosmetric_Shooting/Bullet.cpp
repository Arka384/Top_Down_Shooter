#include "Bullet.h"
#include <iostream>
//sf::Texture Bullet::texture;

Bullet::Bullet()
{
	bulletTexture.loadFromFile("Assets/Extras/bullet.png");
	fireBallTexture.loadFromFile("Assets/Extras/fireball.png");
}

Bullet::Bullet(sf::Vector2f position, int bulletType)
{
	this->bulletType = bulletType;
	this->setSize(sf::Vector2f(bulletSize, bulletSize));
	this->setOrigin(bulletSize / 2, bulletSize / 2);
	this->setFillColor(sf::Color::Red);
	this->setPosition(position);
	if (this->bulletType == 1) {
		this->sprite.setTexture(bulletTexture);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
		this->sprite.setScale(0.018, 0.018);
	}
	else if (this->bulletType == 2) {
		this->sprite.setTexture(fireBallTexture);
		this->sprite.setTextureRect(sf::IntRect(0, 0, 500, 160));
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2 + this->sprite.getGlobalBounds().width / 4
			, this->sprite.getGlobalBounds().height / 2);
		this->sprite.setScale(0.3, 0.3);
	}
	
	this->sprite.setPosition(position);
}

void Bullet::setFireAngle(float angle)
{
	fireAngle = angle;
	this->sprite.setRotation(fireAngle*(180/3.1415));
}

void Bullet::update(float dt)
{
	this->move(std::cos(fireAngle)*dt*speed, 0);
	this->move(0, std::sin(fireAngle)*dt*speed);
	this->sprite.move(std::cos(fireAngle) * dt * speed, 0);
	this->sprite.move(0, std::sin(fireAngle) * dt * speed);
	
	if (this->bulletType == 2)
		animateFireball(dt);
}

void Bullet::animateFireball(float dt)
{
	animTimer += dt;
	if (animTimer > fireballAnimTime) {
		animTimer = 0;

		rectY += 160;
		if (rectY > 160 * 4)
			rectY = 0;
		this->sprite.setTextureRect(sf::IntRect(0, rectY, 500, 160));
	}
}