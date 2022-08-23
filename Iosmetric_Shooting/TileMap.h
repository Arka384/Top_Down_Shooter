#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>

typedef struct Tile {	//corresponds to each tile
	sf::Sprite sprite;
	int type;
}Tile;

class TileMap
{
private:
	sf::Texture completeTileSheet;
	sf::Vector2i tileSheetMax = sf::Vector2i(54, 40);

public:
	int tileSize = 32;	//all tiles are 32x32
	//sf::Vector2i mapDimension = sf::Vector2i(40, 22); //for map1
	sf::Vector2i mapDimension = sf::Vector2i(80, 60); //for map2
	//sf::Vector2i mapDimension = sf::Vector2i(150, 100); //for map2
	int allowedTile = 111 - 1;	//-1 for offset adjustment
	std::vector<Tile> tiles;	//the whole tile map actually

	TileMap();
	void generateTileMap(void);
	void drawTileMap(sf::RenderWindow &window);
};

