#include "GameHelpScreen.h"

GameHelpScreen::GameHelpScreen(GameState* gameState) {
	this->gameState = gameState;  
	 

	this->introText = (char*)"Welcome to Game Development Trivia! This game is based on questions from the back exercises of the book Game Programming All in One by Jonathan S. Harbour. \n\nYou can choose the chapters you want the questions in the quiz to be from in the next screen. \n\nGame will prepare a quiz of 10 questions for you and you have to choose the most accurate option for each question by clicking on it. \n\nGame will keep track of your score and display the results at the end of the game. I hope you enjoy it!";
}

void GameHelpScreen::drawHelpScreenAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, BITMAP* bannerBitmap, FONT* headingFont, FONT* textFont, char* buttonText) {

	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		closeButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.8, .3, buttonText, closeButtonColor, -1);
	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		closeButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.78, 0.5, buttonText, closeButtonColor, -1);
	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);
		
		closeButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W /2, SCREEN_H * 0.71, .7, buttonText, closeButtonColor, -1);
	}


	this->closeButtonColor = OPTION_COLOR;
	this->neverShowAgainButtonColor = OPTION_COLOR;
	
	if (Utility::mouseInTheBoundingBox(closeButton)) {
		gameState->mouseHover = 1;
		this->closeButtonColor = OPTION_COLOR_HOVERED;
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_PLAY;
			gameState->mouseHover = 0; 
			gameState->pendingMouseClick = 0;

			rest(300);
			return;
		}
	}
	else {
		gameState->mouseHover = 0;
	}


	 
}