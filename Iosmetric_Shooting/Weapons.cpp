#include "Weapons.h"

Weapons::Weapons(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;
}

void Weapons::fire(sf::Vector2f mousePos, sf::Vector2f playerPos)
{
	Bullet b(playerPos);

	float dx = mousePos.x - playerPos.x;
	float dy = mousePos.y - playerPos.y;
	float angle = std::atan2(dy, dx);
	b.setFireAngle(angle);
	bullets.push_back(b);
}

void Weapons::update(float dt, TileMap tileMapObj)
{
	auto i = bullets.begin();
	while (i != bullets.end()) {
		i->update(dt);

		if (i->getPosition().x < 0 || i->getPosition().x > windowSize.x ||
			i->getPosition().y < 0 || i->getPosition().y > windowSize.y)
			i = bullets.erase(i);
		else
			i++;
	}
	//destory bullets on tile map collision
	for (int j = 0; j < tileMapObj.tiles.size(); j++) {
		i = bullets.begin();
		while (i != bullets.end()) {
			if (tileMapObj.tiles[j].type != 169 && 
				tileMapObj.tiles[j].sprite.getGlobalBounds().intersects(i->getGlobalBounds())) {
				i = bullets.erase(i);
			}
			else
				i++;
		}
	}
	
}

void Weapons::draw(sf::RenderWindow & window)
{
	for (auto i = bullets.begin(); i != bullets.end(); i++) {
		window.draw(*i);
	}
}
