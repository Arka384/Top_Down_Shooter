#pragma once
#include "Bullet.h"

class Ui
{
private:
	sf::Vector2f windowSize;
	int gameState = 0;	
	//0 -> main menu
	//1 -> character select
	//2 -> count down
	//3 -> play 
	//4 -> pause
	//5 -> game over

	//textures
	sf::Texture menuBackgroundTex, blankBackgroundTex, playButtonTex, arrowTex, startButtonTex;
	//sprites
	sf::Sprite menuBackground, blankBackground, playButton, arrow, startButton;
	//fonts
	sf::Font gravePartyFont;
	//texts
	sf::Text titleText, characterSelectText , countdownText;

	sf::Vector2f playButtonPos, startButtonPos, arrowPos;
	float countDownInterval = 1.f, countDownTimer = 0.f;
	int countNum = 3;

public:
	int playerType = 0;

	Ui(sf::Vector2f windowSize);
	void setGameState(int state);
	int getGameState(void);
	void updateMainMenu(sf::Vector2f mousePos, bool mousePressed);
	void updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed);
	void updateCountDown(float dt);

	void renderMainMenu(sf::RenderWindow& window);
	void renderCharacterSelect(sf::RenderWindow& window);
	void renderCountDown(sf::RenderWindow& window);
};

