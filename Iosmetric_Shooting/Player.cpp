#include "Player.h"

Player::Player(sf::Vector2f startingPos, sf::Vector2f size, sf::Vector2f windowSize)
{
	this->setSize(size);
	this->setOrigin(this->getSize().x / 2, this->getSize().y / 2);
	this->position = startingPos;
	this->setPosition(position);
	
	this->windowSize = windowSize;
}

void Player::update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets)
{
	//keyboard movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		position.x -= moveSpeed * dt;
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		position.x += moveSpeed * dt;
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		position.y -= moveSpeed * dt;
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		position.y += moveSpeed * dt;
		
	}

	this->setPosition(position);

	float dx = mousePos.x - position.x;
	float dy = mousePos.y - position.y;
	float angle = std::atan2(dy, dx);
	angle = angle * (180 / 3.1415);
	this->setRotation(angle + 180);


	//collision with enemy bullets
	auto i = enemyBullets.begin();
	while (i != enemyBullets.end()) {
		if (this->isColliding(*i)) {
			this->health -= 20;
			if (this->health <= 0)
				this->setFillColor(sf::Color::Red);
			i = enemyBullets.erase(i);
		}
		else
			i++;
	}
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(*this);
}
