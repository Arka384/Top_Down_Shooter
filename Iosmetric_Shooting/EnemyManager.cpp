#include "EnemyManager.h"

EnemyManager::EnemyManager(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;	
}

void EnemyManager::load(void) {
	//loading textures
	std::string walkTexFileName = "Assets/characters/Enemy_";
	for (int i = 0; i < 4; i++) {
		std::string currFileName = walkTexFileName + std::to_string(i + 1) + "/walk.png";
		walkTextures[i].loadFromFile(currFileName);

		enemyWalkSprites[i].setTexture(walkTextures[i]);
		enemyWalkSprites[i].setTextureRect(sf::IntRect(sf::IntRect(0 * subTexRectSize, 0, subTexRectSize, subTexRectSize)));
		enemyWalkSprites[i].setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		enemyWalkSprites[i].setScale(scaleSize);

		killScores.push_back(0);	//pushing 4 times
	}
	enemySprite = enemyWalkSprites[0];

	//loading generic death texture
	genericDeathTex.loadFromFile("Assets/Generic_death_animation/generic_death.png");
	genericDeathSprite.setTexture(genericDeathTex);
	genericDeathSprite.setTextureRect(sf::IntRect(0, 0, 2048, 2048));
	genericDeathSprite.setOrigin(genericDeathSprite.getGlobalBounds().width / 2, genericDeathSprite.getGlobalBounds().height / 2);
	genericDeathSprite.setScale(0.18, 0.18);

	shadowTex.loadFromFile("Assets/Extras/shadow.png");
	shadow.setTexture(shadowTex);
	shadow.setScale(0.035, 0.035);

	//loading sounds
	hurtBuf.loadFromFile("Assets/Sounds/Player_sounds/hit.wav");
	hurt.setBuffer(hurtBuf);

	resourceLoaded = true;
}

void EnemyManager::spawnEnemies(sf::Vector2f playerPos, Camera view)
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
		return;
		break;
	}

	int enemyType = std::rand() % 4;
	enemySprite = enemyWalkSprites[enemyType];

	Enemy *e = new Enemy(sf::Vector2f(x, y), colRectSize, enemySprite, this->shadow, enemyType);
	enemies.push_back(*e);
	numberOfEnemy++;

	maxEnemySpawnd = (numberOfEnemy == maxNumberOfEnemy) ? true : false;
}

void EnemyManager::update(float dt, Weapons & w, sf::Vector2f playerPos, Camera &view)
{
	//spawn enemies
	spawnnigTimer += dt;
	if (spawnnigTimer >= spawnTime && maxEnemySpawnd == false) {
		spawnnigTimer = 0;
		spawnEnemies(playerPos, view);
		spawnTime = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0 - 0.5)));
	}

	//update enemies
	auto i = enemies.begin();
	while (i != enemies.end()) {
		i->update(dt, playerPos, w, view);

		moveEnemy(dt, playerPos, *i);
		animateWalk(dt, *i);
		i->sprite.setPosition(i->getPosition() - spritePosOffset);
		i->shadowSprite.setPosition(i->getPosition().x - 30, i->getPosition().y - 5);

		shoot(playerPos, *i, dt);

		if (i->getHealth() <= 0) {	//enemy is down trigger death animation
			hurt.play();
			genericDeathSprite.setColor(i->deathShadowColor);
			genericDeathSprite.setPosition(i->sprite.getPosition());
			deathShadows.push_back(std::make_pair(genericDeathSprite, 0.f));

			//updating score
			killScores[i->enemyType]++;

			i = enemies.erase(i);
		}
		else
			i++;
	}
	numberOfEnemy = enemies.size();
	maxEnemySpawnd = (numberOfEnemy == maxNumberOfEnemy) ? true : false;
	
	//update enemy death shadows
	auto j = deathShadows.begin();
	while (j != deathShadows.end()) {
		j->second += dt;
		if (j->second > 0.1f)
			j->first.setTextureRect(sf::IntRect(2048, 0, 2048, 2048));
		if (j->second > 0.15f)
			j->first.setTextureRect(sf::IntRect((2048 * 2), 0, 2048, 2048));
		if(j->second > 1.4f)
			j->first.setColor(sf::Color(j->first.getColor().r, j->first.getColor().g, j->first.getColor().b, 255 / 2));
		
		if (j->second > 2.f)
			j = deathShadows.erase(j);
		else
			j++;	
	}

	//update enemy bullets
	auto enBullet = enemyBullets.begin();
	while (enBullet != enemyBullets.end()) {
		enBullet->update(dt);
		if (ifOutsizeView(*enBullet, view))
			enBullet = enemyBullets.erase(enBullet);
		else
			enBullet++;
	}
}

