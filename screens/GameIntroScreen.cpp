#include "GameIntroScreen.h"

DIALOG gameIntroDialog = { d_textbox_proc, 0, 0,  0,  0,  0,  0, 0, 0, 0,   0, NULL, NULL, NULL };

GameIntroScreen::GameIntroScreen(GameState* gameState, ConfigManager* configManager) {
	this->gameState = gameState;
	this->configManager = configManager;
	this->bannerBitmap = load_bitmap("assets/ui-elem/banner.bmp", NULL);
	 

	this->introText = (char*)"Welcome to Game Development Trivia! This game is based on questions from the back exercises of the book Game Programming All in One by Jonathan S. Harbour. \n\nYou can choose the chapters you want the questions in the quiz to be from in the next screen. \n\nGame will prepare a quiz of 10 questions for you and you have to choose the most accurate option for each question by clicking on it. \n\nGame will keep track of your score and display the results at the end of the game. I hope you enjoy it!";
}

void GameIntroScreen::drawIntroScreenAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, FONT* headingFont, FONT* textFont) {

	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);



	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.5, "WELCOME!", COLOR_TEXT, -1);
		introPlayer = Utility::draw_wrapping_text(buffer, textFont, &gameIntroDialog, this->introText, SCREEN_W*0.2, SCREEN_H * 0.32, SCREEN_W*0.6, SCREEN_H*0.4, 10);
		skipIntroButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2.7, SCREEN_H * 0.78, .37, "DON'T SHOW AGAIN", neverShowAgainButtonColor, -1);
		nextButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 1.35, SCREEN_H * 0.78, .37, "NEXT", nextButtonColor, -1);
	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.75, "WELCOME!", COLOR_TEXT, -1);
		introPlayer = Utility::draw_wrapping_text(buffer, textFont, &gameIntroDialog, this->introText, SCREEN_W * 0.2, SCREEN_H * 0.3, SCREEN_W * 0.6, SCREEN_H * 0.4, 10);
		skipIntroButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2.7, SCREEN_H * 0.78, 0.5, "DON'T SHOW AGAIN", neverShowAgainButtonColor, -1);
		nextButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 1.44, SCREEN_H * 0.78, 0.5, "NEXT", nextButtonColor, -1);
	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.23, 1, "WELCOME!", COLOR_TEXT, -1);
		introPlayer = Utility::draw_wrapping_text(buffer, textFont, &gameIntroDialog, this->introText, SCREEN_W * 0.25, SCREEN_H * 0.3, SCREEN_W * 0.5, SCREEN_H * 0.4, 10);
		skipIntroButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2.5, SCREEN_H * 0.75, .6, "DON'T SHOW AGAIN", neverShowAgainButtonColor, -1);
		nextButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 1.6, SCREEN_H * 0.75, .6, "NEXT", nextButtonColor, -1);
	}


	this->nextButtonColor = OPTION_COLOR;
	this->neverShowAgainButtonColor = OPTION_COLOR;

	// handle clicks on the skip intro button
	if (Utility::mouseInTheBoundingBox(skipIntroButton)) {
		gameState->mouseHover = 1;
		this->neverShowAgainButtonColor = OPTION_COLOR_HOVERED;

		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_HELP;
			gameState->skip_intro = 1;
			configManager->save_config(CONFIG_FILENAME, gameState);
			gameState->pendingMouseClick = 0;
			gameState->mouseHover = 0;

			if (introPlayer) { 
				shutdown_dialog(introPlayer);
				introPlayer = NULL;
			}
			rest(300);
			return;
		}
	}
	// handle clicks on the next button
	else if (Utility::mouseInTheBoundingBox(nextButton)) {
		gameState->mouseHover = 1;
		this->nextButtonColor = OPTION_COLOR_HOVERED;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_HELP;
			gameState->mouseHover = 0; 
			gameState->pendingMouseClick = 0;

			if (introPlayer) { 
				shutdown_dialog(introPlayer);
				introPlayer = NULL;
			}

			rest(300);
			return;
		}
	}
	else {
		gameState->mouseHover = 0;
	}


	 
}