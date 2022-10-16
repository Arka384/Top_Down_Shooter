#include "Ui.h"

Ui::Ui(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;

	//resolution management
	std::string menuBackFileName = "Assets/Ui/main_menu_1";
	std::string blankBackFileName = "Assets/Ui/blank_background";
	std::string howToFileName = "Assets/Ui/how_TO";
	sf::Vector2f titleTextPosition, charSelectTextPosition;
	float titleTextCharSize, charSelectTextCharSize;
	

	if (windowSize.x <= 1366 && windowSize.y <= 768) {
		menuBackFileName.append("_small.png");
		blankBackFileName.append("_small.png");
		howToFileName.append("_small.png");
		titleTextPosition = sf::Vector2f(200, 100);
		titleTextCharSize = 180;
		playButtonScale = sf::Vector2f(0.6, 0.6);
		charSelectTextPosition = sf::Vector2f(100, 100);
		charSelectTextCharSize = 120;
		startButtonScale = sf::Vector2f(0.6, 0.6);
		healthStuffScale = sf::Vector2f(0.5, 0.4);
		noWayOutScale = sf::Vector2f(0.7, 0.7);
		noWayOutPos = sf::Vector2f(windowSize.x - 540, windowSize.y - 260);
		gotoMenuButtonScale = sf::Vector2f(0.8, 0.8);
		gotoMenuButtonPos = sf::Vector2f(windowSize.x / 2 - 55, windowSize.y - 110);
	}
	else {
		menuBackFileName.append(".png");
		blankBackFileName.append(".png");
		howToFileName.append(".png");
		titleTextPosition = sf::Vector2f(350, 120);
		titleTextCharSize = 250;
		playButtonScale = sf::Vector2f(1, 1);
		charSelectTextPosition = sf::Vector2f(200, 180);
		charSelectTextCharSize = 150;
		startButtonScale = sf::Vector2f(0.8, 0.8);
		healthStuffScale = sf::Vector2f(0.6, 0.4);
		noWayOutScale = sf::Vector2f(1, 1);
		noWayOutPos = sf::Vector2f(windowSize.x - 660, windowSize.y - 340);
		gotoMenuButtonScale = sf::Vector2f(1, 1);
		gotoMenuButtonPos = sf::Vector2f(windowSize.x / 2 - 75,	windowSize.y - 280);
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

	howToTex.loadFromFile(howToFileName);
	howToInfo.setTexture(howToTex);
	howToInfo.setPosition(0, -20);

	noWayOutTex.loadFromFile("Assets/Ui/noWayOut.png");
	noWayOut.setTexture(noWayOutTex);
	noWayOut.setScale(noWayOutScale);
	noWayOut.setPosition(noWayOutPos);

	scoreUiTex.loadFromFile("Assets/Ui/kills.png");
	scoreUi.setTexture(scoreUiTex);
	scoreUi.setPosition(windowSize.x / 2 - scoreUi.getGlobalBounds().width / 2, windowSize.y / 2 - scoreUi.getGlobalBounds().height / 2);

	gotoMenuButtonTex.loadFromFile("Assets/Ui/goto_main_menu.png");
	gotoMenuButton.setTexture(gotoMenuButtonTex);
	gotoMenuButton.setScale(gotoMenuButtonScale);
	gotoMenuButton.setPosition(gotoMenuButtonPos);

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

	for (int i = 0; i < 5; i++) {
		scoreTexts[i].setFont(gravePartyFont);
		scoreTexts[i].setFillColor(sf::Color(0, 0, 0, 255));
		scoreTexts[i].setCharacterSize(50);
	}

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
	if (ifMouseIntersects(mousePos, playButton.getPosition(), 
		sf::Vector2f(playButton.getGlobalBounds().width, playButton.getGlobalBounds().height))) {
		
		playButton.setScale(playButtonScale.x + 0.2, playButtonScale.y + 0.2);
		playButton.setPosition(playButtonPos.x - 20, playButtonPos.y - 12);

		if (mousePressed)
			gameState = 1;	//change to char select 
			//gameState = 3;
	}
	else {
		playButton.setPosition(playButtonPos);
		playButton.setScale(playButtonScale);
	}
		
}

void Ui::updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed)
{
	if (ifMouseIntersects(mousePos, startButton.getPosition(), 
		sf::Vector2f(startButton.getGlobalBounds().width, startButton.getGlobalBounds().height))) {

		startButton.setScale(startButtonScale.x + 0.2, startButtonScale.x + 0.2);
		startButton.setPosition(startButtonPos.x - 20, startButtonPos.y - 12);

		if (mousePressed)
			gameState = 2;	//change to countDown state
	}
	else {
		startButton.setPosition(startButtonPos);
		startButton.setScale(startButtonScale);
	}


	if (ifMouseIntersects(mousePos, arrow.getPosition(),
		sf::Vector2f(arrow.getGlobalBounds().width, arrow.getGlobalBounds().height))) {

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

void Ui::updateHowToState(sf::Vector2f mousePos, bool mousePressed)
{
	if (ifMouseIntersects(mousePos, noWayOut.getPosition(),
		sf::Vector2f(noWayOut.getGlobalBounds().width, noWayOut.getGlobalBounds().height))) {

		noWayOut.setScale(noWayOutScale.x + 0.1, noWayOutScale.y + 0.1);
		noWayOut.setPosition(noWayOutPos.x - 16, noWayOutPos.y - 8);

		if (mousePressed)
			gameState = 3;
	}
	else {
		noWayOut.setScale(noWayOutScale);
		noWayOut.setPosition(noWayOutPos);
	}
}

void Ui::updateCountDown(float dt)
{
	countDownTimer += dt;

	if (countDownTimer > countDownInterval) {
		countDownTimer = 0;

		if (countNum == -1) {
			gameState = 4;	//change to play state
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

void Ui::loadScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, std::vector<int> scores)
{
	float x = viewCenter.x - scoreUi.getGlobalBounds().width / 2;
	float y = viewCenter.y - scoreUi.getGlobalBounds().height / 2;
	scoreUi.setPosition(x, y);

	int totalScore = 0;
	for (int i = 0; i < 4; i++) {
		totalScore += scores[i];
		std::string tempScore = std::to_string(scores[i]);
		scoreTexts[i].setString(tempScore);
		scoreTexts[i].setPosition((x+100 + i*130), y + 250);
	}
	std::string tempScore = std::to_string(totalScore);
	scoreTexts[4].setString(tempScore);
	scoreTexts[4].setPosition(x + scoreUi.getGlobalBounds().width / 2, y + 315);
	scoresLoaded = true;
}

void Ui::updateScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, sf::Vector2f mousePos, bool mousePressed)
{
	if (ifMouseIntersects(mousePos, gotoMenuButton.getPosition(),
		sf::Vector2f(gotoMenuButton.getGlobalBounds().width, gotoMenuButton.getGlobalBounds().height))) {

		gotoMenuButton.setScale(gotoMenuButtonScale.x + 0.2, gotoMenuButtonScale.y + 0.2);
		gotoMenuButton.setPosition(gotoMenuButtonPos.x - 16, gotoMenuButtonPos.y - 8);

		if (mousePressed)
			//need to reset everything before changing to menu 
			gameState = 0;
	}
	else {
		gotoMenuButton.setScale(gotoMenuButtonScale);
		gotoMenuButton.setPosition(gotoMenuButtonPos);
	}
}


bool Ui::ifMouseIntersects(sf::Vector2f mousePos, sf::Vector2f buttonPos, sf::Vector2f buttonSize)
{
	if (mousePos.x > buttonPos.x && mousePos.x <  buttonPos.x + buttonSize.x &&
		mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + buttonSize.y)
		return true;
	else
		return false;
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

void Ui::renderHowToState(sf::RenderWindow& window)
{
	window.draw(howToInfo);
	window.draw(noWayOut);
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

void Ui::renderScoreState(sf::RenderWindow& window)
{
	window.draw(scoreUi);
	for (int i = 0; i < 5; i++)
		window.draw(scoreTexts[i]);
	window.draw(gotoMenuButton);
}
