#include "Player.h"
#include "../mappy/mappyal.h"
#define PLAYER_W 30
#define PLAYER_H 37


Player::Player(BITMAP* spritesheet, SoundManager* soundManager, int initPosX, int initPosY, int initXonMap, int w, int h) : Sprite(spritesheet,
	w * SCALING_FACTOR_RELATIVE_TO_640, h * SCALING_FACTOR_RELATIVE_TO_640,
	3, 5, 15,
	12, 0, 0,
	0, 0,
	initPosX - w/2, initPosY - h, 1
	)
{
	// initialize variable
	this->soundManager = soundManager;
	this->posX = initPosX;
	this->posY = initPosY;
	this->xOnMap = initXonMap;
	// running animations = Frame 0 -> Frame 4 on the spritesheet
	this->animationFrames[ANIMATION_RUNNING][0] = 1;
	this->animationFrames[ANIMATION_RUNNING][1] = 5;

	// running animations = Frame 5 -> Frame 9 on the spritesheet
	this->animationFrames[ANIMATION_DYING][0] = 6;
	this->animationFrames[ANIMATION_DYING][1] = 10;

	// running animations = Frame 10 -> Frame 13 on the spritesheet
	this->animationFrames[ANIMATION_JUMPING][0] = 11;
	this->animationFrames[ANIMATION_JUMPING][1] = 14;
	currentAnimation = ANIMATION_JUMPING;
	currentFrame = this->animationFrames[currentAnimation][0];

}
Player::~Player()
{
	if (this->playerSprite)
		this->playerSprite->~Sprite();
}

bool Player::isAlive()
{
	return this->currently_alive;
}
void Player::alive(bool currently_alive)
{
	this->currently_alive = currently_alive;
}

bool Player::isJumping()
{
	return this->currently_jumping;
}
void Player::jumping(bool currently_jumping)
{
	this->currently_jumping = currently_jumping;
}

bool Player::isRunning()
{
	return currently_running;
}
void Player::running(bool currently_running)
{
	this->currently_running = currently_running;
}

int Player::getPosX()
{
	return this->posX;
}
void Player::setPosX(int posX)
{
	this->posX = posX;
}
int Player::getPosY()
{
	return this->posY;
}
void Player::setPosY(int posY)
{
	this->posY = posY;
}
void Player::update() 
{

}
int Player::get_x_on_map() 
{
	return xOnMap;
}

void Player::set_x_on_map(int x)
{
	this->xOnMap=x;
}

 

void Player::updateAnimation() {
	// change animation frame depending on the FPS
	if (clock() - lastFrameSwitchTime > 1000 / this->fps) {
		lastFrameSwitchTime = clock();
		currentFrame++;

		if ( currentFrame > animationFrames[currentAnimation][1] - 1) { 
			if (loop)
				currentFrame = animationFrames[currentAnimation][0];
			else
				currentFrame--;
		}

	}
}
void Player::draw(BITMAP* dest) {

	updatePos();
	drawframe(dest, currentFrame);
	updateAnimation();
	float x_onMap = get_x_on_map();


	int x1 = (int)(get_x_on_map() + w / 4.0) % (mapblockwidth * mapwidth);
	int y = (int)((this->yPos + this->h) * 960.0 / SCREEN_H);
	int x2 = (int)(get_x_on_map() + 3.0 * w / 4.0) % (mapblockwidth * mapwidth);
 
}

void Player::jump() 
{

	currently_jumping = true;
	isAscendingForJump = true; 
	jumpVelocity = MAX_JUMP_VELOCITY;
	currentAnimation = ANIMATION_JUMPING;
	currentFrame = animationFrames[currentAnimation][0];
	loop = false;

}
 
void Player::updatePos() 
{ 
		// change jump height and velocity
		jumpHeight += jumpVelocity;
		yPos -= jumpVelocity;

		// apply deceleration
		jumpVelocity -= 0.025 * MAX_JUMP_VELOCITY;
		int x1 = (int)(get_x_on_map() + w / 4.0) % (mapblockwidth * mapwidth);
		int y = (int)((this->yPos + this->h)*960.0/SCREEN_H);
		int y_mid = (int)((this->yPos + this->h/2) * 960.0 / SCREEN_H);
		int x2 = (int)(get_x_on_map() + 3.0 * w / 4.0) % (mapblockwidth * mapwidth);
		 
		if (isAlive() && jumpVelocity<0 && ((MapGetBlock(x1/mapblockwidth, y / mapblockheight)->tl )
			|| MapGetBlock(x2 / mapblockwidth, y / mapblockheight)->tl) && (y % mapblockheight < 20))
		{
			currently_jumping = false;
			jumpVelocity = 0;
			currentAnimation = ANIMATION_RUNNING;

			this->yPos -= (y % mapblockheight)*SCALING_FACTOR_RELATIVE_TO_1280;
			jumpHeight += (y % mapblockheight)*SCALING_FACTOR_RELATIVE_TO_1280; 
			loop = true;

		}
 

		if (jumpHeight < -30 )
		{
			currently_alive = 0;
			//rest(5000); 
		}

		if (isAlive() && (MapGetBlock(((x2+x1)/2) / mapblockwidth, y_mid / mapblockheight)->tl))
		{
			kill(); 
			this->soundManager->playSound(SOUND_BUZZER, 1000); 
		}
}

void Player::kill()
{	
	this->currently_alive = false;
	currentAnimation = ANIMATION_DYING; 
	currently_jumping = false;
	jumpVelocity = 0;
	loop = false;
}