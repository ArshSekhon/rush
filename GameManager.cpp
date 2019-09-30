#include "GameManager.h"

#include <allegro.h> 

ConfigManager configManager;

// close button
volatile int close_button_flag = 0;
void close_button_handler(void)
{
	close_button_flag = 1;
}
END_OF_FUNCTION(close_button_handler)


GameManager::GameManager(GameState* gs) {
	gameState = gs;
	gs->gameScreen = GAME_SCREEN_LOADING;
	gs->gfxSettingsUpdated = 1;

	loadingBanner = NULL;
	cursor = NULL;
	cursorHand = NULL;
	menuBanner = NULL;
	menuBackground = NULL;

	pointerAsCursor = 0;

}
GameManager::~GameManager() {
}

// does the required initialization for the game
int GameManager::init() {
	// initialize allegro
	if (allegro_init() != 0) {
		allegro_message("ERROR: Failed to initialize Allegro.");
		return ERROR_ALLEGRO_INIT;
	}

	set_window_title("Rush: Escaping Doom");

	// set handler to make the close button work
	LOCK_FUNCTION(close_button_handler);
	int callback = set_close_button_callback(close_button_handler);
	// load configuration
	configManager.load_config(CONFIG_FILENAME, gameState);

	// Make sure game continues to run when not in focus
	// REFERENCE: https://www.allegro.cc/manual/4/api/graphics-modes/set_display_switch_mode
	set_display_switch_mode(SWITCH_BACKGROUND);
	set_color_depth(32);
	// set GFX mode
	int gfx_mode = GFX_AUTODETECT_WINDOWED;
	if (gameState->fullscreen == 1) {
		gfx_mode = GFX_AUTODETECT_FULLSCREEN;
	}

	//set_color_depth(32);
	if (set_gfx_mode(gfx_mode, gameState->resolution_x, gameState->resolution_y, 0, 0) != 0) {
		return ERROR_ALLEGRO_GFX_CHANGE;
	}




	this->bitmaps_datafile = load_datafile("assets/bmps.dat");

	if (this->loadingBanner == NULL)
		loadingBanner = (BITMAP*)this->bitmaps_datafile[LOADING_BANNER_BMP].dat;
	if (this->menuBanner == NULL)
		menuBanner = (BITMAP*)this->bitmaps_datafile[BANNER_BMP].dat; 


	showLoadingScreen();





	// install sound 
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "") != 0) {
		allegro_message("ERROR: Failed to install sound.");
		return ERROR_ALLEGRO_SOUND_INIT;
	}
	set_volume(gameState->sound_volume * 25.5, gameState->music_volume * 25.5);


	soundManager = new SoundManager(gameState);
	soundManager->playBgMusic(1);

	//install mouse
	if (install_mouse() == -1) {
		allegro_message("ERROR: Failed to install Mouse.");
		return ERROR_ALLEGRO_KEYBOARD_INIT;
	}


	//load the custom mouse pointer
	cursorHand = (BITMAP*) this->bitmaps_datafile[CURSOR_HAND_BMP].dat;
	cursor = (BITMAP*)this->bitmaps_datafile[POINTER_BMP].dat;
	set_mouse_sprite(cursorHand);

	// set_mouse_sprite_focus(cursor->w / 2, cursor->h / 2); 

	//install keyboard
	if (install_keyboard() != 0) {
		allegro_message("ERROR: Failed to install Keyboard.");
		return ERROR_ALLEGRO_KEYBOARD_INIT;
	}

	this->font_datafile = load_datafile("assets/fonts.dat");

	this->headingFont = (FONT*) this->font_datafile[FONT_36_PCX].dat;
	this->textFont = (FONT*) this->font_datafile[FONT_TNR_16_PCX].dat;



	mainMenu = new MainMenu(gameState, (BITMAP*)this->bitmaps_datafile[MAINMENU_BUTTONS_BMP].dat, (BITMAP*)this->bitmaps_datafile[MAINMENU_BG_BMP].dat);
	settingsMenu = new SettingsMenu(gameState);
	gfxSettingsMenu = new GFXSettingsMenu(gameState, &configManager);
	soundSettingsMenu = new SoundSettingsMenu(gameState, &configManager);

	creditsScreen = new CreditsScreen(gameState); 
	gameHelpScreen = new GameHelpScreen(gameState);
	gameIntroScreen = new GameIntroScreen(gameState, &configManager);
	gameScreen = new GameScreen(gameState, soundManager, bitmaps_datafile);


	rest(1200);


	gameState->gameScreen = GAME_SCREEN_MAIN_MENU;
	gameState->pendingMouseClick = 0;
	return 0;
}
//game look
void GameManager::runGameLoop() {
	BITMAP* buffer = NULL;
	unsigned long start_time = 0, rest_time = 0, curr_time = 0;
	long frame_time = 0;
	unsigned int framesRendered = 0, game_fps = 0;


	while (!key[KEY_ESC] && !close_button_flag && !gameState->exitGame) {
		curr_time = clock();
		if (curr_time - start_time > 1000) {
			start_time = curr_time;
			game_fps = framesRendered;
			framesRendered = 0;
		}

		if (gameState->mouseHover == 1 && (mouse_b & 1) && gameState->pendingMouseClick == 0) {
			soundManager->playSound(SOUND_CLICK, 1000);
		}

		if ((mouse_b & 1) && gameState->mouseHover == 1) {
			gameState->pendingMouseClick = 1;
		}

		if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_M]) {
			muteActionTriggered = 1;
		} else if (!((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_M]) && muteActionTriggered==1) {
				muteActionTriggered = 0; 
				if (musicPlaying) {
					musicPlaying = 0;
					soundManager->stopBgMusic();
					this->soundVol = gameState->sound_volume;
					gameState->sound_volume = 0;
				}
				else {
					musicPlaying = 1;
					soundManager->playBgMusic(1);
					gameState->sound_volume = this->soundVol;
				}
		}



		// if gfx settings change need to create new buffer
		if (gameState->gfxSettingsUpdated) {
			gameState->gfxSettingsUpdated = 0;
			buffer = create_bitmap(gameState->resolution_x, gameState->resolution_y);
			show_mouse(screen);
		}
		 
		renderFrameToBuffer(buffer);

		if (gameState->mouseHover == 1 && pointerAsCursor == 0) {
			set_mouse_sprite(cursorHand);
			pointerAsCursor = 1;
		}
		else if (gameState->mouseHover == 0 && pointerAsCursor == 1) {
			set_mouse_sprite(cursor);
			pointerAsCursor = 0;
		}
		 
		//textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "Mouse position is %d, %d! FPS: %d", mouse_x, mouse_y, game_fps);

		
		//draw buffer to screen and clear buffer
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(buffer);
		frame_time = clock() - curr_time;
		rest_time = ((15 - frame_time) > 0) ? 15 - frame_time : 1;
		rest(rest_time);

		framesRendered++;
	};

}

