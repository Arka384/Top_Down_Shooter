#include "Player.h"

Player::Player(sf::Vector2i tilePos, sf::Vector2f size, sf::Vector2f windowSize)
{
	this->playerTile = tilePos;
	this->setSize(size);
	this->position = sf::Vector2f(playerTile.x*size.x, playerTile.y*size.y);
	this->setPosition(position);
	this->windowSize = windowSize;
}

void Player::update(float dt, std::list<Bullet> &enemyBullets, TileMap tileMapObj)
{
	updateDealyTimer += dt;
	if (updateDealyTimer < updateDelay)
		return;
	else
		updateDealyTimer = 0.f;

	//keyboard movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		//position.x -= moveSpeed * dt;
		if (playerTile.x != 0) {
			int newTx = playerTile.x - 1;
			int newTy = playerTile.y;
			int tileVal = tileMapObj.tiles[newTx + newTy * tileMapObj.mapDimension.x].type;
			if (tileVal == tileMapObj.allowedTile) {
				playerTile.x = newTx;
				playerTile.y = newTy;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//position.x += moveSpeed * dt;
		if (playerTile.x != tileMapObj.mapDimension.x - 1) {
			int newTx = playerTile.x + 1;
			int newTy = playerTile.y;
			int tileVal = tileMapObj.tiles[newTx + newTy * tileMapObj.mapDimension.x].type;
			if (tileVal == tileMapObj.allowedTile) {
				playerTile.x = newTx;
				playerTile.y = newTy;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//position.y -= moveSpeed * dt;
		if (playerTile.y != 0) {
			int newTx = playerTile.x;
			int newTy = playerTile.y - 1;
			int tileVal = tileMapObj.tiles[newTx + newTy * tileMapObj.mapDimension.x].type;
			if (tileVal == tileMapObj.allowedTile) {
				playerTile.x = newTx;
				playerTile.y = newTy;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		//position.y += moveSpeed * dt;
		if (playerTile.y != tileMapObj.mapDimension.y - 1) {
			int newTx = playerTile.x;
			int newTy = playerTile.y + 1;
			int tileVal = tileMapObj.tiles[newTx + newTy * tileMapObj.mapDimension.x].type;
			if (tileVal == tileMapObj.allowedTile) {
				playerTile.x = newTx;
				playerTile.y = newTy;
			}
		}
	}


	position = sf::Vector2f(playerTile.x*this->getSize().x, playerTile.y*this->getSize().y);
	this->setPosition(position);

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
