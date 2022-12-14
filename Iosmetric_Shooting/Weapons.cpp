#include "Weapons.h"

Weapons::Weapons(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;
}

void Weapons::load(void)
{
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

	//loading shotgun tuxtures
	shotgunTex.loadFromFile("Assets/Weapons/weaponR3.png");
	shotgun.setTexture(shotgunTex);
	shotgun.setOrigin(shotgun.getGlobalBounds().width / 2, shotgun.getGlobalBounds().height / 2);
	shotgun.setScale(scaleSize);

	pickupGun[0] = rifel;
	pickupGun[1] = shotgun;

	//loading muzzle flash textures
	muzzleFlashTex.loadFromFile("Assets/Extras/muzzle.png");
	muzzleFlash.setTexture(muzzleFlashTex);
	muzzleFlash.setOrigin(muzzleFlash.getGlobalBounds().width / 2, muzzleFlash.getGlobalBounds().height / 2);
	muzzleFlash.setScale(0.05, 0.05);

	crosshairTex.loadFromFile("Assets/Extras/crosshair.png");
	crosshair.setTexture(crosshairTex);
	crosshair.setScale(0.8, 0.8);
	crosshair.setOrigin(crosshair.getGlobalBounds().width / 2, crosshair.getGlobalBounds().height / 2);
	crosshair.setColor(sf::Color(255, 255, 255, 200));

	//loading sounds
	pistolSoundBuf.loadFromFile("Assets/Sounds/Weapon_sounds/9mm-pistol-shot.wav");
	pistolSound.setBuffer(pistolSoundBuf);
	pistolSound.setVolume(40);
	rifelSoundBuf.loadFromFile("Assets/Sounds/Weapon_sounds/ar-15-single-shot.wav");
	rifelSound.setBuffer(rifelSoundBuf);
	shotgunSoundBuf.loadFromFile("Assets/Sounds/Weapon_sounds/12-gauge-pump-action-shotgun.wav");
	shotgunSound.setBuffer(shotgunSoundBuf);

	pistolPickupBuf.loadFromFile("Assets/Sounds/Weapon_sounds/pistol-cock.wav");
	pistolPickup.setBuffer(pistolPickupBuf);
	rifelPickupBuf.loadFromFile("Assets/Sounds/Weapon_sounds/rifel_cock.wav");
	rifelPickup.setBuffer(rifelPickupBuf);
	shotgunPickupBuf.loadFromFile("Assets/Sounds/Weapon_sounds/shotgun_cock.wav");
	shotgunPickup.setBuffer(shotgunPickupBuf);

	resourceLoaded = true;
}

void Weapons::fire(sf::Vector2f mousePos)
{
	if (gunType == 1) {
		if (reloadTimer > pistolReloadTime)
			reloadTimer = 0;
		else
			return;
	}
	else if (gunType == 2) {
		if (reloadTimer > rifelReloadTime)
			reloadTimer = 0;
		else
			return;
	}
	else {
		if (reloadTimer > shotGunReloadTime)
			reloadTimer = 0;
		else
			return;
	}
	
	switch (gunType)
	{
	case 1:
		pistolSound.play();
		break;
	case 2:
		rifelSound.play();
		break;
	case 3:
		shotgunSound.play();
		break;
	default:
		break;
	}

	sf::Vector2f gunMid = sf::Vector2f(gunSprite.getPosition().x, gunSprite.getPosition().y);
	
	float dx = mousePos.x - gunMid.x;
	float dy = mousePos.y - gunMid.y;
	float angle = std::atan2(dy, dx);

	float yOffset = std::sin(angle) * (gunSprite.getGlobalBounds().width / 2);
	float xOffset = std::cos(angle) * (gunSprite.getGlobalBounds().width / 2);
	float finalX = gunMid.x + xOffset;
	float finalY = gunMid.y + yOffset;

	if (gunType == 3) {//if shotgun then multiple bullets
		for (int i = -31; i <= 31; i+=31) {	//these values represents angle
			Bullet* b = new Bullet(sf::Vector2f(finalX, finalY), 1);
			b->setFireAngle(angle+i);
			bullets.push_back(*b);
		}
	}	
	else {	//single bullets if not shotgun
		Bullet* b = new Bullet(sf::Vector2f(finalX, finalY), 1);
		b->setFireAngle(angle);
		bullets.push_back(*b);
	}

	muzzleFlash.setPosition(finalX, finalY);
	renderFlash = true;
}