void GameManager::exit() {

	if (loadingBanner != NULL)
		destroy_bitmap(loadingBanner);

	if (cursor != NULL)
		destroy_bitmap(cursor);

	if (cursorHand != NULL)
		destroy_bitmap(cursorHand);

	if (menuBanner != NULL)
		destroy_bitmap(menuBanner);

	if (menuBackground != NULL)
		destroy_bitmap(menuBackground);

	allegro_exit();
}



 // draws loading screen on the buffer
void GameManager::showLoadingScreen() { 
	 
	rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);
	float relative_width_banner_screen;

	if (SCREEN_W <= 640 || SCREEN_H <= 480) {
		relative_width_banner_screen = 0.6;
	}
	else {
		relative_width_banner_screen = 0.4;
	}

	masked_stretch_blit(loadingBanner, 
		screen, 
		0, 
		0, 
		loadingBanner->w, 
		loadingBanner->h, 
		(SCREEN_W)*(1-relative_width_banner_screen)/2, 
		(SCREEN_H - ((float)loadingBanner->h) / loadingBanner->w * (SCREEN_W) * (relative_width_banner_screen)) / 2,
		(SCREEN_W) * (relative_width_banner_screen), 
		((float)loadingBanner->h)/loadingBanner->w*(SCREEN_W) * (relative_width_banner_screen));
}


// passes on the control to the appropriate object for drawing the graphics and doing the require error handling
void GameManager::renderFrameToBuffer(BITMAP* buffer) {
	switch (gameState->gameScreen) {
		 
	case GAME_SCREEN_MAIN_MENU:
		gameState->gameScreen = mainMenu->showMainMenu(buffer);
		break;
	case GAME_SCREEN_SETTINGS:
		settingsMenu->drawSettingsMenuAndHandleInput(buffer, this->menuBanner, this->headingFont);
		break;
	case GAME_SCREEN_GFX_SETTINGS:
		gfxSettingsMenu->drawGfxMenuAndHandleInput(buffer, this->menuBanner, this->headingFont);
		break;
	case GAME_SCREEN_SOUND_SETTINGS:
		soundSettingsMenu->drawSoundSettingsMenuAndHandleInput(buffer, this->menuBanner, this->headingFont);
		break;  
	case GAME_SCREEN_CREDITS:
		creditsScreen->drawCreditsScreenAndHandleInput(buffer, this->menuBackground, this->menuBanner, this->headingFont, this->textFont);
		break;
	case GAME_SCREEN_START:
		gameIntroScreen->drawIntroScreenAndHandleInput(buffer, this->menuBackground, this->menuBanner, this->headingFont, this->textFont);
		break;
	case GAME_SCREEN_HELP:
		gameHelpScreen->drawHelpScreenAndHandleInput(buffer, this->menuBackground, (BITMAP*)this->bitmaps_datafile[HELP_BANNER_BMP].dat, this->headingFont, this->textFont, (char*)"CONTINUE");
		break;
	case GAME_SCREEN_PLAY:
		gameScreen->drawGameScreenAndHandleInput(buffer, this->menuBanner, this->headingFont, this->textFont);
	}

}