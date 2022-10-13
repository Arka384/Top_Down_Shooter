#include "Ui.h"

Ui::Ui(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;

	//loading textures and sprites
	menuBackgroundTex.loadFromFile("Assets/Ui/main_menu_1.png");
	menuBackground.setTexture(menuBackgroundTex);
	menuBackground.setPosition(0, -20);

	playButtonTex.loadFromFile("Assets/Ui/play_button.png");
	playButton.setTexture(playButtonTex);
	playButtonPos = sf::Vector2f(windowSize.x / 2 - playButton.getGlobalBounds().width / 2, windowSize.y / 2 - 50);
	playButton.setPosition(playButtonPos);

	nextButtonTex.loadFromFile("Assets/Ui/next_button.png");
	nextButton.setTexture(nextButtonTex);
	nextButton.setScale(0.7, 0.7);
	nextButtonPos = sf::Vector2f(windowSize.x / 2 - nextButton.getGlobalBounds().width / 2, windowSize.y - 250);
	nextButton.setPosition(nextButtonPos);


	//loading fonts
	gravePartyFont.loadFromFile("Assets/Fonts/GraveParty.ttf");

	//loading texts
	titleText.setFont(gravePartyFont);
	titleText.setCharacterSize(250);
	titleText.setFillColor(sf::Color(19, 15, 45, 255));
	titleText.setString("NO WAY OUT!");
	titleText.setPosition(350, 120);
	titleText.setRotation(-31.5 * (180 / 3.1415));

	characterSelectText.setFont(gravePartyFont);
	characterSelectText.setCharacterSize(150);
	characterSelectText.setFillColor(sf::Color(72, 37, 55, 255));
	characterSelectText.setString("SELECT  YOUR  PLAYER");
	characterSelectText.setPosition(350, 120);

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
		
		playButton.setScale(1.2, 1.2);
		playButton.setPosition(playButtonPos.x - 20, playButtonPos.y - 12);

		if (mousePressed)
			gameState = 1;	//change to char select 
	}
	else {
		playButton.setPosition(playButtonPos);
		playButton.setScale(1, 1);
	}
		
}

void Ui::updateCharacterSelect(sf::Vector2f mousePos, bool mousePressed)
{
	float nextBW = nextButton.getGlobalBounds().width;
	float nextBH = nextButton.getGlobalBounds().height;

	if (mousePos.x > nextButton.getPosition().x && mousePos.x < nextButton.getPosition().x + nextBW &&
		mousePos.y > nextButton.getPosition().y && mousePos.y < nextButton.getPosition().y + nextBH) {

		nextButton.setScale(0.9, 0.9);
		nextButton.setPosition(nextButtonPos.x - 20, nextButtonPos.y - 12);

		if (mousePressed)
			gameState = 2;	//change to countDown state
	}
	else {
		nextButton.setPosition(nextButtonPos);
		nextButton.setScale(0.7, 0.7);
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

void Ui::renderMainMenu(sf::RenderWindow& window)
{
	window.draw(menuBackground);
	window.draw(playButton);
	window.draw(titleText);
}

void Ui::renderCharacterSelect(sf::RenderWindow& window)
{
	window.draw(characterSelectText);
	window.draw(nextButton);
}

void Ui::renderCountDown(sf::RenderWindow& window)
{
	window.draw(countdownText);
}
