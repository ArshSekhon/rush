#include "MainMenu.h"
#include "../Constants.h"  
#include <allegro.h>
#include "../Utility.h"



MainMenu::MainMenu(GameState* gs, BITMAP* buttonsBitmap, BITMAP* mainMenuBG) { 
	this->gameState = gs;
	this->background = mainMenuBG;
	this->buttonsBitmap = buttonsBitmap;
	 
}

int MainMenu::showMainMenu(BITMAP* buffer) {
	stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);
	//draw buffer to screen and clear buffer

	//draw buttons

	int y_first_button = SCREEN_H * 0.6;
	playButton = draw_button(buffer, buttonsBitmap, SCREEN_W * 0.5, y_first_button, 0, cursorOverPlayButton);
	settingsButton = draw_button(buffer, buttonsBitmap, SCREEN_W * 0.5, y_first_button,1, cursorOverOptionsButton);
	creditsButton = draw_button(buffer, buttonsBitmap, SCREEN_W * 0.5, y_first_button, 2, cursorOverCreditsButton);
	exitButton = draw_button(buffer, buttonsBitmap, SCREEN_W * 0.5, y_first_button, 3, cursorOverExitButton);


	// handle clicks on the start button
	if (Utility::mouseInTheBoundingBox(playButton)) {
		gameState->mouseHover = 1;

		this->cursorOverPlayButton = 1;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 0;

		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {

			if (!gameState->skip_intro)
				gameState->gameScreen = GAME_SCREEN_START;
			else
				gameState->gameScreen = GAME_SCREEN_PLAY;

			//reset the score and current question number 
			gameState->currentScore = 0;
			gameState->health = 100;

			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the settings button
	else if (Utility::mouseInTheBoundingBox(settingsButton)) {
		gameState->mouseHover = 1;

		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 1;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 0;

		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_SETTINGS;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the credits button
	else if (Utility::mouseInTheBoundingBox(creditsButton)) {
		gameState->mouseHover = 1;

		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 1;
		this->cursorOverExitButton = 0;

		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_CREDITS;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the credits button
	else if (Utility::mouseInTheBoundingBox(exitButton)) {
		gameState->mouseHover = 1;


		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 1;


		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
			gameState->exitGame = 1;
			gameState->pendingMouseClick = 0;
		}
	}
	else {
		gameState->mouseHover = 0;
		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 0;
	}


	//mouse coordinates
	//textprintf(buffer, font, 10, 10, -1, "X:%d Y:%d S:%d S:%d C:%d E:%d GS:%d FS:%d", mouse_x, mouse_y, startButton.y, settingsButton.y, creditsButton.y, exitButton.y, gameState->gameScreen, gameState->fullscreen);
	

	return this->gameState->gameScreen;
}

BoundingBox MainMenu::draw_button(BITMAP* buffer,
											BITMAP* sprite, 
											int d_x,
											int d_y,
											int position,
											bool hovered) {

	int buttonH = ((float)sprite->h / 4);
	int buttonW = (sprite->w / 2.0);

	BoundingBox boundingBox = {
		d_x,
		d_y,
		buttonW * SCALING_FACTOR_RELATIVE_TO_1280,
		((float)sprite->h / 4) / (sprite->w / 2.0) * buttonW * SCALING_FACTOR_RELATIVE_TO_1280
	};



	boundingBox.x -= (buttonW * SCALING_FACTOR_RELATIVE_TO_1280) / 2;
	boundingBox.y -= (buttonH * SCALING_FACTOR_RELATIVE_TO_1280) / 2;
	boundingBox.y += boundingBox.h*0.45*position + boundingBox.h * position;

	if (!hovered)
		masked_stretch_blit(sprite,
			buffer, 0, ((float)sprite->h / 4)*position, (sprite->w / 2), (sprite->h / 4),
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);
	else
		masked_stretch_blit(sprite,
			buffer, (sprite->w / 2), ((float)sprite->h / 4) * position, (sprite->w / 2), (sprite->h / 4),
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);


	return boundingBox;

}