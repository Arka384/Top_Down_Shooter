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

void Weapons::update(float dt, Camera view)
{
	auto i = bullets.begin();
	while (i != bullets.end()) {
		i->update(dt);
		if (ifOutsideView(*i, view))
			i = bullets.erase(i);
		else
			i++;
	}
}

bool Weapons::ifOutsideView(Bullet b, Camera view)
{
	int viewLeft = view.playerView.getCenter().x - view.playerView.getSize().x / 2;
	int viewRight = view.playerView.getCenter().x + view.playerView.getSize().x / 2;
	int viewUp = view.playerView.getCenter().y - view.playerView.getSize().y / 2;
	int viewDown = view.playerView.getCenter().y + view.playerView.getSize().y / 2;

	if (b.getPosition().x < viewLeft || b.getPosition().x > viewRight ||
		b.getPosition().y < viewUp || b.getPosition().y > viewDown)
		return true;
	else
		return false;
}

void Weapons::draw(sf::RenderWindow & window)
{
	for (auto i = bullets.begin(); i != bullets.end(); i++) {
		window.draw(*i);
	}
}
