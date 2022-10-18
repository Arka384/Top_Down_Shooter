#pragma once
#include "Enemy.h"

class EnemyManager
{
private:
	sf::Vector2f windowSize;
	float enemyReloadTime = 1.f;
	float spawnTime = 1.f;
	float spawnnigTimer = 0.f;
	float reloadingTimer = 0.f;
	float moveSpeed = 300.f;
	int maxNumberOfEnemy = 5;
	int numberOfEnemy = 0;
	bool maxEnemySpawnd = false;

	//sprite and textures
	sf::Texture walkTextures[4], genericDeathTex, shadowTex;
	sf::Sprite enemyWalkSprites[4], shadow;
	sf::Sprite genericDeathSprite;
	sf::Vector2f scaleSize = sf::Vector2f(0.15, 0.15), spritePosOffset = sf::Vector2f(0, 60), colRectSize = sf::Vector2f(40, 80);
	sf::SoundBuffer hurtBuf;
	sf::Sound hurt;

	int subTexRectSize = 2048;
	int minDistBtPlayerEnemy = 450;	//least distance between player and enemy

	std::list<std::pair<sf::Sprite, float>> deathShadows;

public:
	std::vector<int> killScores;
	std::list<Enemy> enemies;
	std::list<Bullet> enemyBullets;
	sf::Sprite enemySprite;
	bool resourceLoaded = false;

	EnemyManager(sf::Vector2f windowSize);
	void load(void);
	void shoot(sf::Vector2f playerPos, Enemy enemy, float dt);
	void spawnEnemies(sf::Vector2f playerPos, Camera view);
	void update(float dt, Weapons &w, sf::Vector2f playerPos, Camera &view);
	void moveEnemy(float dt, sf::Vector2f playerPos, Enemy &e);
	void animateWalk(float dt, Enemy &e);
	bool ifOutsizeView(Bullet b, Camera view);
	void resetStates(void);
	void drawEnemies(sf::RenderWindow &window);
};

