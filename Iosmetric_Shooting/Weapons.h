#pragma once
#include "Camera.h"
#include <list>
#include <iostream>

class Weapons
{
private:
	sf::Vector2f windowSize;
	sf::Texture pistolTex, rifelTex, shotgunTex, muzzleFlashTex;
	sf::Sprite pistol, rifel, shotgun;
	int gunType = 1;	//pistol first
	float muzzleFlashTime = 0.1f;
	float flashTimer = 0.f;
	float pistolReloadTime = 0.2f, rifelReloadTime = 0.1f, shotGunReloadTime = 0.3f;
	float reloadTimer = 0.f;
	float gunSpawnTimeDelay = 5.f, gunEquippedTime = 10.f;
	float gunSpawnTimer = 0.f, gunEquippedTimer = 0.f;
	bool gunSpawnned = false;
	int spawndWeaponType = 0;

public:
	std::list<Bullet> bullets;
	sf::Sprite gunSprite, muzzleFlash, pickupGun[2], spawnnedGun;
	sf::Vector2f spritePosOffset = sf::Vector2f(0, 25);
	sf::Vector2f scaleSize = sf::Vector2f(0.1, 0.1);
	bool renderFlash = false;

	Weapons(sf::Vector2f windowSize);
	void fire(sf::Vector2f mousePos);
	void update(bool mousePressed, sf::Vector2f mousePos, sf::Vector2f playerPos, Entity player, float dt, Camera view);
	int spawnWeapon(sf::Vector2f playerPos, float dt, Camera view);
	void changeWeapon(int type);
	bool ifOutsideView(Bullet b, Camera view);
	void draw(sf::RenderWindow &window);
};

