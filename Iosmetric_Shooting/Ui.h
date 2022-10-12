#pragma once
#include "Map.h"

class Ui
{
private:
	int gameState = 0;	//0 -> main menu
						//1 -> count down
						//2 -> play 
						//3 -> pause
						//4 -> game over
public:
	void setGameState(int state);
	int getGameState(void);


};

