#include "GameScreen.h" 


GameScreen::GameScreen(GameState* gameState, SoundManager* soundManager)
{
	this->gameState = gameState;
	this->soundManager = soundManager; 
	 

	MapLoad((char*)"assets/map1.FMP");
	//IMPORTANT player should be created only after mapload
	this->player = new Player(SCREEN_W/10, SCREEN_H * (0.555), 128, 30*1.2, 37*1.2 );
	this->bannerBitmap = load_bitmap("assets/ui-elem/banner.bmp", NULL);
	this->tmpGameScreens[0] = create_bitmap(TEMP_SCREEN_W, TEMP_SCREEN_H);
	this->tmpGameScreens[1] = create_bitmap(TEMP_SCREEN_W, TEMP_SCREEN_H);
	//this->playerShip = new PlayerShip(&this->bullets, 100, this->soundManager);  
	this->enemy = new Enemy(44, 66, (SCREEN_W) / 4, (int)(SCREEN_H * (15.0 / 29)),24);
	  
	//srand(time(NULL)); 
	//this->mineReleaseDelay = std::rand() % (5000);

}

GameScreen::~GameScreen()
{
	this->player->~Player();
}
/*
void GameScreen::displayHealthBarAndScore(BITMAP* buffer, FONT* customFont) {

	
	int labelsX = PLAY_REGION_W + SCREEN_W / 30;
	int healthLabelY = 386 * SCALING_FACTOR_RELATIVE_TO_1280;
	int healthBarY = healthLabelY + 50 * SCALING_FACTOR_RELATIVE_TO_1280;
	int healthBarWidth = SCREEN_W / 5;
	int healthBarHeight = 25 * SCALING_FACTOR_RELATIVE_TO_1280;


	Utility::textout_magnified(buffer, customFont, labelsX, healthLabelY, 0.5*SCALING_FACTOR_RELATIVE_TO_1280, "HEALTH", makecol(11, 255, 255), -1);

	rectfill(buffer, labelsX , healthBarY, labelsX + healthBarWidth, healthBarY + healthBarHeight, makecol(0, 0, 0));
	if(this->gameState->health != 0)
		rectfill(buffer, labelsX, healthBarY, labelsX + (healthBarWidth*((1.0*this->gameState->health)/100)), healthBarY + healthBarHeight, makecol(0, 255, 0)); 

	Utility::textout_magnified(buffer, customFont, labelsX, 486 * SCALING_FACTOR_RELATIVE_TO_1280, 0.5 * SCALING_FACTOR_RELATIVE_TO_1280, "YOUR SCORE", makecol(11, 255, 255), -1);

	Utility::textout_magnified(buffer, font, labelsX, 530 * SCALING_FACTOR_RELATIVE_TO_1280, 2 * SCALING_FACTOR_RELATIVE_TO_1280, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


}*/

void GameScreen::displayResultsBannerAndHandleInput(BITMAP* buffer, FONT* textFont)
{

	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.5, "RESULTS", COLOR_TEXT, -1);


		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.55, "SCORE", makecol(255, 255, 255), -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, .7, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .4, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .4, "RESTART GAME", restartGameButtonColor, -1);


	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.75, "RESULTS", COLOR_TEXT, -1);


		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.65, "SCORE", makecol(255, 255, 255), -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, .9, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .4, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .4, "RESTART GAME", restartGameButtonColor, -1);

	

	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 1, "RESULTS", COLOR_TEXT, -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.75, "SCORE", makecol(255,255,255), -1); 
		 
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, 1, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);
		 


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .5, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .5, "RESTART GAME", restartGameButtonColor, -1);


	} 
	exitToMainMenuButtonColor = restartGameButtonColor = OPTION_COLOR;


	gameState->mouseHover = 0;

	// handle clicks on the apply Button
	if (Utility::mouseInTheBoundingBox(exitToMainMenuButton)) {
		gameState->mouseHover = 1;
		exitToMainMenuButtonColor = OPTION_COLOR_HOVERED;

		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
			// exit to Main Menu 

			gameState->needPlayerReset = 1;

			gameState->gameScreen = GAME_SCREEN_MAIN_MENU;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300); 
		}
	}
	// handle clicks on the back button
	else if (Utility::mouseInTheBoundingBox(restartGameButton)) {
		gameState->mouseHover = 1;
		restartGameButtonColor = OPTION_COLOR_HOVERED;

			if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
				gameState->needPlayerReset = 1;

				gameState->pendingMouseClick = 0;

				rest(300); 
			}
	}




	if (key[KEY_R]) {
		gameState->needPlayerReset = 1;
	}

	
}

