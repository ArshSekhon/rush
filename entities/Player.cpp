#include "Player.h"
#include "../mappy/mappyal.h"
#define PLAYER_W 30
#define PLAYER_H 37


Player::Player(int initPosX, int initPosY, int initXonMap, int w, int h) : Sprite(load_bitmap("assets/sprites/adventurer-run.bmp",NULL),
	w * SCALING_FACTOR_RELATIVE_TO_640, h * SCALING_FACTOR_RELATIVE_TO_640,
	3, 5, 15,
	12, 0, 0,
	0, 0,
	initPosX - w/2, initPosY - h, 1
	)
{
 
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
	return this->alive;
}
void Player::isAlive(bool alive)
{
	this->alive = alive;
}

bool Player::isJumping()
{
	return this->jumping;
}
void Player::isJumping(bool jumping)
{
	this->jumping = jumping;
}

bool Player::isRunning()
{
	return running;
}
void Player::isRunning(bool running)
{
	this->running = running;
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

void Player::render(BITMAP* buffer)
{ 
	int playerHeight = PLAYER_H * SCALING_FACTOR_RELATIVE_TO_1280;
	int playerWidth = PLAYER_W * SCALING_FACTOR_RELATIVE_TO_1280;


	int playerX = posX - playerHeight / 2;
	int playerY = posY - playerHeight;

	textprintf(buffer, font, 350, 20, makecol(255, 255, 255), "x: %d y:%d h:%d w:%d map on x: %d", playerX, playerY, playerHeight, playerWidth, xOnMap);
	//rectfill(buffer, playerX, playerY, playerX+playerWidth, playerY+playerHeight, makecol(0,0,0));
}


void Player::updateAnimation() {
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

	textprintf(dest, font, 0, 100, makecol(255, 255, 255), "jumpHeight: %f jumpVelocity:%f xy1: %f %f xy2: %f %f y_block: %d", jumpHeight, jumpVelocity, get_x_on_map() - w / 2.0, (this->yPos) , get_x_on_map() + w / 2.0, (this->yPos), (y % mapblockheight ));


	textprintf(dest, font, 100, 200, makecol(255, 255, 255), "x1: %f y1: %f x2: %f y2: %f xOnMap: %f", this->xPos-w/2.0, (this->yPos+this->h), this->xPos + w / 2.0, (this->yPos+this->h));


	if(isAlive())
		textprintf(dest, font, 100, 250, makecol(255, 255, 255), "onFloor1: %d onFloor2: %d Mouse: %d", MapGetBlockInPixels(x1,y)->tl , MapGetBlockInPixels(x2, y)->tl);


	putpixel(dest, get_x_on_map() - w / 2, (posY + h), makecol(255, 0, 0));
	putpixel(dest, get_x_on_map() + w / 2, (posY + h), makecol(255, 0, 0));
}

void Player::jump() 
{

	jumping = true;
	isAscendingForJump = true; 
	jumpVelocity = MAX_JUMP_VELOCITY;
	currentAnimation = ANIMATION_JUMPING;
	currentFrame = animationFrames[currentAnimation][0];
	loop = false;

}
 
void Player::updatePos() 
{ 



		jumpHeight += jumpVelocity;
		yPos -= jumpVelocity;


		jumpVelocity -= 0.025 * MAX_JUMP_VELOCITY;
		int x1 = (int)(get_x_on_map() + w / 4.0) % (mapblockwidth * mapwidth);
		int y = (int)((this->yPos + this->h)*960.0/SCREEN_H);
		int y_mid = (int)((this->yPos + this->h/2) * 960.0 / SCREEN_H);
		int x2 = (int)(get_x_on_map() + 3.0 * w / 4.0) % (mapblockwidth * mapwidth);
		 
		if (isAlive() && jumpVelocity<0 && ((MapGetBlock(x1/mapblockwidth, y / mapblockheight)->tl )
			|| MapGetBlock(x2 / mapblockwidth, y / mapblockheight)->tl) && (y % mapblockheight < 20))
		{
			jumping = false;
			jumpVelocity = 0;
			currentAnimation = ANIMATION_RUNNING;

			this->yPos -= (y % mapblockheight)*SCALING_FACTOR_RELATIVE_TO_1280;
			jumpHeight += (y % mapblockheight)*SCALING_FACTOR_RELATIVE_TO_1280;



			loop = true;

		}




		if (jumpHeight < -30 )
		{
			alive = 0; 
			//rest(5000);

		}

		if (isAlive() && (MapGetBlock(((x2+x1)/2) / mapblockwidth, y_mid / mapblockheight)->tl))
		{
			alive = 0;
			loop = false;
			currentAnimation = ANIMATION_DYING;

			jumping = false;
			jumpVelocity = 0;
			loop = false;

		}
}