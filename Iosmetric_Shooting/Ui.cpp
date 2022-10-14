#include "Ui.h"

Ui::Ui(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;

	//resolution management
	std::string menuBackFileName = "Assets/Ui/main_menu_1";
	std::string blankBackFileName = "Assets/Ui/blank_background";
	sf::Vector2f titleTextPosition, charSelectTextPosition;
	float titleTextCharSize, charSelectTextCharSize;
	

	if (windowSize.x <= 1366 && windowSize.y <= 768) {
		menuBackFileName.append("_small.png");
		blankBackFileName.append("_small.png");
		titleTextPosition = sf::Vector2f(200, 100);
		titleTextCharSize = 180;
		playButtonScale = sf::Vector2f(0.6, 0.6);
		charSelectTextPosition = sf::Vector2f(100, 100);
		charSelectTextCharSize = 120;
		startButtonScale = sf::Vector2f(0.6, 0.6);
		healthStuffScale = sf::Vector2f(0.5, 0.4);
	}
	else {
		menuBackFileName.append(".png");
		blankBackFileName.append(".png");
		titleTextPosition = sf::Vector2f(350, 120);
		titleTextCharSize = 250;
		playButtonScale = sf::Vector2f(1, 1);
		charSelectTextPosition = sf::Vector2f(200, 180);
		charSelectTextCharSize = 150;
		startButtonScale = sf::Vector2f(0.8, 0.8);
		healthStuffScale = sf::Vector2f(0.6, 0.4);
	}	

	//loading textures and sprites
	menuBackgroundTex.loadFromFile(menuBackFileName);
	menuBackground.setTexture(menuBackgroundTex);
	menuBackground.setPosition(0, -20);

	playButtonTex.loadFromFile("Assets/Ui/play_button.png");
	playButton.setTexture(playButtonTex);
	playButton.setScale(playButtonScale);
	playButtonPos = sf::Vector2f(windowSize.x / 2 - playButton.getGlobalBounds().width / 2, 
		windowSize.y / 2 + playButton.getGlobalBounds().height/4);
	playButton.setPosition(playButtonPos);

	
	blankBackgroundTex.loadFromFile(blankBackFileName);
	blankBackground.setTexture(blankBackgroundTex);
	blankBackground.setPosition(0, -20);

	arrowTex.loadFromFile("Assets/Ui/arrows.png");
	arrow.setTexture(arrowTex);
	arrow.setScale(0.5, 0.5);
	arrowPos = sf::Vector2f(windowSize.x / 2 - 220, windowSize.y / 2);
	arrow.setPosition(arrowPos);

	startButtonTex.loadFromFile("Assets/Ui/next_button.png");
	startButton.setTexture(startButtonTex);
	startButton.setScale(startButtonScale);
	startButtonPos = sf::Vector2f(windowSize.x / 2 - startButton.getGlobalBounds().width / 2, 
		windowSize.y - startButton.getGlobalBounds().height*2);
	startButton.setPosition(startButtonPos);

	///////////
	//health bar stuffs
	healthOutTex.loadFromFile("Assets/Ui/heathBarOutline.png");
	healthBarOutline.setTexture(healthOutTex);
	healthBarOutline.setScale(healthStuffScale);

	healthInTex.loadFromFile("Assets/Ui/heathBarInline.png");
	healthBarInline.setTexture(healthInTex);
	healthBarInline.setScale(healthStuffScale);

	healthTex.loadFromFile("Assets/Ui/heathBar.png");
	healthBar.setTexture(healthTex);
	healthBar.setScale(healthStuffScale);

	heartTex.loadFromFile("Assets/Ui/heart.png");
	heart.setTexture(heartTex);
	heart.setScale(healthStuffScale.x - 0.08, healthStuffScale.y);


	//loading fonts
	gravePartyFont.loadFromFile("Assets/Fonts/GraveParty.ttf");

	//loading texts
	titleText.setFont(gravePartyFont);
	titleText.setCharacterSize(titleTextCharSize);
	titleText.setFillColor(sf::Color(19, 15, 45, 255));
	titleText.setString("NO WAY OUT!");
	titleText.setPosition(titleTextPosition);
	titleText.setRotation(-31.5 * (180 / 3.1415));

	characterSelectText.setFont(gravePartyFont);
	characterSelectText.setCharacterSize(charSelectTextCharSize);
	characterSelectText.setFillColor(sf::Color(72, 37, 55, 255));
	characterSelectText.setString("SELECT  YOUR  PLAYER");
	characterSelectText.setPosition(charSelectTextPosition);
	characterSelectText.setRotation(-31.5 * (180 / 3.1415));

	countdownText.setFont(gravePartyFont);
	countdownText.setCharacterSize(200);
	countdownText.setFillColor(sf::Color(72, 37, 55, 255));
	countdownText.setString("GET  READY");
	countdownText.setPosition(windowSize.x/2 - countdownText.getGlobalBounds().width/2, windowSize.y / 2 - 220);

}

