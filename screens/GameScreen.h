#pragma once
#include "../constants.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>  
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
#define ENEMY_SPAWN_HEIGHT (int)(SCREEN_H * (15.0 / 29))
/**
 * @brief This class contains function related to diplaying the Game Intro screen, handling the events for the screen and
 * managing and appling the Game Intro. 
 * 
 */
class GameScreen
{
private:
	// pointer to the gameState Struct
	GameState* gameState;
	// pointers to the bitmaps
	BITMAP* gameBackground;
	BITMAP* genericBackground; 
	//pointer to the player object
	Player* player; 

	BITMAP* tmpGameScreens[2];
	int currentScreen=0; 
	int screenWrap_x_pending = 0;
	int playerPos = 0; 

	std::vector<Enemy*> enemies;
	 
	int numFrames;  
	// function to display the result banner at the end of the game
	void displayResultsBannerAndHandleInput(BITMAP* buffer, BITMAP* bannerBitmap, FONT* textFont);
	unsigned long timeElasped = 0, startTime = 0;
	  
	// vars to store information regarding the timming of mine bomb and enemy releases
	unsigned long lastEnemyReleaseTime = 0;
	int enemyReleaseDelay = 0;

	// function to check if it is the time for any new releases of enemy entities 
	void triggerReleases();

	long gameOverTime = -1;
	int gameOverDelay = 1000;
	int xOffset = 0, yOffset=0;

	int gameScrollSpeed = 5;



	// bounding boxes for the buttons on the results banner
	BoundingBox restartGameButton;
	BoundingBox exitToMainMenuButton;

	int exitToMainMenuButtonColor, restartGameButtonColor;
	SoundManager* soundManager; 

public:

	/**
	 * @brief Construct a new Game Screen object
	 * 
	 * @param gameState Pointer to the game state struct
	 * @param soundManager Pointer to the sound manager object
	 */
	GameScreen(GameState* gameState, SoundManager* soundManager);
	/**
	 * @brief Destroy the Game Screen object
	 * 
	 */
	~GameScreen();
	/**
	 * @brief Draws the game screen to the bitmap and handles the keyboard input
	 * 
	 * @param buffer Bitmap where the game screen is rendered
	 * @param bannerBitmap Pointer the bitmap for the banner
	 * @param headingFont Font used for the headings
	 * @param textFont Font used for the texts
	 */
	void drawGameScreenAndHandleInput(BITMAP* buffer, BITMAP* bannerBitmap, FONT* headingFont, FONT* textFont);
};

