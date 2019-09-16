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
	 
}

GameScreen::~GameScreen()
{
	this->player->~Player();
} 

void GameScreen::displayResultsBannerAndHandleInput(BITMAP* buffer, FONT* textFont)
{

	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.5, "RESULTS", COLOR_TEXT, -1);


		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.55, "SCORE", makecol(255, 255, 255), -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, .7, std::to_string((int)this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .4, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .4, "RESTART GAME", restartGameButtonColor, -1);


	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.75, "RESULTS", COLOR_TEXT, -1);


		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.65, "SCORE", makecol(255, 255, 255), -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, .9, std::to_string((int)this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .4, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .4, "RESTART GAME", restartGameButtonColor, -1);

	

	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 1, "RESULTS", COLOR_TEXT, -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.75, "SCORE", makecol(255,255,255), -1); 
		 
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, 1, std::to_string((int)this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);
		 


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

	if ((true || key[KEY_RIGHT]) && this->player->isAlive()) {
		if(screenWrap_x_pending> gameScrollSpeed)
			screenWrap_x_pending -= gameScrollSpeed;
		else{
			xOffset += gameScrollSpeed;
			screenWrap_x_pending = 0;
		}
		this->gameState->currentScore += 0.5;
		
		this->player->set_x_on_map((this->player->get_x_on_map()+ gameScrollSpeed)%(mapblockwidth * mapwidth));
	}

	if (key[KEY_SPACE]) { 
		if (!player->isJumping())
			player->jump();
	}


	if (this->gameState->needPlayerReset) 
	{
		this->player = new Player(SCREEN_W / 10, SCREEN_H * (0.555), 128, 30 * 1.2, 37 * 1.2);
		xOffset = 0;
		screenWrap_x_pending = 0;
		yOffset = 0;
		this->gameState->needPlayerReset = 0;
		this->gameState->currentScore = 0;
		this->enemies.clear();
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


	//textprintf(buffer, font, 20, 80, makecol(255,255,255), "xOffset: %d scrn_wrap x: %d tile: %d enemiesAlive: %d", xOffset, screenWrap_x_pending,(int)blockdata->tl, enemies.size());
		

	//textprintf(buffer, font, 20, 40, makecol(255, 255, 255), "x: %d  y: %d",  (int)(mouse_x/(64*SCALING_FACTOR_RELATIVE_TO_1280)), (int)(mouse_y / (64 * SCALING_FACTOR_RELATIVE_TO_1280)));
	//textprintf(buffer, font, 20, 60, makecol(255, 255, 255), "x: %d  y: %d", (int)(mouse_x), (int)(mouse_y));

	 





	//render enemies and check for any hits
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->renderEnemy(buffer); 

		Sprite* enemySprite = enemies[i]->getSprite(); 

		if (player->collided(buffer, player->getH() / 6, player->getW() / 6, enemySprite, enemySprite->getH() / 6, enemySprite->getW() / 7))
		{
			player->kill();
		}



		if (enemySprite->getX() + enemySprite->getH() < 0) {  
			enemies[i]->~Enemy();
			enemies.erase(enemies.begin() + i--);
		}
	}
















	this->player->draw(buffer);

	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_H]) {
		gameState->gameScreen = GAME_SCREEN_HELP;
	} 



	Utility::textout_magnified(buffer, headingFont, 30, 10,0.5, "SCORE: ", makecol(0, 0, 0), -1);
	Utility::textout_magnified(buffer, headingFont, 120, 10, 0.5, std::to_string((int)this->gameState->currentScore).c_str(), makecol(0, 0, 0), -1);




	if(!player->isAlive() && player->getY()> SCREEN_H)
	{
		displayResultsBannerAndHandleInput(buffer, headingFont);
	}


	this->triggerReleases();
	//rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H / 15, makecol(77, 196, 240)); 
	
	//rest(100);
}
 
/*
void GameScreen::checkHits(BITMAP* buffer)
{
	Sprite* mainSprite;
	Sprite* otherSprite;


}
	*/

void GameScreen::triggerReleases()
{	 



	//release enemy
	if (clock() - lastEnemyReleaseTime > enemyReleaseDelay) {
		 
		this->enemies.push_back(new Enemy(66 * SCALING_FACTOR_RELATIVE_TO_1280, 99 * SCALING_FACTOR_RELATIVE_TO_1280, (SCREEN_W*1.3), ENEMY_SPAWN_HEIGHT, 24));
		this->enemyReleaseDelay = std::rand() % (2000) + 2000;

		lastEnemyReleaseTime = clock(); 
	}

	
}