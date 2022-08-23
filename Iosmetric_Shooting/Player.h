#pragma once
#include "EnemyManager.h"

class Player : public Entity {
private:
	std::vector<Tile> hits;
	sf::Vector2f position;
	sf::Vector2i playerTile;
	sf::Vector2f movementDir;
	sf::Vector2f windowSize;

	sf::Texture playerTexture, feetWalkTextures[20];
	sf::Sprite handGunSprite, feetWalkSprite;
	int feetWalkSpriteIndex = 0;


	float updateDelay = 0.02f;
	float updateDealyTimer = 0.f;
	float moveSpeed = 500.f;
	int health = 100;

public:
	Player(sf::Vector2i tilePos, sf::Vector2f size, sf::Vector2f windowSize);
	void update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets, TileMap tileMapObj);
	void draw(sf::RenderWindow &window);

};

