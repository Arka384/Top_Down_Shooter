#pragma once
#include "Bullet.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

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
	//5 -> score
	//6 -> game over

	//textures
	sf::Texture menuBackgroundTex, blankBackgroundTex, playButtonTex, arrowTex, startButtonTex;
	sf::Texture healthOutTex, healthInTex, healthTex, heartTex;
	sf::Texture howToTex, noWayOutTex, scoreUiTex, gotoMenuButtonTex;
	sf::Texture rifelTimeBarTex, shotgunTimeBarTex, timeBarInlineTex, timeBarTex;
	sf::Texture newHighScoreTex;
	//sprites
	sf::Sprite menuBackground, blankBackground, playButton, arrow, startButton;
	sf::Sprite healthBarOutline, healthBarInline, healthBar, heart;
	sf::Sprite howToInfo, noWayOut, scoreUi, gotoMenuButton;
	sf::Sprite rifelTimeBar, shotgunTimeBar, timeBarInline, timeBar;
	sf::Sprite newHighScore;

	//fonts
	sf::Font gravePartyFont;
	//texts
	sf::Text titleText, characterSelectText , countdownText, scoreTexts[6];
	//sounds
	sf::SoundBuffer buttonActiveBuffer, buttonSelectBuffer;
	sf::SoundBuffer bgMusicBuf[5];
	sf::Sound buttonActive, buttonSelect;
	sf::Sound bgMusic[5];

	sf::Vector2f playButtonPos, startButtonPos, arrowPos, noWayOutPos, gotoMenuButtonPos;
	sf::Vector2f playButtonScale, startButtonScale, healthStuffScale, noWayOutScale, gotoMenuButtonScale;
	sf::Vector2f gunTimerBarScale;
	float countDownInterval = 1.2f, countDownTimer = 0.f;
	int countNum = 3;

	bool playButtonActive = true;
	bool soundException1 = true, soundException2 = true;
	bool bgMusicPlaying = false;
	bool newHighScoreAchieved = false;
	int musicType = 1;
	int bgMusicVolume = 60;
	

public:
	int playerType = 0;
	bool scoresLoaded = false;

	Ui(sf::Vector2f windowSize);
	void setGameState(int state);
	int getGameState(void);
	void updateMainMenu(sf::Vector2f mousePos, bool mousePressed);
	void updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed);
	void updateHowToState(sf::Vector2f mousePos, bool mousePressed);
	void updateCountDown(float dt);
	void updatePlayState(sf::Vector2f viewSize, sf::Vector2f viewCenter, int playerHealth, float remainingGunTime);
	void loadScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, std::vector<int> scores);
	bool updateScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, sf::Vector2f mousePos, bool mousePressed);

	bool ifMouseIntersects(sf::Vector2f mousePos, sf::Vector2f buttonPos, sf::Vector2f buttonSize, int number);
	void resetStates(void);

	void renderMainMenu(sf::RenderWindow& window);
	void renderCharacterSelect(sf::RenderWindow& window);
	void renderHowToState(sf::RenderWindow& window);
	void renderCountDown(sf::RenderWindow& window);
	void renderPlayState(sf::RenderWindow& window, bool showTimeBar, int timebarType);
	void renderScoreState(sf::RenderWindow& window);
};

