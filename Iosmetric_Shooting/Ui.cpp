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
		gunTimerBarScale = sf::Vector2f(0.5, 0.5);
		chadMeterScale = sf::Vector2f(0.5, 0.4);
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
		gunTimerBarScale = sf::Vector2f(0.6, 0.6);
		chadMeterScale = sf::Vector2f(0.5, 0.5);
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

	//gun timer bar
	rifelTimeBarTex.loadFromFile("Assets/Ui/rifel_outline.png");
	rifelTimeBar.setTexture(rifelTimeBarTex);
	rifelTimeBar.setScale(gunTimerBarScale);
	shotgunTimeBarTex.loadFromFile("Assets/Ui/shotgun_outline.png");
	shotgunTimeBar.setTexture(shotgunTimeBarTex);
	shotgunTimeBar.setScale(gunTimerBarScale);
	timeBarInlineTex.loadFromFile("Assets/Ui/gunTimer_inline.png");
	timeBarInline.setTexture(timeBarInlineTex);
	timeBarInline.setScale(gunTimerBarScale);
	timeBarTex.loadFromFile("Assets/Ui/gunTimer_bar.png");
	timeBar.setTexture(timeBarTex);
	timeBar.setScale(gunTimerBarScale);

	//chad meter stuffs
	chadMeterOutlineTex.loadFromFile("Assets/Ui/chad_meter_outline.png");
	chadMeterOut.setTexture(chadMeterOutlineTex);
	chadMeterOut.setScale(chadMeterScale);
	chadMeterOutlineOnTex.loadFromFile("Assets/Ui/chad_meter_outline_on.png");
	chadMeterOutOn.setTexture(chadMeterOutlineOnTex);
	chadMeterOutOn.setScale(chadMeterScale);
	chadMeterInline = timeBarInline;
	chadMeterInline.setScale(chadMeterScale);
	chadMeterInline.setRotation(90.f);
	chadMeter = timeBar;
	chadMeter.setScale(chadMeterScale);
	chadMeter.setRotation(-90.f);

	//score things
	newHighScoreTex.loadFromFile("Assets/Ui/newHighScore.png");
	newHighScore.setTexture(newHighScoreTex);
	newHighScore.setScale(0.6, 0.6);
	newHighScore.setRotation(-31);

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

	for (int i = 0; i < 6; i++) {
		scoreTexts[i].setFont(gravePartyFont);
		scoreTexts[i].setFillColor(sf::Color(0, 0, 0, 255));
		scoreTexts[i].setCharacterSize(50);
	}

	pauseText.setFont(gravePartyFont);
	pauseText.setCharacterSize(200);
	pauseText.setFillColor(sf::Color(72, 37, 55, 255));
	pauseText.setString("PAUSED");
	pauseText.setPosition(windowSize.x / 2 - pauseText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);

	toggleChadModeText.setFont(gravePartyFont);
	toggleChadModeText.setFillColor(sf::Color(72, 37, 55, 255));
	toggleChadModeText.setString("PRESS 'E' TO TURN ON CHAD MODE");
	toggleChadModeText.setCharacterSize(70);


	//loading sounds
	buttonActiveBuffer.loadFromFile("Assets/Sounds/Ui/menu_active.wav");
	buttonActive.setBuffer(buttonActiveBuffer);

	buttonSelectBuffer.loadFromFile("Assets/Sounds/Ui/menu_select.wav");
	buttonSelect.setBuffer(buttonSelectBuffer);

	std::string bgMusicFilename = "Assets/Sounds/Background_music/bg_music_";
	for (int i = 0; i < 5; i++) {
		bgMusicBuf[i].loadFromFile(bgMusicFilename + std::to_string(i + 1) + ".wav");
		bgMusic[i].setBuffer(bgMusicBuf[i]);
		if (i > 0)
			bgMusic[i].setVolume(bgMusicVolume - 20);
		else
			bgMusic[i].setVolume(bgMusicVolume);
	}

	gigaChadSoundBuf.loadFromFile("Assets/Sounds/Background_music/giga_chad_2.wav");
	gigaChadSound.setBuffer(gigaChadSoundBuf);

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
	if (bgMusic[0].getStatus() != sf::Sound::Playing) {
		bgMusic[musicType].stop();
		bgMusic[0].play();
	}
		
	if (ifMouseIntersects(mousePos, playButton.getPosition(), 
		sf::Vector2f(playButton.getGlobalBounds().width, playButton.getGlobalBounds().height), 0)) {
		
		playButton.setScale(playButtonScale.x + 0.2, playButtonScale.y + 0.2);
		playButton.setPosition(playButtonPos.x - 20, playButtonPos.y - 12);

		if (mousePressed) {
			buttonSelect.play();
			gameState = 1;	//change to char select 
		}
		
	}
	else {
		playButton.setPosition(playButtonPos);
		playButton.setScale(playButtonScale);
	}
		
}

