#include "EnemyManager.h"

EnemyManager::EnemyManager(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;
}

void EnemyManager::spawnEnemies(void)
{
	//say it's level 1
	//so adding 4 static enemies
	int enemySize = 40;		//for now

	int x = std::rand() % static_cast<int>(windowSize.x - enemySize);
	int y = std::rand() % static_cast<int>(windowSize.y - enemySize);

	Enemy e(sf::Vector2f(x, y), sf::Vector2f(enemySize, enemySize));
	enemies.push_back(e);
	numberOfEnemy++;
	if (numberOfEnemy == maxNumberOfEnemy)
		maxEnemySpawnd = true;
}

void EnemyManager::update(float dt, Weapons & w, sf::Vector2f playerPos, Camera view)
{
	//spawn enemies
	spawnnigTimer += dt;
	if (spawnnigTimer >= spawnTime && maxEnemySpawnd == false) {
		spawnnigTimer = 0;
		spawnEnemies();
		spawnTime = 0.2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0 - 0.2)));
	}

	//update enemies
	auto i = enemies.begin();
	while (i != enemies.end()) {
		i->update(dt, w);
		shoot(playerPos, *i, dt);

		if (i->getHealth() <= 0)
			i = enemies.erase(i);
		else
			i++;
	}

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
		enemyReloadTime = 1.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2 - 1.0)));
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
		window.draw(*i);
	}
	for (auto i = enemyBullets.begin(); i != enemyBullets.end(); i++) {
		window.draw(*i);
	}
}
