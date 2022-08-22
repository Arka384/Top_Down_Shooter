#include "TileMap.h"

TileMap::TileMap()
{
	completeTileSheet.loadFromFile("TileMap/tilesheet_complete.png");
}

void TileMap::loadSubTextures(void)
{
	std::ifstream subTex("TileMap/Map2/subTextures.txt");
	int num = 0;

	while (subTex >> num) {
		int key = num;
		subTex >> num;
		int val1 = num;
		subTex >> num;
		int val2 = num;

		subTextureCoords[key] = std::make_pair(val1, val2);
	}
	subTex.close();

	/*for (auto itr = subTextureCoords.begin(); itr != subTextureCoords.end(); ++itr) {
		std::cout << itr->first << " -> " << itr->second.first << " " << itr->second.second << '\n';
	}*/
}

void TileMap::generateTileMap(void)
{
	fflush(stdin);
	std::ifstream maptxt("TileMap/Map2/map2.txt");
	int tileValue = 0;
	
	for (int i = 0; i < mapDimension.y; i++) {
		for (int j = 0; j < mapDimension.x; j++) {

			int tileX = j * tileSize;
			int tileY = i * tileSize;

			maptxt >> tileValue;
			std::pair<int, int> tileCoords = subTextureCoords[tileValue];
			//std::cout << tileValue << " -> " << tileCoords.first << " " << tileCoords.second << "\n";
		
			Tile tile;
			tile.type = tileValue;
			tile.sprite.setTexture(completeTileSheet);
			tile.sprite.setTextureRect(sf::IntRect(tileCoords.first, tileCoords.second, tileSize, tileSize));
			tile.sprite.setPosition(tileX, tileY);
			//tile.sprite.setScale(0.5, 0.5);

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
