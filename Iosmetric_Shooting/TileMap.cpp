#include "TileMap.h"

TileMap::TileMap()
{
	completeTileSheet.loadFromFile("Assets/TileMap/tilesheet_complete.png");
}

void TileMap::generateTileMap(void)
{
	fflush(stdin);
	std::ifstream maptxt("Assets/TileMap/Map2/map2.txt");
	int tileValue = 0;
	
	for (int i = 0; i < mapDimension.y; i++) {
		for (int j = 0; j < mapDimension.x; j++) {

			int tileX = j * tileSize;
			int tileY = i * tileSize;

			maptxt >> tileValue;
			tileValue--;
			int tileIndexI = tileValue / tileSheetMax.x;
			int tileIndexJ = tileValue - (tileSheetMax.x * tileIndexI);
		
			Tile tile;
			tile.type = tileValue;
			tile.sprite.setTexture(completeTileSheet);
			tile.sprite.setTextureRect(sf::IntRect(tileIndexJ*tileSize, tileIndexI*tileSize, tileSize, tileSize));
			tile.sprite.setPosition(tileX, tileY);

			tiles.push_back(tile);
		}
	}
	maptxt.close();
}

void TileMap::drawTileMap(sf::RenderWindow & window)
{
	for (int i = 0; i < tiles.size(); i++)
		window.draw(tiles[i].sprite);
}
