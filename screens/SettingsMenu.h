#pragma once
#include "..//Constants.h"
#include "..//Utility.h"
#include <allegro.h>

#define OPTION_COLOR  makecol(76,46,16) 
#define OPTION_COLOR_HOVERED makecol(247, 236, 213)

/**
 * @brief This class contains function related to diplaying the Settings Menu and handling the events for it.
 * 
 */
class SettingsMenu
{
private:
	BITMAP* bannerBitmap;
	GameState* gameState;
	BoundingBox soundSettingButton;
	BoundingBox gfxSettingButton;
	BoundingBox backButton;

	int backButtonColor = OPTION_COLOR;
	int gfxSettingsButtonColor = OPTION_COLOR;
	int soundSettingsButtonColor = OPTION_COLOR;

public:
	/**
	 * @brief Construct a new SettingsMenu object that would be used to display the Settings menu
	 * 
	 * @param gs Pointer to the game state struct that is shared by the entire game 
	 */
	SettingsMenu(GameState* gs);
	/**
	 * @brief Destroy the SettingsMenu struct and performs the required clean-up.
	 * 
	 */
	~SettingsMenu();
	
	/**
	 * @brief Draws Settings menu on to the buffer passed as an arguement 
	 * and also handles mouse click events for the same.
	 * 
	 * @param buffer Screen buffer or other buffer where the Settings screen has to be drawn.
	 * @param headingFont Pointer to the font to be used for the settings screen.
	 */
	void drawSettingsMenuAndHandleInput(BITMAP* buffer, FONT* headingFont);
};

