#include "GameScreen.h" 
 
 
void thread_func(GameScreen* gs) {
	while (true)
	{
		gs->triggerReleases();
		rest(1000);
	}
}



GameScreen::GameScreen(GameState* gameState, SoundManager* soundManager, DATAFILE* bitmaps_datafile)
{
	this->gameState = gameState;
	this->soundManager = soundManager; 
	this->bitmaps_datafile = bitmaps_datafile;


	enemyGeneratorThread = new std::thread(&thread_func, this);

	MapLoad((char*)"assets/map1.FMP");
	//IMPORTANT player should be created only after mapload
	this->player = new Player((BITMAP*)this->bitmaps_datafile[ADVENTURER_RUN_BMP].dat , this->soundManager, SCREEN_W/10, SCREEN_H * (0.555), 128, 30*0.95, 37*0.95 );
	//create two virtual screens for infinite scrolling
	this->tmpGameScreens[0] = create_bitmap(TEMP_SCREEN_W, TEMP_SCREEN_H);
	this->tmpGameScreens[1] = create_bitmap(TEMP_SCREEN_W, TEMP_SCREEN_H); 
	 
}

GameScreen::~GameScreen()
{
	this->player->~Player();
	this->enemyGeneratorThread->~thread();
} 

void GameScreen::displayResultsBannerAndHandleInput(BITMAP* buffer, BITMAP* bannerBitmap, FONT* textFont)
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

void GameScreen::drawGameScreenAndHandleInput(BITMAP* buffer, BITMAP* bannerBitmap, FONT* headingFont, FONT* textFont) {
	// calculates how much time has passed in the game
	if (this->startTime == 0) {
		startTime = clock();
	}
	else {
		timeElasped = clock() - startTime;
	}

	// update the world scrolling related variables.
	if (this->player->isAlive()) {
		if(screenWrap_x_pending> gameScrollSpeed)
			screenWrap_x_pending -= gameScrollSpeed;
		else{
			xOffset += gameScrollSpeed;
			screenWrap_x_pending = 0;
		}
		this->gameState->currentScore += 0.5;
		
		this->player->set_x_on_map((this->player->get_x_on_map()+ gameScrollSpeed)%(mapblockwidth * mapwidth));
	}
	// if space is pressed make the player jump
	if (key[KEY_SPACE]) { 
		if (!player->isJumping()) { 
			player->jump();
			soundManager->playSound(SOUND_JUMP, 1000);
		}

	}

	// reset the game if required due to restart 
	if (this->gameState->needPlayerReset) 
	{
		this->player = new Player((BITMAP*)this->bitmaps_datafile[ADVENTURER_RUN_BMP].dat, this->soundManager, SCREEN_W / 10, SCREEN_H * (0.555), 128, 30 * .95, 37 * .95);
		xOffset = 0;
		screenWrap_x_pending = 0;
		yOffset = 0;
		this->gameState->needPlayerReset = 0;
		this->gameState->currentScore = 0;
		this->enemies.clear();
	}

	// calculate the offsets for the scrolling. These offset values are used when wrapping around the game world to create infinite scroll
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


	// draw parts of worlds on both the virtual game screens for infinite scrolling
	MapDrawBG(tmpGameScreens[currentScreen], xOffset, yOffset, 0, 0, TEMP_SCREEN_W - 1, TEMP_SCREEN_H - 1);
	MapDrawFG(tmpGameScreens[currentScreen], xOffset, yOffset, 0, 0, TEMP_SCREEN_W - 1, TEMP_SCREEN_H - 1, 0);

	// if end of the world has not reached only blit current screen to the buffer  
	if (screenWrap_x_pending<=0) {

		stretch_blit(tmpGameScreens[currentScreen], buffer, 0, 0, 1280, 960, 0, 0, SCREEN_W, SCREEN_H);
	}
	// if the end of the world has reached render parts of both virtual screens to ensure smooth infinite scroll
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

	// wait for the mutex to be available and then lock it
	std::lock_guard<std::mutex> lk(threadSafeMutex);
	
	//textprintf_centre(buffer, font, 100, 100, makecol(255, 0, 0), "THREAD: %d", counter_thread);

	renderEnemiesAndCheckForHits(buffer);
	cv.notify_one();


	// render the player
	this->player->draw(buffer);

	// open game help on Ctrl+H
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_H]) {
		gameState->gameScreen = GAME_SCREEN_HELP;
	} 


	// display score
	Utility::textout_magnified(buffer, headingFont, 30, 10,0.5, "SCORE: ", makecol(0, 0, 0), -1);
	Utility::textout_magnified(buffer, headingFont, 120, 10, 0.5, std::to_string((int)this->gameState->currentScore).c_str(), makecol(0, 0, 0), -1);
	
	if (!player->isAlive() && player->getY() > SCREEN_H)
	{
		displayResultsBannerAndHandleInput(buffer, bannerBitmap, headingFont);
	}

	



	//this->triggerReleases();
	
	//rest(100);
}
  

bool GameScreen::isGameRunningAndPlayerAlive() {
	return this->player!=nullptr && this->player->isAlive() && this->gameState->gameScreen == GAME_SCREEN_PLAY;
}


void GameScreen::triggerReleases()
{	 

	//release enemy depending on the randomly chosen release time
	if (clock() - lastEnemyReleaseTime > enemyReleaseDelay) {
		// lock mutex and if cannot lock give up and try again later
		std::unique_lock<std::mutex> lk(this->threadSafeMutex);
		// don't do anything until the player is alive and if player is alive proceed
		this->cv.wait(lk, [this] {return this->isGameRunningAndPlayerAlive(); });
		// spawn a new enemy
		this->enemies.push_back(new Enemy((BITMAP*)this->bitmaps_datafile[WIZARD_FLY_BMP].dat, (BITMAP*)this->bitmaps_datafile[FLAME_BMP].dat, (SCREEN_W * 1.3), ENEMY_SPAWN_HEIGHT, 24));
		// set random delay for next release
		this->enemyReleaseDelay = std::rand() % (2000) + 2000;
		
		lastEnemyReleaseTime = clock(); 
		// unlock mutex
		lk.unlock();
	}

	
}


void GameScreen::renderEnemiesAndCheckForHits(BITMAP* buffer) {
	//render enemies and check for any hits
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->renderEnemy(buffer);

		Sprite* enemySprite = enemies[i]->getSprite();

		if (enemySprite->collided(buffer, enemySprite->getW() / 7, enemySprite->getH() / 4, (Sprite*)player, player->getH() / 5, player->getW() / 6))
		{
			player->kill();
			soundManager->playSound(SOUND_BUZZER, 1000);
		}

		if (enemySprite->getX() + enemySprite->getH() < 0) {
			enemies[i]->~Enemy();
			enemies.erase(enemies.begin() + i--);
		}
	}

}