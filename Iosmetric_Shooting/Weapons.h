#pragma once
#include "Camera.h"
#include <list>
#include <iostream>

class Weapons
{
private:
	sf::Vector2f windowSize;
	sf::Texture pistolTex, rifelTex, shotgunTex;
	sf::Sprite pistol, rifel, shotgun;

public:
	std::list<Bullet> bullets;
	sf::Sprite gunSprite;
	sf::Vector2f spritePosOffset = sf::Vector2f(0, 25);
	sf::Vector2f scaleSize = sf::Vector2f(0.1, 0.1);

	Weapons(sf::Vector2f windowSize);
	void fire(sf::Vector2f mousePos, sf::Vector2f playerPos);
	void update(sf::Vector2f mousePos, sf::Vector2f playerPos, float dt, Camera view);
	bool ifOutsideView(Bullet b, Camera view);
	void draw(sf::RenderWindow &window);
};

