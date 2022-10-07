#include "EnemyManager.h"

EnemyManager::EnemyManager(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;
	
	//loading textures
	type1WalkTexture.loadFromFile("Assets/characters/Enemy_1/walk.png");
	type1WalkSprite.setTexture(type1WalkTexture);
	type1WalkSprite.setTextureRect(sf::IntRect(sf::IntRect(0*subTexRectSize, 0, subTexRectSize, subTexRectSize)));
	type1WalkSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
	type1WalkSprite.setScale(scaleSize);

	enemySprite = type1WalkSprite;
}

void EnemyManager::spawnEnemies(void)
{
	int x = std::rand() % static_cast<int>(windowSize.x*1.25f);
	int y = std::rand() % static_cast<int>(windowSize.y*1.25f);

	Enemy e(sf::Vector2f(x, y), colRectSize, enemySprite);
	enemies.push_back(e);
	numberOfEnemy++;

	maxEnemySpawnd = (numberOfEnemy == maxNumberOfEnemy) ? true : false;
}

void EnemyManager::update(float dt, Weapons & w, sf::Vector2f playerPos, Camera view)
{
	//spawn enemies
	spawnnigTimer += dt;
	if (spawnnigTimer >= spawnTime && maxEnemySpawnd == false) {
		spawnnigTimer = 0;
		spawnEnemies();
		spawnTime = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0 - 0.5)));
	}

	//update enemies
	auto i = enemies.begin();
	while (i != enemies.end()) {
		i->update(dt, playerPos, w);

		moveEnemy(dt, playerPos, *i);
		animateWalk(dt, *i);
		i->sprite.setPosition(i->getPosition() - spritePosOffset);

		shoot(playerPos, *i, dt);

		if (i->getHealth() <= 0)
			i = enemies.erase(i);
		else
			i++;
	}
	numberOfEnemy = enemies.size();
	maxEnemySpawnd = (numberOfEnemy == maxNumberOfEnemy) ? true : false;
	

	//update enemy bullets
	auto enBullet = enemyBullets.begin();
	while (enBullet != enemyBullets.end()) {
		enBullet->update(dt);
		if (ifOutsizeView(*enBullet, view))
			enBullet = enemyBullets.erase(enBullet);
		else
			enBullet++;
	}
}

void EnemyManager::moveEnemy(float dt, sf::Vector2f playerPos, Enemy & e)
{
	float dx = playerPos.x - e.getPosition().x;
	float dy = playerPos.y - e.getPosition().y;
	float value = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
	if (value <= minDistBtPlayerEnemy) {
		e.inNearestPoint = true;
		return;
	}
	e.inNearestPoint = false;
	sf::Vector2f normDir = sf::Vector2f((dx / value), (dy / value));
	e.move(normDir*moveSpeed*dt);
}

void EnemyManager::animateWalk(float dt, Enemy &e)
{
	if (e.inNearestPoint) {
		e.currWalkTex = 0;
		e.sprite.setTextureRect(sf::IntRect(e.currWalkTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		e.sprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if (e.flipped)
			e.sprite.setScale(-scaleSize.x, scaleSize.y);
		else
			e.sprite.setScale(scaleSize);
		return;
	}
		

	e.walkAnimTimer += dt;
	if (e.walkAnimTimer >= e.walkAnimTime) {
		e.walkAnimTimer = 0;

		e.currWalkTex++;
		if (e.currWalkTex == e.maxWalkTex - 1)
			e.currWalkTex = 0;
		e.sprite.setTextureRect(sf::IntRect(e.currWalkTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		e.sprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if (e.flipped)
			e.sprite.setScale(-scaleSize.x, scaleSize.y);
		else
			e.sprite.setScale(scaleSize);
	}
	//type1WalkSprite.setPosition(position - spritePosOffset);
	
}

bool EnemyManager::ifOutsizeView(Bullet b, Camera view)
{
	int viewLeft = view.playerView.getCenter().x - view.playerView.getSize().x / 2;
	int viewRight = view.playerView.getCenter().x + view.playerView.getSize().x / 2;
	int viewUp = view.playerView.getCenter().y - view.playerView.getSize().y / 2;
	int viewDown = view.playerView.getCenter().y + view.playerView.getSize().y / 2;

	if (b.getPosition().x < viewLeft || b.getPosition().x > viewRight ||
		b.getPosition().y < viewUp || b.getPosition().y > viewDown)
		return true;
	else
		return false;
}

void EnemyManager::shoot(sf::Vector2f playerPos, Enemy enemy, float dt)
{
	reloadingTimer += dt;
	if (reloadingTimer >= enemyReloadTime) {
		reloadingTimer = 0;
		enemyReloadTime = 1.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.5 - 1.5)));
		//bullet fire for particular enemy
		Bullet b(enemy.getPosition());
		float dx = playerPos.x - enemy.getPosition().x;
		float dy = playerPos.y - enemy.getPosition().y;
		float angle = std::atan2(dy, dx);
		b.setFireAngle(angle);
		enemyBullets.push_back(b);
	}
}

void EnemyManager::drawEnemies(sf::RenderWindow & window)
{
	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		//window.draw(*i);
		window.draw(i->sprite);
	}
	for (auto i = enemyBullets.begin(); i != enemyBullets.end(); i++) {
		window.draw(i->sprite);
	}
}
