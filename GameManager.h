#pragma once
#include "screens/GameScreen.h"
#include "Constants.h" 
#include "screens/MainMenu.h"
#include "screens/CreditsScreen.h"
#include "screens/SettingsMenu.h"
#include "screens/GFXSettingsMenu.h"
#include "screens/SoundSettingsMenu.h"
#include "screens/GameIntroScreen.h"
#include "screens/GameHelpScreen.h"
#include "SoundManager.h"


#include "Constants.h"
#include "ConfigManager.h" 

#include <allegro.h>

class GameManager
{
private:

	SoundManager* soundManager;

	MainMenu* mainMenu;
	CreditsScreen* creditsScreen;
	SettingsMenu* settingsMenu;
	GFXSettingsMenu* gfxSettingsMenu;
	SoundSettingsMenu* soundSettingsMenu;
	GameIntroScreen* gameIntroScreen;
	GameHelpScreen* gameHelpScreen;
	GameScreen* gameScreen;
	

	BITMAP* cursor;
	BITMAP* cursorHand;
	GameState* gameState; 

	BITMAP* loadingBanner;
	BITMAP* menuBackground;
	BITMAP* menuBanner;

	FONT* headingFont;
	FONT* textFont;

	int pointerAsCursor;
	int muteActionTriggered;
	int musicPlaying = 1;
	int soundVol = 0;

	void showLoadingScreen();
	void renderFrameToBuffer(BITMAP* buffer);

public:
	/**
	 * @brief Construct a new Game Manager object
	 *
	 * @param gamseState Pointer to the struct used for storing game struct
	 */
	GameManager(GameState* gamseState); 
	~GameManager();

	/**
	 * @brief Initializes the game by performing required setup like initializing allegro etc.
	 *
	 * @return int Zero if initialization is successfull
	 */
	int init(void);
	/**
	 * @brief Exits the game
	 *
	 */
	void exit(void);
	/**
	 * @brief Game loop
	 *
	 */
	void runGameLoop(void);
};

