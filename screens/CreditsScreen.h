#pragma once
#include "../constants.h"
#include "../Utility.h"
#include <allegro.h>

#define OPTION_COLOR  makecol(76,46,16) 
#define OPTION_COLOR_HOVERED makecol(247, 236, 213)

/**
 * @brief This class contains function related to diplaying then Credits screen and handling the events for it. 
 * 
 */
class CreditsScreen
{
private: 
	GameState* gameState;
	BITMAP* tempScreenBmp; 
	char* credits; 

	BoundingBox backButton;
	int backButtonColor = OPTION_COLOR;
public:
	/**
	 * @brief Construct a new Credits Menu object.
	 * 
	 * @param gameState Pointer to the game state struct that is shared by the entire game.
	 */
	CreditsScreen(GameState* gameState);
	/**
	 * @brief This function draws credits menu on to the buffer passed as an arguement and also handles mouse clicks for the credits menu screen.
	 * 
	 * @param buffer Screen buffer or other buffer where the Credits screen has to be drawn.
	 * @param bannerBitmap Pointer the bitmap for the banner
	 * @param headingFont Pointer to the font used for headings
	 * @param textFont Pointer to the font used for text
	 */
	void drawCreditsScreenAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, BITMAP* bannerBitmap, FONT* headingFont, FONT* textFont);
};

