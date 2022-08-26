#pragma once
#include "Enemy.h"

class EnemyManager
{
private:
	sf::Vector2f windowSize;
	float enemyReloadTime = 1.f;
	float spawnTime = 0.2f;

	float spawnnigTimer = 0.f;
	float reloadingTimer = 0.f;

	int maxNumberOfEnemy = 4;
	int numberOfEnemy = 0;
	bool maxEnemySpawnd = false;


public:
	std::list<Enemy> enemies;
	std::list<Bullet> enemyBullets;

	EnemyManager(sf::Vector2f windowSize);
	void shoot(sf::Vector2f playerPos, Enemy enemy, float dt);
	void spawnEnemies(void);
	void update(float dt, Weapons &w, sf::Vector2f playerPos, Camera view);
	bool ifOutsizeView(Bullet b, Camera view);
	void drawEnemies(sf::RenderWindow &window);
};

