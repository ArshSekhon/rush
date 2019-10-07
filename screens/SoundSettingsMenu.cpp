#include "SoundSettingsMenu.h"

// constructor
SoundSettingsMenu::SoundSettingsMenu(GameState* gs, ConfigManager* configManager) {
	this->gameState = gs;
	this->configManager = configManager;

	this->bannerBitmap = load_bitmap("assets/ui-elem/Banner.bmp", NULL);
	this->musicVolume = gs->music_volume;
	this->soundVolume = gs->sound_volume;
	this->levels = new const char* [11]{ "0" ,"1","2","3","4","5","6","7","8","9","10"};
	this->soundVolChangeArrows = new BoundingBox[2];;
	this->musicVolChangeArrows = new BoundingBox[2];
}


SoundSettingsMenu::~SoundSettingsMenu() {
	destroy_bitmap(bannerBitmap);
}


void SoundSettingsMenu::drawSoundSettingsMenuAndHandleInput(BITMAP* buffer, FONT* font) {

	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);


	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.25, 0.5, "VOLUME SETTINGS", COLOR_TEXT, -1);

		int arrowLeftX = SCREEN_W / 2;
		int arrowRightX = SCREEN_W / 1.25;

		Utility::textout_magnified(buffer, font, SCREEN_W / 5.2, SCREEN_H * 0.43, 0.4, "SOUND", COLOR_TEXT, -1);
		soundVolChangeArrows[0] = Utility::create_arrow_left(buffer, arrowLeftX, SCREEN_H * 0.44, 15, soundVolChangeArrowsColor);

		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 1.53, SCREEN_H * 0.44, 0.4, levels[soundVolume] , soundVolChangeArrowsColor, -1);
		soundVolChangeArrows[1] = Utility::create_arrow_right(buffer, arrowRightX, SCREEN_H * 0.44, 15, soundVolChangeArrowsColor);

		Utility::textout_magnified(buffer, font, SCREEN_W / 5.2, SCREEN_H * 0.53, 0.4, "MUSIC", COLOR_TEXT, -1);
		musicVolChangeArrows[0] = Utility::create_arrow_left(buffer, arrowLeftX, SCREEN_H * 0.54, 15, musicVolChangeArrowsColor);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 1.53, SCREEN_H * 0.55, 0.4, levels[musicVolume], musicVolChangeArrowsColor, -1);
		musicVolChangeArrows[1] = Utility::create_arrow_right(buffer, arrowRightX, SCREEN_H * 0.54, 15, musicVolChangeArrowsColor);

		backButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 3, SCREEN_H * 0.75, 0.4, "BACK", backButtonColor, -1);
		applyButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, 0.4, "APPLY", applyButtonColor, -1);
	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);


		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.25, 0.75, "VOLUME SETTINGS", COLOR_TEXT, -1);




		int arrowLeftX = SCREEN_W / 1.9;
		int arrowRightX = SCREEN_W / 1.4;

		Utility::textout_magnified(buffer, font, SCREEN_W / 3.5, SCREEN_H * 0.43, .5, "SOUND", COLOR_TEXT, -1);
		soundVolChangeArrows[0] = Utility::create_arrow_left(buffer, arrowLeftX, SCREEN_H * 0.44, 15, soundVolChangeArrowsColor);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 1.6, SCREEN_H * 0.45, .5, levels[soundVolume], soundVolChangeArrowsColor, -1);
		soundVolChangeArrows[1] = Utility::create_arrow_right(buffer, arrowRightX, SCREEN_H * 0.44, 15, soundVolChangeArrowsColor);

		Utility::textout_magnified(buffer, font, SCREEN_W / 3.5, SCREEN_H * 0.53, .5, "MUSIC", COLOR_TEXT, -1);
		musicVolChangeArrows[0] = Utility::create_arrow_left(buffer, arrowLeftX, SCREEN_H * 0.54, 15, musicVolChangeArrowsColor);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 1.6, SCREEN_H * 0.55, .5, levels[musicVolume], musicVolChangeArrowsColor, -1);
		musicVolChangeArrows[1] = Utility::create_arrow_right(buffer, arrowRightX, SCREEN_H * 0.54, 15, musicVolChangeArrowsColor);





		backButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 3, SCREEN_H * 0.75, .5, "BACK", backButtonColor, -1);
		applyButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .5, "APPLY", applyButtonColor, -1);
	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2, SCREEN_H * 0.33, 1, "VOLUME SETTINGS", COLOR_TEXT, -1);





		int arrowLeftX = SCREEN_W / 2;
		int arrowRightX = SCREEN_W / 1.5;

		Utility::textout_magnified(buffer, font, SCREEN_W / 3, SCREEN_H * 0.43, .6, "SOUND", COLOR_TEXT, -1);
		soundVolChangeArrows[0] = Utility::create_arrow_left(buffer, arrowLeftX, SCREEN_H * 0.44, 15, soundVolChangeArrowsColor);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 1.7, SCREEN_H * 0.45, .6, levels[soundVolume], soundVolChangeArrowsColor, -1);
		soundVolChangeArrows[1] = Utility::create_arrow_right(buffer, arrowRightX, SCREEN_H * 0.44, 15, soundVolChangeArrowsColor);

		Utility::textout_magnified(buffer, font, SCREEN_W / 3, SCREEN_H * 0.53, .6, "MUSIC", COLOR_TEXT, -1);
		musicVolChangeArrows[0] = Utility::create_arrow_left(buffer, arrowLeftX, SCREEN_H * 0.54, 15, musicVolChangeArrowsColor);
		Utility::textout_centre_scaled(buffer, font, SCREEN_W / 1.7, SCREEN_H * 0.55, 0.6, levels[musicVolume], musicVolChangeArrowsColor, -1);
		musicVolChangeArrows[1] = Utility::create_arrow_right(buffer, arrowRightX, SCREEN_H * 0.54, 15, musicVolChangeArrowsColor);





		backButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W / 2.5, SCREEN_H * 0.69, .6, "BACK", backButtonColor, -1);
		applyButton = Utility::textout_centre_scaled(buffer, font, SCREEN_W * 1.8 / 3, SCREEN_H * 0.69, .6, "APPLY", applyButtonColor, -1);
	} 



	backButtonColor = OPTION_COLOR;
	applyButtonColor = OPTION_COLOR;

	soundVolChangeArrowsColor = OPTION_COLOR;
	musicVolChangeArrowsColor = OPTION_COLOR;

	// handle clicks on the apply button
	if (Utility::mouseInTheBoundingBox(applyButton)) {
		applyButtonColor = OPTION_COLOR_HOVERED;
		gameState->mouseHover = 1;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			this->changeSoundSettings(musicVolume, soundVolume, this->gameState);
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the back button
	else if (Utility::mouseInTheBoundingBox(backButton)) {
		backButtonColor = OPTION_COLOR_HOVERED;
		gameState->mouseHover = 1;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_SETTINGS;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks for volume arrows for sound
	else if (Utility::mouseInTheBoundingBox(soundVolChangeArrows[0]) || Utility::mouseInTheBoundingBox(soundVolChangeArrows[1])) {
		gameState->mouseHover = 1;
		soundVolChangeArrowsColor = OPTION_COLOR_HOVERED;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			if (Utility::mouseInTheBoundingBox(soundVolChangeArrows[0])) {
				if (soundVolume > 0)
					soundVolume--;
			}
			else if (Utility::mouseInTheBoundingBox(soundVolChangeArrows[1])) {
				if (soundVolume < 10)
					soundVolume++;
			}
			gameState->pendingMouseClick = 0;
			rest(200);
		}
	}
	// handle clicks for volume arrows for music
	else if (Utility::mouseInTheBoundingBox(musicVolChangeArrows[0]) || Utility::mouseInTheBoundingBox(musicVolChangeArrows[1])) {
		gameState->mouseHover = 1;
		musicVolChangeArrowsColor = OPTION_COLOR_HOVERED;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			if (Utility::mouseInTheBoundingBox(musicVolChangeArrows[0])) {
				if (musicVolume > 0)
					musicVolume--;
			}
			else if (Utility::mouseInTheBoundingBox(musicVolChangeArrows[1])) {
				if (musicVolume < 10)
					musicVolume++;
			}
			gameState->pendingMouseClick = 0;
			rest(200);
		}
	}
	else {
		gameState->mouseHover = 0;
	}


}
// this function changes the sound settings and immediately saves the settings to the config file

void SoundSettingsMenu::changeSoundSettings(int musicVol, int soundVol, GameState* gameState) {
	gameState->music_volume = musicVol;
	gameState->sound_volume = soundVol;

	set_volume(gameState->sound_volume * 25.5, gameState->music_volume * 25.5);

	configManager->save_config(CONFIG_FILENAME, gameState);
}