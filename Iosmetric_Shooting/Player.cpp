#include "Player.h"

Player::Player(sf::Vector2f startingPos, sf::Vector2f windowSize)
{
	this->setSize(colRectSize);
	this->setOrigin(this->getSize().x / 2, this->getSize().y / 2);
	this->position = startingPos;
	this->setPosition(position);
	this->windowSize = windowSize;
}

void Player::load(void)
{
	//loading walk textures for all three characters
	for (int i = 0; i < 3; i++) {
		std::string walkTexureFileName = charTexureFileName + "Char_" + std::to_string(i + 1) + "/" + "walk.png";
		walkTexture[i].loadFromFile(walkTexureFileName);
	}

	//loading idle textures for all three characters
	for (int i = 0; i < 3; i++) {
		std::string idleTexureFileName = charTexureFileName + "Char_" + std::to_string(i + 1) + "/" + "idle.png";
		idleTexture[i].loadFromFile(idleTexureFileName);
	}

	//loading death textures for all three characters
	for (int i = 0; i < 3; i++) {
		std::string deathTexureFileName = charTexureFileName + "Char_" + std::to_string(i + 1) + "/" + "death.png";
		deathTexture[i].loadFromFile(deathTexureFileName);
	}
	setCharacterType(2);

	shadowTex.loadFromFile("Assets/Extras/shadow.png");
	shadow.setTexture(shadowTex);
	shadow.setScale(0.035, 0.035);

	fireTex.loadFromFile("Assets/Extras/fireball.png");
	fire.setTexture(fireTex);
	fire.setTextureRect(sf::IntRect(0, 0, 500, 160));
	fire.setScale(0.6, 0.8);
	fire.setRotation(90.f);
	fire.setOrigin(fire.getGlobalBounds().width / 2, fire.getGlobalBounds().height / 2);
	fire.setColor(sf::Color(254, 227, 138, 200));


	//loading sounds
	deathSoundBuf.loadFromFile("Assets/Sounds/Player_sounds/death.wav");
	deathSound.setBuffer(deathSoundBuf);
	hurtSoundBuf.loadFromFile("Assets/Sounds/Player_sounds/umph.wav");
	hurtSound.setBuffer(hurtSoundBuf);

	resourceLoaded = true;
}

void Player::update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets, Weapons &weapon, int totalScore)
{
	//keyboard movement
	sf::Vector2f oldPos = position;
	if (!isDead) {
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
	}
	shadow.setPosition(position.x - 30, position.y - 5);

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

	if ((totalScore - lastChadToggleScore >= chadToggleScore) && !isDead 
			&& !gigaChadMode && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		gigaChadMode = true;
		weapon.changeWeapon(2, true);
	}
	if (gigaChadMode) {
		chadModeTimer += dt;
		if (chadModeTimer >= chadeModeTime - 5) {
			blinkTimer += dt;
			if (blinkTimer >= blinkTime) {
				blinkTimer = 0;
				playerBlink = (playerBlink) ? false : true;
			}
				
		}
		animateFire(dt);
		if (chadModeTimer >= chadeModeTime) {
			gigaChadMode = false;
			playerBlink = false;
			chadModeTimer = 0;
			lastChadToggleScore = totalScore;
			if (!weapon.gunEquipped)
				weapon.changeWeapon(1, true);
		}
	}

	//animations
	if (isDead && !deathAnimEnd) {
		animateDeath(dt);
		return;
	}
	
	if (!isDead) {
		if (oldPos == position) {
			playerIdle = true;
			animateIdle(dt, scaleSize);
		}
		else {
			playerIdle = false;
			animateWalk(dt);
		}
	}

	if (deathAnimEnd) {
		deathSceneKeepTimer += dt;
		if (deathSceneKeepTimer > 3)
			deathSceneEnd = true;
	}

	//collision with enemy bullets
	auto i = enemyBullets.begin();
	while (i != enemyBullets.end()) {
		if (this->isColliding(*i)) {
			if (!gigaChadMode) {	//invincible in chad mode
				this->health -= 20;	//comment this line and you will be invincible
				playerSprite.setColor(sf::Color::Red);
			}

			if(!deathAnimEnd)
				hurtSound.play();

			if (this->health <= 0) {
				isDead = true;
				if(deathSound.getStatus() != sf::Sound::Playing)
					deathSound.play();
				this->setFillColor(sf::Color::Red);
			}
			i = enemyBullets.erase(i);
		}
		else
			i++;
	}
}

void Player::setCharacterType(int type)
{
	//type varries between 0-2
	//walk sprites
	characterType = type;
	walkSprite.setTexture(walkTexture[characterType]);
	walkSprite.setTextureRect(sf::IntRect(currWalkTex * subTexRectSize, 0, subTexRectSize, subTexRectSize));
	walkSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	walkSprite.setScale(scaleSize);

	//idle sprites
	idleSprite.setTexture(idleTexture[characterType]);
	idleSprite.setTextureRect(sf::IntRect(currIdleTex * subTexRectSize, 0, subTexRectSize, subTexRectSize));
	idleSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	idleSprite.setScale(scaleSize);
	playerSprite = idleSprite;	//initial sprite

	//death sprties
	deathSprite.setTexture(deathTexture[characterType]);
	deathSprite.setTextureRect(sf::IntRect(currDeathTex * subTexRectSize, 0, subTexRectSize, subTexRectSize));
	deathSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	deathSprite.setScale(scaleSize);
}

int Player::getCharacterType(void)
{
	return this->characterType;
}

int Player::getHealth(void)
{
	return this->health;
}

void Player::resetStates(void)
{
	this->health = 100;
	this->characterType = 0;
	deathSceneKeepTimer = 0;
	position = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
	currIdleTex = currWalkTex = currDeathTex = 0;
	playerIdle = true;
	flipped = false;
	gunBehindPlayer = false;
	hitAnimated = true;
	isDead = false;
	deathAnimEnd = false;
	deathSceneEnd = false;
	playerBlink = false;
	gigaChadMode = false;
	lastChadToggleScore = 0;
}

int Player::killsLeftToChadMode(int currentScore)
{
	return (lastChadToggleScore + chadToggleScore) - currentScore;
}

void Player::animateIdle(float dt, sf::Vector2f requiredScale)
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
			idleSprite.setScale(-requiredScale.x, requiredScale.y);
		else
			idleSprite.setScale(requiredScale);
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

void Player::animateFire(float dt)
{
	fireAnimTimer += dt;
	if (fireAnimTimer > fireAnimTime) {
		fireAnimTimer = 0;

		rectY += 160;
		if (rectY > 160 * 4)
			rectY = 0;
		fire.setTextureRect(sf::IntRect(0, rectY, 500, 160));
	}
	fire.setPosition(position.x - fire.getGlobalBounds().width / 2.6, position.y - fire.getGlobalBounds().height/1.45);
}

void Player::draw(sf::RenderWindow &window, Weapons wp, int gameState)
{
	if (playerBlink)
		return;

	if (gigaChadMode) {
		window.draw(fire);
	}

	if (gunBehindPlayer) {
		if (!isDead && gameState == 4) {
			window.draw(wp.gunSprite);
			if (wp.renderFlash)
				window.draw(wp.muzzleFlash);
		}			
		window.draw(playerSprite);
	}
	else {
		window.draw(playerSprite);
		if (!isDead && gameState == 4) {
			window.draw(wp.gunSprite);
			if (wp.renderFlash)
				window.draw(wp.muzzleFlash);
		}
	}

	
}
