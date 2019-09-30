#pragma once 
#include "../Constants.h"
#include <allegro.h>
#define PLAY_BUTTON 1
#define OPTIONS_BUTTON 2
#define CREDITS_BUTTON 3
#define EXIT_BUTTON 4
 
#define MAIN_MENU_BUTTON_SPRITE "assets/backgrounds/mainmenu-bg.bmp"

/**
 * @brief This class contains function related to diplaying the Main Menu and handling the events for it.
 * 
 */
class MainMenu
{
public:

	/**
	 * @brief Construct a new MainMenu object that would be used to create the Main menu
	 * 
	 * @param gs Pointer to the game state struct that is shared by the entire game 
	 * @param buttonsBitmap pointer to the buttons bitmap
	 * @param mainMenuBG pointer to the main menu BG bitmap
	 */
	MainMenu(GameState* gs, BITMAP* buttonsBitmap, BITMAP* mainMenuBG);

	/**
	 * @brief Draws main menu on to the buffer passed as an arguement 
	 * and also handles mouse click events for the same.
	 * 
	 * @param buffer Screen buffer or other buffer where the main menu screen has to be drawn.
	 */
	int showMainMenu(BITMAP* buffer);
private:
	GameState* gameState; 
	BITMAP* buttonsBitmap;

	BITMAP* background;

	BoundingBox  playButton;
	BoundingBox settingsButton;
	BoundingBox creditsButton;
	BoundingBox exitButton;

	bool cursorOverPlayButton = 0;
	bool cursorOverOptionsButton = 0;
	bool cursorOverCreditsButton = 0;
	bool cursorOverExitButton = 0;

	BoundingBox draw_button(BITMAP* buffer,
		BITMAP* sprite, 
		int d_x,
		int d_y,
		int position,
		bool hovered);

};

