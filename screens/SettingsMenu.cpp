#include "SettingsMenu.h"


SettingsMenu::SettingsMenu(GameState* gameState) { 
	this->gameState = gameState;
}
SettingsMenu::~SettingsMenu() { 
}

void SettingsMenu::drawSettingsMenuAndHandleInput(BITMAP* buffer, BITMAP* bannerBitmap, FONT* font) {

	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);


	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.35, 0.5, "SETTINGS", COLOR_TEXT, -1);
		gfxSettingButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.50, .4, "GRAPHICS SETTINGS", gfxSettingsButtonColor, -1);
		soundSettingButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.59, .4, "SOUND SETTINGS", soundSettingsButtonColor, -1);
		backButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.68, .4, "BACK", backButtonColor, -1);
		 

	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);


		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.35, 0.8, "SETTINGS", COLOR_TEXT, -1);
		gfxSettingButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.49, 0.56, "GRAPHICS SETTINGS", gfxSettingsButtonColor, -1);
		soundSettingButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.56, 0.56, "SOUND SETTINGS", soundSettingsButtonColor, -1);
		backButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.63, 0.56, "BACK", backButtonColor, -1); 


	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.35, 1, "SETTINGS", COLOR_TEXT, -1);
		gfxSettingButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.47, 0.7, "GRAPHICS SETTINGS", gfxSettingsButtonColor, -1);
		soundSettingButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.55, 0.7, "SOUND SETTINGS", soundSettingsButtonColor, -1);
		backButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.63, 0.7, "BACK", backButtonColor, -1);

		 
	}

	// handle clicks on the gfx settings button
	if (Utility::mouseInTheBoundingBox(gfxSettingButton)) {

		this->backButtonColor = OPTION_COLOR;
		this->gfxSettingsButtonColor = OPTION_COLOR_HOVERED;
		this->soundSettingsButtonColor = OPTION_COLOR;

		gameState->mouseHover = 1;

		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_GFX_SETTINGS;
			gameState->pendingMouseClick = 0;
			rest(300); 
		}
	}
	// handle clicks on the sound settings button
	else if (Utility::mouseInTheBoundingBox(soundSettingButton)) {
		gameState->mouseHover = 1;

		this->backButtonColor = OPTION_COLOR;
		this->gfxSettingsButtonColor = OPTION_COLOR;
		this->soundSettingsButtonColor = OPTION_COLOR_HOVERED;

		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_SOUND_SETTINGS;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the back button
	else if (Utility::mouseInTheBoundingBox(backButton)) {
		gameState->mouseHover = 1;
		this->backButtonColor = OPTION_COLOR_HOVERED;
		this->gfxSettingsButtonColor = OPTION_COLOR;
		this->soundSettingsButtonColor = OPTION_COLOR;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_MAIN_MENU;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	else {
		this->backButtonColor = OPTION_COLOR;
		this->gfxSettingsButtonColor = OPTION_COLOR;
		this->soundSettingsButtonColor = OPTION_COLOR;
		gameState->mouseHover = 0;
	}


	 
}