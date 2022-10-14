#pragma once
#include "EnemyManager.h"

class Player : public Entity {
private:
	sf::Vector2f position;
	sf::Vector2f movementDir;
	sf::Vector2f windowSize;
	float moveSpeed = 400.f;
	int health = 100;
	int characterType = 0;

	//sprites and textures
	//there will be three characters. So 3 sets of textures will be there.
	sf::Texture idleTexture[3], walkTexture[3], deathTexture[3];
	sf::Sprite playerSprite, idleSprite, walkSprite, deathSprite;

	std::string charTexureFileName = "Assets/characters/";

	int subTexRectSize = 2048;
	int currIdleTex = 0, maxIdleTex = 6;
	int currWalkTex = 0, maxWalkTex = 8;
	int currDeathTex = 0, maxDeathTex = 8;

	sf::Vector2f scaleSize = sf::Vector2f(0.15, 0.15), spritePosOffset = sf::Vector2f(0, 65), colRectSize = sf::Vector2f(40, 80);

	//animations
	bool playerIdle = true, flipped = false, gunBehindPlayer = false, deathAnimEnd = false, hitAnimated = true;
	float idleAnimTime = 0.2f, idleAnimTimer = 0.f;
	float walkAnimTime = 0.07f, walkAnimTimer = 0.f;
	float deathAnimTime = 0.08f, deathAnimTimer = 0.f;

public:
	float isDead = false;
	Player(sf::Vector2f startingPos, sf::Vector2f windowSize);
	void update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets, Weapons &weapon);
	void setCharacterType(int type);
	int getCharacterType(void);
	int getHealth(void);

	void animateIdle(float dt, sf::Vector2f requiredScale);
	void animateWalk(float dt);
	void animateDeath(float dt);

	void draw(sf::RenderWindow &window, Weapons wp);

};