void GameScreen::drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont) {
	if (this->startTime == 0) {
		startTime = clock();
	}
	else {
		timeElasped = clock() - startTime;
	}

	if (key[KEY_RIGHT] && this->player->isAlive()) {
		if(screenWrap_x_pending>10)
			screenWrap_x_pending -= 10;
		else{
			xOffset += 10;
			screenWrap_x_pending = 0;
		}

		
		this->player->set_x_on_map((this->player->get_x_on_map()+10)%(mapblockwidth * mapwidth));
	}

	if (key[KEY_SPACE]) { 
		if (!player->isJumping())
			player->jump();
	}



	if (xOffset < 0) xOffset = 0;
	if (xOffset > (mapwidth * mapblockwidth - 1280)) {
		//xOffset = mapwidth * mapblockwidth - 1280;
		xOffset = 0;
		currentScreen = !currentScreen;
		screenWrap_x_pending = 1280;
	}
	if (yOffset < 0)
		yOffset = 0;
	if (yOffset > (mapheight * mapblockheight - 960))
		yOffset = mapheight * mapblockheight - 960;



	MapDrawBG(tmpGameScreens[currentScreen], xOffset, yOffset, 0, 0, TEMP_SCREEN_W - 1, TEMP_SCREEN_H - 1);
	MapDrawFG(tmpGameScreens[currentScreen], xOffset, yOffset, 0, 0, TEMP_SCREEN_W - 1, TEMP_SCREEN_H - 1, 0);
	 
	//blit(tmpGameScreen, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	if (screenWrap_x_pending<=0) {

		stretch_blit(tmpGameScreens[currentScreen], buffer, 0, 0, 1280, 960, 0, 0, SCREEN_W, SCREEN_H);
	}
	else {
		
		
		//rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));


		stretch_blit(
			tmpGameScreens[!currentScreen], buffer, 
			TEMP_SCREEN_W-screenWrap_x_pending, 0,
			screenWrap_x_pending, TEMP_SCREEN_H,
			0, 0, 
			screenWrap_x_pending * SCALING_FACTOR_RELATIVE_TO_1280+1, SCREEN_H);

		stretch_blit(
			tmpGameScreens[currentScreen], buffer,
			0, 0,
			TEMP_SCREEN_W - screenWrap_x_pending, TEMP_SCREEN_H,
			screenWrap_x_pending * SCALING_FACTOR_RELATIVE_TO_1280 , 0,
			(TEMP_SCREEN_W - screenWrap_x_pending) * SCALING_FACTOR_RELATIVE_TO_1280, SCREEN_H);


	}

	BLKSTR* blockdata;
	blockdata = MapGetBlockInPixels(this->player->get_x_on_map(),SCREEN_H*9/15);


	textprintf(buffer, font, 20, 80, makecol(255,255,255), "xOffset: %d scrn_wrap x: %d tile: %d", xOffset, screenWrap_x_pending,(int)blockdata->tl);
		

	textprintf(buffer, font, 20, 40, makecol(255, 255, 255), "x: %d  y: %d",  (int)(mouse_x/(64*SCALING_FACTOR_RELATIVE_TO_1280)), (int)(mouse_y / (64 * SCALING_FACTOR_RELATIVE_TO_1280)));
	textprintf(buffer, font, 20, 60, makecol(255, 255, 255), "x: %d  y: %d", (int)(mouse_x), (int)(mouse_y));

	 
	enemy->renderEnemy(buffer);

	this->player->draw(buffer);

	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_H]) {
		gameState->gameScreen = GAME_SCREEN_HELP;
	} 



	Utility::textout_magnified(buffer, textFont, 20, 10, 1, "SCORE: ", makecol(255, 255, 255), -1);
	Utility::textout_magnified(buffer, textFont, 100, 10, 1, std::to_string((int)this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


	//rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H / 15, makecol(77, 196, 240)); 
	
	//rest(100);
}

/*
void GameScreen::checkHits(BITMAP* buffer)
{
	Sprite* mainSprite;
	Sprite* otherSprite;


}

void GameScreen::triggerReleases()
{	 



	//release enemy
	if (clock() - lastEnemyReleaseTime > enemyReleaseDelay) {

		int shipType = (std::rand() % (5)<2) ? ENEMY_SHIP_SMALL : ENEMY_SHIP_BIG;
		this->enemyShips.push_back(new EnemyShip(shipType, &this->bullets, (std::rand() % ((int)(PLAY_REGION_W - 200 * SCALING_FACTOR_RELATIVE_TO_1280))), -55 * SCALING_FACTOR_RELATIVE_TO_1280, (shipType == ENEMY_SHIP_SMALL)?0.66:0.33));
		this->enemyReleaseDelay = std::rand() % (5000) + 2000;

		lastEnemyReleaseTime = clock(); 
	}

	

	*/