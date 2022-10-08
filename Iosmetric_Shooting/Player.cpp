#include "Player.h"

Player::Player(sf::Vector2f startingPos, sf::Vector2f windowSize)
{
	this->setSize(colRectSize);
	this->setOrigin(this->getSize().x / 2, this->getSize().y / 2);
	this->position = startingPos;
	this->setPosition(position);
	
	this->windowSize = windowSize;

	//loading walk textures
	walkTexture.loadFromFile(walkTexureFileName);
	walkSprite.setTexture(walkTexture);
	walkSprite.setTextureRect(sf::IntRect(currWalkTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
	walkSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	walkSprite.setScale(scaleSize);
	//loading idle texture
	idleTexture.loadFromFile(idleTexureFileName);
	idleSprite.setTexture(idleTexture);
	idleSprite.setTextureRect(sf::IntRect(currIdleTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
	idleSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	idleSprite.setScale(scaleSize);
	playerSprite = idleSprite;	//initial sprite
	//loading death texture
	deathTexture.loadFromFile(deathTexureFileName);
	deathSprite.setTexture(deathTexture);
	deathSprite.setTextureRect(sf::IntRect(currDeathTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
	deathSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	deathSprite.setScale(scaleSize);
}

void Player::update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets, Weapons &weapon)
{
	//keyboard movement
	sf::Vector2f oldPos = position;
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

	/*float dx = mousePos.x - position.x;
	float dy = mousePos.y - position.y;*/
	float dx = mousePos.x - weapon.gunSprite.getPosition().x;
	float dy = mousePos.y - weapon.gunSprite.getPosition().y;
	float angle = std::atan2(dy, dx);
	angle = angle * (180 / 3.1415);
	weapon.gunSprite.setRotation(angle);
	weapon.muzzleFlash.setRotation(angle);

	//flipping the gun
	flipped = (mousePos.x < position.x) ? true : false;

	if (flipped) {
		weapon.gunSprite.setScale(weapon.scaleSize.x, -weapon.scaleSize.y);
	}
	else {
		weapon.gunSprite.setScale(weapon.scaleSize);
	}
	//if gun points upwords
	if (mousePos.y < position.y)
		gunBehindPlayer = true;
	else
		gunBehindPlayer = false;
		

	this->setPosition(position);
	weapon.gunSprite.setPosition(this->getPosition() + weapon.spritePosOffset);

	if (flipped)
		weapon.gunSprite.setPosition(weapon.gunSprite.getPosition().x - 20, weapon.gunSprite.getPosition().y);
	else
		weapon.gunSprite.setPosition(weapon.gunSprite.getPosition().x + 20, weapon.gunSprite.getPosition().y);

	//animations
	if (isDead && !deathAnimEnd) {
		animateDeath(dt);
		return;
	}
	
	if (!isDead) {
		if (oldPos == position) {
			playerIdle = true;
			animateIdle(dt);
		}
		else {
			playerIdle = false;
			animateWalk(dt);
		}
	}

	//collision with enemy bullets
	auto i = enemyBullets.begin();
	while (i != enemyBullets.end()) {
		if (this->isColliding(*i)) {
			this->health -= 20;
			playerSprite.setColor(sf::Color::Red);
			if (this->health <= 0) {
				isDead = true;
				this->setFillColor(sf::Color::Red);
			}
			i = enemyBullets.erase(i);
		}
		else
			i++;
	}
}

void Player::animateIdle(float dt)
{
	idleAnimTimer += dt;
	if (idleAnimTimer >= idleAnimTime) {
		idleAnimTimer = 0;
		
		currIdleTex++;
		if (currIdleTex == maxIdleTex - 1)
			currIdleTex = 0;
		idleSprite.setTextureRect(sf::IntRect(currIdleTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		idleSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if(flipped)
			idleSprite.setScale(-scaleSize.x, scaleSize.y);
		else
			idleSprite.setScale(scaleSize);
	}
	idleSprite.setPosition(position - spritePosOffset);
	playerSprite = idleSprite;
}

void Player::animateWalk(float dt)
{
	walkAnimTimer += dt;
	if (walkAnimTimer >= walkAnimTime) {
		walkAnimTimer = 0;

		currWalkTex++;
		if (currWalkTex == maxWalkTex - 1)
			currWalkTex = 0;
		walkSprite.setTextureRect(sf::IntRect(currWalkTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		walkSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if (flipped)
			walkSprite.setScale(-scaleSize.x, scaleSize.y);
		else
			walkSprite.setScale(scaleSize);
	}
	walkSprite.setPosition(position - spritePosOffset);
	playerSprite = walkSprite;
}

void Player::animateDeath(float dt)
{
	deathAnimTimer += dt;
	if (deathAnimTimer >= deathAnimTime) {
		deathAnimTimer = 0;

		currDeathTex++;
		if (currDeathTex == maxDeathTex - 1) {
			deathAnimEnd = true;
		}	

		deathSprite.setTextureRect(sf::IntRect(currDeathTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		deathSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if (flipped)
			deathSprite.setScale(-scaleSize.x, scaleSize.y);
		else
			deathSprite.setScale(scaleSize);
	}
	deathSprite.setPosition(position - spritePosOffset);
	playerSprite = deathSprite;
}

void Player::draw(sf::RenderWindow &window, Weapons wp)
{
	//window.draw(*this);
	if (gunBehindPlayer) {
		if (!isDead) {
			window.draw(wp.gunSprite);
			if (wp.renderFlash)
				window.draw(wp.muzzleFlash);
		}			
		window.draw(playerSprite);
	}
	else {
		window.draw(playerSprite);
		if (!isDead) {
			window.draw(wp.gunSprite);
			if (wp.renderFlash)
				window.draw(wp.muzzleFlash);
		}
			
	}
}
