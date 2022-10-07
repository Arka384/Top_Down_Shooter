#include "Weapons.h"

Weapons::Weapons(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;

	//loading pistol textures
	pistolTex.loadFromFile("Assets/Weapons/weaponR2.png");
	pistol.setTexture(pistolTex);
	pistol.setOrigin(pistol.getGlobalBounds().width / 2 - 80, pistol.getGlobalBounds().height / 2 + 20);
	pistol.setScale(scaleSize);
	gunSprite = pistol;

	//loading rifel textures
	rifelTex.loadFromFile("Assets/Weapons/weaponR1.png");
	rifel.setTexture(rifelTex);
	rifel.setOrigin(rifel.getGlobalBounds().width / 2, rifel.getGlobalBounds().height / 2);
	rifel.setScale(scaleSize);
	//gunSprite = rifel;

	//loading shotgun tuxtures
	shotgunTex.loadFromFile("Assets/Weapons/weaponR3.png");
	shotgun.setTexture(shotgunTex);
	shotgun.setOrigin(shotgun.getGlobalBounds().width / 2, shotgun.getGlobalBounds().height / 2);
	shotgun.setScale(scaleSize);
	//gunSprite = shotgun;

	//loading muzzle flash textures
	muzzleFlashTex.loadFromFile("Assets/Extras/muzzle.png");
	muzzleFlash.setTexture(muzzleFlashTex);
	muzzleFlash.setOrigin(muzzleFlash.getGlobalBounds().width / 2, muzzleFlash.getGlobalBounds().height / 2);
	muzzleFlash.setScale(0.05, 0.05);
}

void Weapons::fire(sf::Vector2f mousePos, sf::Vector2f playerPos)
{
	sf::Vector2f gunMid = sf::Vector2f(gunSprite.getPosition().x, gunSprite.getPosition().y);
	
	float dx = mousePos.x - gunMid.x;
	float dy = mousePos.y - gunMid.y;
	float angle = std::atan2(dy, dx);

	float yOffset = std::sin(angle) * (gunSprite.getGlobalBounds().width / 2);
	float xOffset = std::cos(angle) * (gunSprite.getGlobalBounds().width / 2);
	float finalX = gunMid.x + xOffset;
	float finalY = gunMid.y + yOffset;

	Bullet b(sf::Vector2f(finalX, finalY));
	b.setFireAngle(angle);
	bullets.push_back(b);

	//muzzleFlash.setRotation(angle);
	muzzleFlash.setPosition(finalX, finalY);
	renderFlash = true;
}

void Weapons::update(sf::Vector2f mousePos, sf::Vector2f playerPos, float dt, Camera view)
{
	flashTimer += dt;
	if (flashTimer > muzzleFlashTime) {
		flashTimer = 0;
		renderFlash = false;
	}
	else {	//update muzzle flash location
		sf::Vector2f gunMid = sf::Vector2f(gunSprite.getPosition().x, gunSprite.getPosition().y);

		float dx = mousePos.x - gunMid.x;
		float dy = mousePos.y - gunMid.y;
		float angle = std::atan2(dy, dx);

		float yOffset = std::sin(angle) * ((gunSprite.getGlobalBounds().width + 70) / 2);
		float xOffset = std::cos(angle) * ((gunSprite.getGlobalBounds().width + 70) / 2);
		float finalX = gunMid.x + xOffset;
		float finalY = gunMid.y + yOffset;

		//muzzleFlash.setRotation(angle);
		muzzleFlash.setPosition(finalX, finalY);
	}

	auto i = bullets.begin();
	while (i != bullets.end()) {
		i->update(dt);
		if (ifOutsideView(*i, view))
			i = bullets.erase(i);
		else
			i++;
	}
}

void Weapons::changeWeapon(int type)
{
	switch (type)
	{
	case 1:
		gunSprite = pistol;
		break;
	case 2:
		gunSprite = rifel;
		break;
	case 3:
		gunSprite = shotgun;
		break;
	default:
		break;
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
		window.draw(i->sprite);
		//window.draw(*i);
	}
	
}