void Ui::updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed)
{
	if (ifMouseIntersects(mousePos, startButton.getPosition(), 
		sf::Vector2f(startButton.getGlobalBounds().width, startButton.getGlobalBounds().height), 1)) {

		startButton.setScale(startButtonScale.x + 0.2, startButtonScale.x + 0.2);
		startButton.setPosition(startButtonPos.x - 20, startButtonPos.y - 12);
		if (soundException1) {
			soundException1 = false;
			buttonActive.play();
		}

		if (mousePressed) {
			buttonSelect.play();
			gameState = 2;	//change to howto state
		}
	}
	else {
		startButton.setPosition(startButtonPos);
		startButton.setScale(startButtonScale);
		soundException1 = true;
	}

	if (ifMouseIntersects(mousePos, arrow.getPosition(),
		sf::Vector2f(arrow.getGlobalBounds().width, arrow.getGlobalBounds().height), 2)) {

		arrow.setScale(0.6, 0.6);
		arrow.setPosition(arrowPos.x - 10, arrowPos.y - 6);
		if (soundException2) {
			soundException2 = false;
			buttonActive.play();
		}

		if (mousePressed) {
			mousePressed = false;
			buttonSelect.play();
			playerType += 1;
			if (playerType > 2)
				playerType = 0;
		}
	}
	else {
		arrow.setPosition(arrowPos);
		arrow.setScale(0.5, 0.5);
		soundException2 = true;
	}
}

void Ui::updateHowToState(sf::Vector2f mousePos, bool mousePressed)
{
	if (ifMouseIntersects(mousePos, noWayOut.getPosition(),
		sf::Vector2f(noWayOut.getGlobalBounds().width, noWayOut.getGlobalBounds().height),3)) {

		noWayOut.setScale(noWayOutScale.x + 0.1, noWayOutScale.y + 0.1);
		noWayOut.setPosition(noWayOutPos.x - 16, noWayOutPos.y - 8);

		if (mousePressed) {
			buttonSelect.play();
			gameState = 3;
		}
	}
	else {
		noWayOut.setScale(noWayOutScale);
		noWayOut.setPosition(noWayOutPos);
	}
}

void Ui::updateCountDown(float dt)
{
	/*if (bgMusic[0].getStatus() == sf::Sound::Playing) {
		if (bgMusic[0].getVolume() > 0)
			bgMusic[0].setVolume(bgMusic[0].getVolume()-0.18);
		if (static_cast<int>(bgMusic[0].getVolume()) <= 0) {
			bgMusic[0].stop();
			bgMusicPlaying = false;
			bgMusic[0].setVolume(bgMusicVolume);
		}
	}*/
	fadeOutSound(bgMusic[0], 0.18);
	if(!bgMusicPlaying && bgMusic[0].getStatus() != sf::Sound::Playing){
		musicType = std::rand() % 4 + 1;
		bgMusic[musicType].play();
		bgMusicPlaying = true;
	}

	countDownTimer += dt;

	if (countDownTimer > countDownInterval) {
		countDownTimer = 0;

		if (countNum == -1) {
			gameState = 4;	//change to play state
			return;
		}
		buttonActive.play();
		countdownText.setString(std::to_string(countNum));
		if (countNum == 0) {
			buttonSelect.play();
			countdownText.setString("GO");
		}
		countdownText.setPosition(windowSize.x / 2 - countdownText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);
		countNum -= 1;
	}
}

