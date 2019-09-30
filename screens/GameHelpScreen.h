#pragma once
#include "../constants.h"
#include  "../ConfigManager.h"

#include "../Utility.h"
#include <allegro.h>

#define OPTION_COLOR  makecol(76,46,16) 
#define OPTION_COLOR_HOVERED makecol(247, 236, 213)
/**
 * @brief This class contains function related to diplaying the Game Intro screen, handling the events for the screen and
 * managing and appling the Game Intro. 
 * 
 */
class GameHelpScreen
{
private: 
	GameState* gameState;
	BITMAP* tempScreenBmp;
	char* introText;
	FONT* bigFont;
	BoundingBox skipIntroButton;
	BoundingBox closeButton;
	ConfigManager* configManager;


	int closeButtonColor = OPTION_COLOR;
	int neverShowAgainButtonColor = OPTION_COLOR;
public:
	/**
	 * 
	 * @brief Construct a new GameIntroScreen object that would be used to show an intro screen when game start.
	 * 
	 * @param gameState Pointer to the game state struct that is shared by the entire game
	 * @param configManager Pointer to the ConfigManager object that would be used to load and save the config related to game intro screen
	 * 
	 */
	GameHelpScreen(GameState* gameState);


	/**
	 * @brief Draws game intro screen on to the buffer passed as an arguement 
	 * and also handles mouse click events for the same.
	 * 
	 * @param buffer Screen buffer or other buffer where the game intro screen screen has to be drawn.
	 * @param bannerBitmap Pointer the bitmap for the banner
	 * @param headingFont Pointer to the font used for headings
	 * @param textFont Pointer to the font used for text
	 * @param buttonText Text to be displayed as close button
	 */
	void drawHelpScreenAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, BITMAP* bannerBitmap, FONT* headingFont, FONT* textFont, char* buttonText);
};

