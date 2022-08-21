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
	std::map<int, std::pair<int, int>> subTextureCoords;

public:
	int tileSize = 32;	//all tiles are 32x32
	sf::Vector2i mapDimension = sf::Vector2i(32, 22);
	std::vector<Tile> tiles;	//the whole tile map actually

	TileMap();
	void loadSubTextures(void);
	void generateTileMap(void);
	void drawTileMap(sf::RenderWindow &window);
};

