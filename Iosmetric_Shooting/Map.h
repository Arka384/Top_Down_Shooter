#pragma once
#include "Player.h"
#include <array>

typedef struct quad {
	int x;
	int y;
	std::list<sf::Sprite> objects;
}quad;

class Map
{
private:
	sf::Vector2f windowSize;
	sf::Texture rockTex[3];
	sf::Sprite rockSprite;
	sf::Vector2f scaleSize = sf::Vector2f(0.1, 0.1);
	sf::Vector2i oldViewIndex = sf::Vector2i(0, 0);

	std::list<quad> quads;

public:
	sf::Color backgroundColor = sf::Color(109, 105, 135, 255);

	Map(sf::Vector2f windowSize);
	void initMap(Camera view);
	void spwanObjectsInQuad(sf::Vector2i quadIndex, Camera view);
	void removeQuad(sf::Vector2i quadIndex);
	void update(Camera view, bool keyPressed, sf::Vector2f playerPo);
	bool outsideView(sf::Sprite object, Camera view);
	void draw(sf::RenderWindow& window);
};