void Weapons::update(bool mousePressed, sf::Vector2f mousePos, sf::Vector2f playerPos, Entity player, float dt, Camera view, bool playerStatus)
{
	flashTimer += dt;	//for muzzle flash
	reloadTimer += dt;	//for firing delay
	gunSpawnTimer += dt;	//for gun spawn
	if (gunEquipped) {
		gunEquippedTimer += dt;
		remainingGunTime = gunEquippedTime - gunEquippedTimer;
	}
		

	if (gunType == 2 && mousePressed && !playerStatus) {
		fire(mousePos);
	}
	crosshair.setPosition(mousePos);

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

		muzzleFlash.setPosition(finalX, finalY);
	}

	//spawn guns
	if (gunSpawnTimer >= gunSpawnTimeDelay && gunSpawnned == false) {
		gunSpawnTimer = 0;
		gunSpawnTimeDelay = 10 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (15 - 10)));
		spawndWeaponType = spawnWeapon(playerPos, dt, view);
	}
	if (gunSpawnned && gunSpawnTimer > 5) {
		gunSpawnned = false;
		gunSpawnTimer = 0;
	}
	//update spawned gun
	if (gunSpawnned && spawnnedGun.getGlobalBounds().intersects(player.getGlobalBounds())) {
		gunSpawnTimer = 0;
		gunEquippedTimer = 0;
		changeWeapon(spawndWeaponType + 2, true);
		gunSpawnned = false;
		gunEquipped = true;
	}
	//update equipped gun time
	if (gunEquipped && gunEquippedTimer >= gunEquippedTime) {
		changeWeapon(1, true);	//reset weapon to pistol
		gunEquipped = false;
		gunEquippedTimer = 0;
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

int Weapons::spawnWeapon(sf::Vector2f playerPos, float dt, Camera view)
{
	int direction = std::rand() % 4;
	int x = 0, y = 0;
	sf::Vector2f viewSize = view.playerView.getSize();

	switch (direction)
	{
	case 0:	//up
		x = std::rand() % static_cast<int>(viewSize.x);
		y = playerPos.y - viewSize.y / 2;
		break;
	case 1:	//down
		x = std::rand() % static_cast<int>(viewSize.x);
		y = playerPos.y + viewSize.y / 2;
		break;
	case 2:	//left
		x = playerPos.x - viewSize.x / 2;
		y = std::rand() % static_cast<int>(viewSize.y);
		break;
	case 3:	//right
		x = playerPos.x + viewSize.x / 2;
		y = std::rand() % static_cast<int>(viewSize.y);
		break;
	default:
		return 0;
		break;
	}

	int type = std::rand() % 2;
	spawnnedGun = pickupGun[type];
	spawnnedGun.setPosition(playerPos.x - 400, playerPos.y - 400);
	gunSpawnned = true;

	return type;
}

void Weapons::changeWeapon(int type, bool playSound)
{
	switch (type)
	{
	case 1:
		gunSprite = pistol;
		gunType = 1;
		if(playSound)
			pistolPickup.play();
		break;
	case 2:
		gunSprite = rifel;
		gunType = 2;
		if (playSound)
			rifelPickup.play();
		break;
	case 3:
		gunSprite = shotgun;
		gunType = 3;
		if (playSound)
			shotgunPickup.play();
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

void Weapons::resetStates(void)
{
	changeWeapon(1, false);
	flashTimer = 0.f;
	reloadTimer = 0.f;
	gunSpawnTimer = 0.f;
	gunSpawnned = false;
	spawndWeaponType = 0;
	gunEquippedTimer = 0;
	gunEquipped = false;
	remainingGunTime = 0;
	renderFlash = false;

	bullets.clear();
}

void Weapons::draw(sf::RenderWindow & window)
{
	for (auto i = bullets.begin(); i != bullets.end(); i++) {
		window.draw(i->sprite);
	}

	if (gunSpawnned) {
		window.draw(spawnnedGun);
	}
}