void Ui::updatePlayState(sf::Vector2f viewSize, sf::Vector2f viewCenter, int playerHealth, float remainingGunTime, int killsLeftForChadMode, bool chadMode)
{
	//std::cout << killsLeftForChadMode << "\n";
	//offset for ui shake
	float offset = 3 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (8 - 3)));
	if (killsLeftForChadMode > 0)
		offset = 0;
	float direction = rand() % 2;
	offset = ((direction == 0) ? offset : -offset);

	//music things
	if (bgMusic[musicType].getStatus() == sf::Sound::Stopped && !chadMode && gigaChadSound.getStatus() == sf::Sound::Stopped) {
		musicType = std::rand() % 4 + 1;
		bgMusic[musicType].play();
		bgMusicPlaying = true;
	}
	if (chadMode && gigaChadSound.getStatus() != sf::Sound::Playing) {
		//stop the current playing background music
		/*if (bgMusic[musicType].getStatus() == sf::Sound::Playing) {
			if (bgMusic[musicType].getVolume() > 0)
				bgMusic[musicType].setVolume(bgMusic[musicType].getVolume() - 0.2);
			if (static_cast<int>(bgMusic[musicType].getVolume()) <= 0) {
				bgMusic[musicType].stop();
				bgMusicPlaying = false;
				bgMusic[musicType].setVolume(bgMusicVolume);
			}
		}*/
		fadeOutSound(bgMusic[musicType], 0.2);
		if(bgMusic[musicType].getVolume() <= 20) {	//when background music have stopped play chad music
			bgMusic[musicType].stop();
			gigaChadSound.setVolume(100);
			gigaChadSound.play();
		}
	}
	if (gigaChadSound.getStatus() == sf::Sound::Playing && !chadMode) {
		fadeOutSound(gigaChadSound, 0.1);
	}

	//player health bar and gun time bar updates
	if (playerHealth >= 0) {
		float healthBarFactor = healthStuffScale.x / 5;
		float reduceScale = healthBarFactor * ((100 - playerHealth) / 20);
		healthBar.setScale(healthStuffScale.x - reduceScale, healthStuffScale.y);
	}
	if (remainingGunTime >= 0) {
		float timerbarFactor = gunTimerBarScale.x / 10;
		float reduceScale = timerbarFactor * ((10 - remainingGunTime));
		timeBar.setScale(gunTimerBarScale.x - reduceScale, gunTimerBarScale.y);
	}
	
	float x = viewCenter.x - viewSize.x / 2 + healthBarOutline.getGlobalBounds().width / 4;
	float y = viewCenter.y - viewSize.y / 2 + healthBarOutline.getGlobalBounds().height / 2;
	healthBarOutline.setPosition(x + offset,y + offset);
	healthBarInline.setPosition(x + 12 + offset, y + 8 + offset);
	healthBar.setPosition(x + 12 + offset, y + 8 + offset);
	if (this->windowSize.x <= 1366 && this->windowSize.y <= 768) {
		heart.setPosition(x - 30 + offset, y - 6 + offset);
		timeBarInline.setPosition(x + 600 + 100 + offset, y + 10 + offset);
		timeBar.setPosition(x + 600 + 100 + offset, y + 10 + offset);
	}
	else {
		heart.setPosition(x - 38 + offset, y - 10 + offset);
		timeBarInline.setPosition(x + 600 + 120 + offset, y + 10 + offset);
		timeBar.setPosition(x + 600 + 120 + offset, y + 10 + offset);
	}
		
	rifelTimeBar.setPosition(x + 600 + offset, y + offset);
	shotgunTimeBar.setPosition(x + 600 + offset, y + offset);

	//updating chad meter
	x = viewCenter.x + viewSize.x / 2 - chadMeterOut.getGlobalBounds().width;
	if (chadMode) {
		chadMeterOutOn.setPosition(x - 15 + offset, y - 20 + offset);
	}
	chadMeterOut.setPosition(x - 15 + offset, y - 20 + offset);
	chadMeterInline.setPosition(x + 70 + offset, y + 80 + offset);
	float chadMeterIncreaseFactor = chadMeterScale.x / chadModeKillsRequired;	//for 20 kills
	float chadMeterCurrScale = (chadModeKillsRequired - killsLeftForChadMode) * chadMeterIncreaseFactor;
	chadMeter.setScale(chadMeterCurrScale, chadMeterScale.y);
	chadMeter.setPosition(x + 25 + offset, y + 375 + offset);

	//text for chad mode toggle
	x = viewCenter.x - toggleChadModeText.getGlobalBounds().width / 2;
	y = viewCenter.y + viewSize.y / 2 - toggleChadModeText.getGlobalBounds().height * 3.5;
	toggleChadModeText.setPosition(x, y);

	//pause text position
	pauseText.setPosition(sf::Vector2f(viewCenter.x - pauseText.getGlobalBounds().width / 2,
		viewCenter.y - pauseText.getGlobalBounds().height));
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

	std::ifstream highScoreFile("Assets/User_flies/score.txt");
	std::string scoreInFile;
	highScoreFile >> scoreInFile;
	highScoreFile.close();
	int highestScore = std::atoi(scoreInFile.c_str());
	if (totalScore > highestScore) {
		newHighScoreAchieved = true;
		newHighScore.setPosition(x - 440, y - 50);
		highestScore = totalScore;
		std::ofstream highScoreFile("Assets/User_flies/score.txt");
		highScoreFile << std::to_string(highestScore);
	}

	scoreTexts[5].setString(std::to_string(highestScore));
	scoreTexts[5].setPosition(x + scoreUi.getGlobalBounds().width / 2, y + 360);

	gotoMenuButtonPos = sf::Vector2f(x + 250, y + 520);
	gotoMenuButton.setPosition(gotoMenuButtonPos);

	scoresLoaded = true;
}

