#pragma once
#include "Bullet.h"

class Ui
{
private:
	sf::Vector2f windowSize;
	int gameState = 0;	
	//0 -> main menu
	//1 -> character select
	//2 -> how to
	//3 -> count down
	//4 -> play 
	//5 -> pause
	//6 -> game over

	//textures
	sf::Texture menuBackgroundTex, blankBackgroundTex, playButtonTex, arrowTex, startButtonTex;
	sf::Texture healthOutTex, healthInTex, healthTex, heartTex;
	sf::Texture howToTex, noWayOutTex;
	//sprites
	sf::Sprite menuBackground, blankBackground, playButton, arrow, startButton;
	sf::Sprite healthBarOutline, healthBarInline, healthBar, heart;
	sf::Sprite howToInfo, noWayOut;
	//fonts
	sf::Font gravePartyFont;
	//texts
	sf::Text titleText, characterSelectText , countdownText;

	sf::Vector2f playButtonPos, startButtonPos, arrowPos, noWayOutPos;
	sf::Vector2f playButtonScale, startButtonScale, healthStuffScale, noWayOutScale;
	float countDownInterval = 1.f, countDownTimer = 0.f;
	int countNum = 3;

public:
	int playerType = 0;

	Ui(sf::Vector2f windowSize);
	void setGameState(int state);
	int getGameState(void);
	void updateMainMenu(sf::Vector2f mousePos, bool mousePressed);
	void updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed);
	void updateHowToState(sf::Vector2f mousePos, bool& mousePressed);
	void updateCountDown(float dt);
	void updatePlayState(sf::Vector2f viewSize, sf::Vector2f viewCenter, int playerHealth);
	bool ifMouseIntersects(sf::Vector2f mousePos, sf::Vector2f buttonPos, sf::Vector2f buttonSize);

	void renderMainMenu(sf::RenderWindow& window);
	void renderCharacterSelect(sf::RenderWindow& window);
	void renderHowToState(sf::RenderWindow& window);
	void renderCountDown(sf::RenderWindow& window);
	void renderPlayState(sf::RenderWindow& window);
};