void EnemyManager::moveEnemy(float dt, sf::Vector2f playerPos, Enemy & e)
{
	float dx = playerPos.x - e.getPosition().x;
	float dy = playerPos.y - e.getPosition().y;
	float value = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
	if (value <= minDistBtPlayerEnemy) {
		e.inNearestPoint = true;
		return;
	}
	e.inNearestPoint = false;
	sf::Vector2f normDir = sf::Vector2f((dx / value), (dy / value));
	e.move(normDir*moveSpeed*dt);
}

void EnemyManager::animateWalk(float dt, Enemy &e)
{
	if (e.inNearestPoint && e.enemyType != 2) {
		e.currWalkTex = 0;
		e.sprite.setTextureRect(sf::IntRect(e.currWalkTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		e.sprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if (e.flipped)
			e.sprite.setScale(-scaleSize.x, scaleSize.y);
		else
			e.sprite.setScale(scaleSize);
		return;
	}
		
	e.walkAnimTimer += dt;
	if (e.walkAnimTimer >= e.walkAnimTime) {
		e.walkAnimTimer = 0;

		e.currWalkTex++;
		if (e.currWalkTex == e.maxWalkTex - 1)
			e.currWalkTex = 0;
		e.sprite.setTextureRect(sf::IntRect(e.currWalkTex*subTexRectSize, 0, subTexRectSize, subTexRectSize));
		e.sprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
		if (e.flipped)
			e.sprite.setScale(-scaleSize.x, scaleSize.y);
		else
			e.sprite.setScale(scaleSize);
	}
	
}

bool EnemyManager::ifOutsizeView(Bullet b, Camera view)
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

void EnemyManager::resetStates(void)
{
	spawnnigTimer = 0.f;
	reloadingTimer = 0.f;
	spawnTime = 1.f;
	maxEnemySpawnd = false;

	deathShadows.clear();
	killScores.clear();
	for (int i = 0; i < 4; i++)
		killScores.push_back(0);
	enemies.clear();
	enemyBullets.clear();
}

void EnemyManager::shoot(sf::Vector2f playerPos, Enemy enemy, float dt)
{
	reloadingTimer += dt;
	if (reloadingTimer >= enemyReloadTime) {
		reloadingTimer = 0;
		enemyReloadTime = 1.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.5 - 1.5)));
		//bullet fire for particular enemy
		Bullet *b = new Bullet(enemy.getPosition(), 2);
		float dx = playerPos.x - enemy.getPosition().x;
		float dy = playerPos.y - enemy.getPosition().y;
		float angle = std::atan2(dy, dx);
		b->setFireAngle(angle);
		enemyBullets.push_back(*b);
	}
}

void EnemyManager::drawEnemies(sf::RenderWindow & window)
{
	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		window.draw(i->shadowSprite);
	}

	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		window.draw(i->sprite);
	}

	for (auto i = deathShadows.begin(); i != deathShadows.end(); i++) {
		window.draw(i->first);
	}

	for (auto i = enemyBullets.begin(); i != enemyBullets.end(); i++) {
		window.draw(i->sprite);
	}
}