bool Ui::updateScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, sf::Vector2f mousePos, bool mousePressed)
{
	/*if (bgMusic[musicType].getStatus() == sf::Sound::Playing) {
		if (bgMusic[musicType].getVolume() > 0)
			bgMusic[musicType].setVolume(bgMusic[musicType].getVolume() - 0.2);
		if (static_cast<int>(bgMusic[musicType].getVolume()) <= 0) {
			bgMusic[musicType].stop();
			bgMusicPlaying = false;
			bgMusic[musicType].setVolume(bgMusicVolume);
		}
	}*/
	fadeOutSound(bgMusic[musicType], 0.2);

	if (ifMouseIntersects(mousePos, gotoMenuButton.getPosition(),
		sf::Vector2f(gotoMenuButton.getGlobalBounds().width, gotoMenuButton.getGlobalBounds().height), 4)) {

		gotoMenuButton.setScale(gotoMenuButtonScale.x + 0.2, gotoMenuButtonScale.y + 0.2);
		gotoMenuButton.setPosition(gotoMenuButtonPos.x - 16, gotoMenuButtonPos.y - 8);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonSelect.play();
			return true;
		}
	}
	else {
		gotoMenuButton.setScale(gotoMenuButtonScale);
		gotoMenuButton.setPosition(gotoMenuButtonPos);
		return false;
	}
}

bool Ui::ifMouseIntersects(sf::Vector2f mousePos, sf::Vector2f buttonPos, sf::Vector2f buttonSize, int number)
{
	if (mousePos.x > buttonPos.x && mousePos.x <  buttonPos.x + buttonSize.x &&
		mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + buttonSize.y) {
		if(playButtonActive && (number!=1 && number!=2))
		{
			buttonActive.play();
		}
		playButtonActive = false;
		return true;
	}
	else {
		playButtonActive = true;
		return false;
	}
}

void Ui::fadeOutSound(sf::Sound &sound, float volumeDownFactor)
{
	if (sound.getStatus() == sf::Sound::Playing) {
		if (sound.getVolume() > 0)
			sound.setVolume(sound.getVolume() - volumeDownFactor);
		if (static_cast<int>(sound.getVolume()) <= 0) {
			sound.stop();
			bgMusicPlaying = false;
			sound.setVolume(bgMusicVolume);
		}
	}
}

void Ui::resetStates(void)
{
	playerType = 0;
	scoresLoaded = false;
	countNum = 3;
	bgMusicPlaying = false;
	newHighScoreAchieved = false;
	countdownText.setString("GET  READY");
	countdownText.setPosition(windowSize.x / 2 - countdownText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);
	chadMeter.setScale(chadMeterScale);
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

void Ui::renderPlayState(sf::RenderWindow& window, bool showTimeBar, int timebarType, bool chadMode, int killsLeftForChadMode)
{
	window.draw(healthBarInline);
	window.draw(healthBar);
	window.draw(healthBarOutline);
	window.draw(heart);

	window.draw(chadMeterInline);
	window.draw(chadMeter);
	if (chadMode)
		window.draw(chadMeterOutOn);
	else
		window.draw(chadMeterOut);

	if (killsLeftForChadMode <= 0 && !chadMode)
		window.draw(toggleChadModeText);

	if (showTimeBar) {
		window.draw(timeBarInline);
		window.draw(timeBar);
		if (timebarType == 0)
			window.draw(rifelTimeBar);
		else
			window.draw(shotgunTimeBar);
	}
}

void Ui::renderScoreState(sf::RenderWindow& window)
{
	window.draw(scoreUi);
	if (newHighScoreAchieved)
		window.draw(newHighScore);
	for (int i = 0; i < 6; i++)
		window.draw(scoreTexts[i]);
	window.draw(gotoMenuButton);
}

void Ui::renderPauseState(sf::RenderWindow& window)
{
	window.draw(pauseText);
}
