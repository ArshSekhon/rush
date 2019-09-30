#pragma once
#include <allegro.h>
#include <winalleg.h> 
#include "../Constants.h"  
#include "../ConfigManager.h"
#include "../Utility.h"

#define OPTION_COLOR  makecol(76,46,16) 
#define OPTION_COLOR_HOVERED makecol(247, 236, 213)
/**
 * @brief This class contains function related to diplaying the Graphics Settings screen, handling the events for the screen and
 * managing and appling the graphic settings. 
 * 
 */
class GFXSettingsMenu
{
public:
	/**
	 * @brief Construct a new GFXSettingsMenu object that would be used to create Graphics menu
	 * 
	 * @param gs Pointer to the game state struct that is shared by the entire game
	 * @param configManager Pointer to the ConfigManager object that would be used by Graphics Menu to load and save the configurations
	 */
	GFXSettingsMenu(GameState* gs, ConfigManager* configManager);
	
	/**
	 * @brief Draws graphics settings menu on to the buffer passed as an arguement 
	 * and also handles mouse clicks for the graphics settings menu. It also works with ConfigManager to load and save Graphics related setting
	 * and apply them to the game when apply button is pressed.
	 * 
	 * @param buffer Screen buffer or other buffer where the Graphic settings screen has to be drawn.
	 * @param bannerBitmap Pointer the bitmap for the banner
	 * @param font Pointer to the font to be used for the text
	 */
	int drawGfxMenuAndHandleInput(BITMAP* buffer, BITMAP* bannerBitmap, FONT* font);

	/**
	 * @brief Destroy the GFXSettingsMenu object and performs the required clean-up.
	 * 
	 */
	~GFXSettingsMenu();
private:
	GameState* gameState;
	ConfigManager* configManager;
	BITMAP* bannerBitmap; 
	BoundingBox backButton;
	BoundingBox applyButton;
	const char** gfxResOptions;
	const char** gfxScreenModeOptions;
	int gfxResolutionMode;
	int gfxScreenMode;

	int backButtonColor = OPTION_COLOR;
	int applyButtonColor = OPTION_COLOR;

	int resolutionChangeArrowsColor;
	int screenModeChangeArrowsColor;


	BoundingBox* resolutionChangeArrows;
	BoundingBox* screenModeChangeArrows;
	void changeGfxMode(BITMAP* buffer, int gfxRes, int screenMode, GameState* gameState);
};