void Ui::setGameState(int state)
{
	gameState = state;
}

int Ui::getGameState(void)
{
	return gameState;
}

void Ui::updateMainMenu(sf::Vector2f mousePos, bool mousePressed)
{
	float playBW = playButton.getGlobalBounds().width;
	float playBH = playButton.getGlobalBounds().height;

	if (mousePos.x > playButton.getPosition().x && mousePos.x < playButton.getPosition().x + playBW &&
		mousePos.y > playButton.getPosition().y && mousePos.y < playButton.getPosition().y + playBH) {
		
		playButton.setScale(playButtonScale.x + 0.2, playButtonScale.y + 0.2);
		playButton.setPosition(playButtonPos.x - 20, playButtonPos.y - 12);

		if (mousePressed)
			//gameState = 1;	//change to char select 
			gameState = 3;
	}
	else {
		playButton.setPosition(playButtonPos);
		playButton.setScale(playButtonScale);
	}
		
}

void Ui::updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed)
{
	float nextBW = startButton.getGlobalBounds().width;
	float nextBH = startButton.getGlobalBounds().height;
	if (mousePos.x > startButton.getPosition().x && mousePos.x < startButton.getPosition().x + nextBW &&
		mousePos.y > startButton.getPosition().y && mousePos.y < startButton.getPosition().y + nextBH) {

		startButton.setScale(startButtonScale.x + 0.2, startButtonScale.x + 0.2);
		startButton.setPosition(startButtonPos.x - 20, startButtonPos.y - 12);

		if (mousePressed)
			gameState = 2;	//change to countDown state
	}
	else {
		startButton.setPosition(startButtonPos);
		startButton.setScale(startButtonScale);
	}


	float arrowBW = arrow.getGlobalBounds().width;
	float arrowBH = arrow.getGlobalBounds().height;
	if (mousePos.x > arrow.getPosition().x && mousePos.x < arrow.getPosition().x + arrowBW &&
		mousePos.y > arrow.getPosition().y && mousePos.y < arrow.getPosition().y + arrowBH) {

		arrow.setScale(0.6, 0.6);
		arrow.setPosition(arrowPos.x - 10, arrowPos.y - 6);
		if (mousePressed) {
			mousePressed = false;
			playerType += 1;
			if (playerType > 2)
				playerType = 0;
		}
	}
	else {
		arrow.setPosition(arrowPos);
		arrow.setScale(0.5, 0.5);
	}
}

void Ui::updateCountDown(float dt)
{
	countDownTimer += dt;

	if (countDownTimer > countDownInterval) {
		countDownTimer = 0;

		if (countNum == -1) {
			gameState = 3;	//change to play state
			return;
		}

		countdownText.setString(std::to_string(countNum));
		if(countNum == 0)
			countdownText.setString("GO");
		countdownText.setPosition(windowSize.x / 2 - countdownText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);

		countNum -= 1;
	}

}

void Ui::updatePlayState(sf::Vector2f viewSize, sf::Vector2f viewCenter, int playerHealth)
{
	if (playerHealth >= 0) {
		float healthBarFactor = healthStuffScale.x / 5;
		float reduceScale = healthBarFactor * ((100 - playerHealth) / 20);
		healthBar.setScale(healthStuffScale.x - reduceScale, healthStuffScale.y);
	}
	
	float x = viewCenter.x - viewSize.x / 2 + healthBarOutline.getGlobalBounds().width / 4;
	float y = viewCenter.y - viewSize.y / 2 + healthBarOutline.getGlobalBounds().height / 2;
	healthBarOutline.setPosition(x,y);
	healthBarInline.setPosition(x + 12, y + 8);
	healthBar.setPosition(x + 12, y + 8);
	if(this->windowSize.x <= 1366 && this->windowSize.y <=768)
		heart.setPosition(x - 30, y - 6);
	else
		heart.setPosition(x - 38, y - 10);
}


void Ui::renderMainMenu(sf::RenderWindow& window)
{
	window.draw(menuBackground);
	window.draw(playButton);
	window.draw(titleText);
}

void Ui::renderCharacterSelect(sf::RenderWindow& window)
{
	window.draw(blankBackground);
	window.draw(characterSelectText);
	window.draw(startButton);
	window.draw(arrow);
}

void Ui::renderCountDown(sf::RenderWindow& window)
{
	window.draw(countdownText);
}

void Ui::renderPlayState(sf::RenderWindow& window)
{
	window.draw(healthBarInline);
	window.draw(healthBar);
	window.draw(healthBarOutline);
	window.draw(heart);
}
