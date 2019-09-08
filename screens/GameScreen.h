#pragma once
#include "../constants.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../entities/MineBomb.h"
#include "../entities/EnemyShip.h"
#include "../entities/PlayerShip.h"
#include "../entities/Bullet.h"
#include "../entities/Explosion.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../Utility.h"
#include "../Sprite.h"
#include "../SoundManager.h"
#include "../mappy/mappyal.h"
#include <allegro.h>

#define OPTION_COLOR  makecol(76,46,16) 
#define OPTION_COLOR_HOVERED makecol(247, 236, 213)
#define TEMP_SCREEN_W 1280
#define TEMP_SCREEN_H 960

class GameScreen
{
private:
	GameState* gameState;
	BITMAP* gameBackground;
	BITMAP* genericBackground;
	BITMAP* bannerBitmap;
	void displayHealthBarAndScore(BITMAP* buffer, FONT* headingFont);
	 
	Player* player;
	Enemy* enemy;

	BITMAP* tmpGameScreens[2];
	int currentScreen=0; 
	int screenWrap_x_pending = 0;
	int playerPos = 0;

	std::vector<Bullet*> bullets ;
	std::vector<Explosion*> explosions;
	std::vector<MineBomb*> mineBombs; 
	std::vector<EnemyShip*> enemyShips;

	void checkHits(BITMAP* buffer);
	int numFrames; 
	int bulletDamage = 10;
	int mineBombDamage = 30;
	void displayResultsBannerAndHandleInput(BITMAP* buffer, FONT* textFont);
	unsigned long timeElasped = 0, startTime = 0;
	
	unsigned long lastmineReleaseTime = 0;
	int mineReleaseDelay = 0;

	unsigned long lastEnemyReleaseTime = 0;
	int enemyReleaseDelay = 0;
	void triggerReleases();

	long gameOverTime = -1;
	int gameOverDelay = 1000;
	int xOffset = 0, yOffset=0;



	BoundingBox restartGameButton;
	BoundingBox exitToMainMenuButton;

	int exitToMainMenuButtonColor, restartGameButtonColor;
	SoundManager* soundManager;

public:
	GameScreen(GameState* gameState, SoundManager* soundManager);
	~GameScreen();
	void drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont);
};

