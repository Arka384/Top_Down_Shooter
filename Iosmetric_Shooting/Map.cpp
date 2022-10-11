#include "Map.h"

Map::Map(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;

	//loading rock textures
	mapObjects[0].loadFromFile("Assets/Environment/rock1.png");
	mapObjects[1].loadFromFile("Assets/Environment/rock2.png");
	mapObjects[2].loadFromFile("Assets/Environment/rock3.png");
	mapObjects[3].loadFromFile("Assets/Environment/cluster1.png");
	mapObjects[4].loadFromFile("Assets/Environment/cluster2.png");
	mapObjects[5].loadFromFile("Assets/Environment/cluster3.png");

}

void Map::initMap(Camera view)
{
	//loading initial 8 quads
	//middle
	spwanObjectsInQuad(sf::Vector2i(0, 0), view);
	//top left
	spwanObjectsInQuad(sf::Vector2i(-1, -1), view);
	//top
	spwanObjectsInQuad(sf::Vector2i(0, -1), view);
	//top right
	spwanObjectsInQuad(sf::Vector2i(1, -1), view);
	//left
	spwanObjectsInQuad(sf::Vector2i(-1, 0), view);
	//right
	spwanObjectsInQuad(sf::Vector2i(1, 0), view);
	//bottom left
	spwanObjectsInQuad(sf::Vector2i(-1, 1), view);
	//bottom
	spwanObjectsInQuad(sf::Vector2i(0, 1), view);
	//bottom right
	spwanObjectsInQuad(sf::Vector2i(1, 1), view);
}

void Map::spwanObjectsInQuad(sf::Vector2i quadIndex, Camera view)
{
	int quadLeft = quadIndex.x * view.playerView.getSize().x - view.playerView.getSize().x / 2;
	int quadUp = quadIndex.y * view.playerView.getSize().y - view.playerView.getSize().y / 2;

	quad temp;
	temp.x = quadIndex.x;
	temp.y = quadIndex.y;
	for (int i = 0; i < maxNumberOfMapObject; i++) {
		int x = std::rand() % (static_cast<int>(view.playerView.getSize().x)) + quadLeft;
		int y = std::rand() % (static_cast<int>(view.playerView.getSize().y)) + quadUp;
		int objectType = std::rand() % 6;

		sf::Sprite tempSprite;
		tempSprite.setTexture(mapObjects[objectType]);
		if (objectType <= 2) {
			float scale = 0.005 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.1 - 0.005)));
			tempSprite.setScale(scale, scale);
		}
		else {
			float scale = 0.05 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.15 - 0.05)));
			tempSprite.setScale(scale, scale);
		}


		tempSprite.setColor(backgroundColor);
		tempSprite.setPosition(x, y);
		temp.objects.push_back(tempSprite);
	}
	quads.push_back(temp);
}

void Map::removeQuad(sf::Vector2i quadIndex)
{
	auto i = quads.begin();
	while (i != quads.end()) {
		if (i->x == quadIndex.x && i->y == quadIndex.y)
			i = quads.erase(i);
		else
			i++;
	}
}

void Map::update(Camera view, bool keyPressed, sf::Vector2f playerPos)
{
	sf::Vector2i currViewIndex = sf::Vector2i(playerPos.x / windowSize.x, playerPos.y / windowSize.y);
	//std::cout << currViewIndex.x << " " << currViewIndex.y << "\n";
	if (oldViewIndex == currViewIndex)
		return;
	
	//view changed. updates required
	if (currViewIndex.x != oldViewIndex.x) {
		if (oldViewIndex.x > currViewIndex.x) {	//player moved to left quad
			//load top left quad
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y - 1), view);
			//remove top right quad
			removeQuad(sf::Vector2i(currViewIndex.x + 2, currViewIndex.y - 1));

			//load left quad
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y), view);
			//remove right quad
			removeQuad(sf::Vector2i(currViewIndex.x + 2, currViewIndex.y));

			//load bottom left quad
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y + 1), view);
			//remove bottom right quad
			removeQuad(sf::Vector2i(currViewIndex.x + 2, currViewIndex.y + 1));
		}
		else {	//player moved to right quad
			//load top right quad
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y - 1), view);
			//remove top left quad
			removeQuad(sf::Vector2i(currViewIndex.x - 2, currViewIndex.y - 1));

			//load right quad
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y), view);
			//remove left quad
			removeQuad(sf::Vector2i(currViewIndex.x - 2, currViewIndex.y));

			//load bottom right quad
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y + 1), view);
			//remove bottom left quad
			removeQuad(sf::Vector2i(currViewIndex.x - 2, currViewIndex.y + 1));

		}
	}

	if (currViewIndex.y != oldViewIndex.y) {
		if (oldViewIndex.y > currViewIndex.y) {	//player moved up
			//load up left
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y - 1), view);
			//remove bottom left
			removeQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y + 2));

			//load up
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x, currViewIndex.y - 1), view);
			//remove down
			removeQuad(sf::Vector2i(currViewIndex.x, currViewIndex.y + 2));

			//load up right
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y - 1), view);
			//remove bottom right
			removeQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y + 2));
		}
		else {	//player moved down
			//load bottom left
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y + 1), view);
			//remove up left
			removeQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y - 2));

			//load bottom
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x, currViewIndex.y + 1), view);
			//remove up
			removeQuad(sf::Vector2i(currViewIndex.x, currViewIndex.y - 2));

			//load bottom right
			spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y + 1), view);
			//remove up right
			removeQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y - 2));
		}
	}
	
	oldViewIndex = currViewIndex;
}

bool Map::outsideView(sf::Sprite object, Camera view)
{
	int viewLeft = view.playerView.getCenter().x - view.playerView.getSize().x / 2;
	int viewRight = view.playerView.getCenter().x + view.playerView.getSize().x / 2;
	int viewUp = view.playerView.getCenter().y - view.playerView.getSize().y / 2;
	int viewDown = view.playerView.getCenter().y + view.playerView.getSize().y / 2;

	if (object.getPosition().x < viewLeft || object.getPosition().x > viewRight ||
		object.getPosition().y < viewUp || object.getPosition().y > viewDown)
		return true;
	else
		return false;
}

void Map::draw(sf::RenderWindow& window)
{
	for (auto i = quads.begin(); i != quads.end(); i++)
		for (auto j = i->objects.begin(); j != i->objects.end(); j++)
			window.draw(*j);
}
