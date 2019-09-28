#include "Enemy.h"

Enemy::Enemy( int posX, int posY, int fps)
{
	this->enemyType = std::rand() % (3);
	if (this->enemyType > 1) {

		this->enemyH = 48 * SCALING_FACTOR_RELATIVE_TO_1280;
		this->enemyW = 96 * SCALING_FACTOR_RELATIVE_TO_1280;
		posY *= 1.03;

		this->enemySprite = new Sprite(
			load_bitmap("assets/sprites/flame.bmp", NULL),
			enemyW, enemyH, // w, h
			1, 4,		// ssheetNumRows, ssheetNumCols
			4, 12,		// numOfFrames ,  fps
			7*SCALING_FACTOR_RELATIVE_TO_1280, 0, 1, 0,	// velX,  velY,  xDelay,  yDelay,
			posX, posY
			//(SCREEN_W) / 4, (SCREEN_H * (15.0/29)
		);
	
	}
	else {

		this->enemyH = 99 * SCALING_FACTOR_RELATIVE_TO_1280;
		this->enemyW = 66 * SCALING_FACTOR_RELATIVE_TO_1280; 

		this->enemySprite = new Sprite(
			load_bitmap("assets/sprites/wizard-fly.bmp", NULL),
			enemyW, enemyH, // w, h
			1, 3,		// ssheetNumRows, ssheetNumCols
			3, 12,		// numOfFrames ,  fps
			7 * SCALING_FACTOR_RELATIVE_TO_1280, 0, 1, 0,	// velX,  velY,  xDelay,  yDelay,
			posX, posY
			//(SCREEN_W) / 4, (SCREEN_H * (15.0/29)
		);

	}
}


Enemy::~Enemy() 
{
	this->enemySprite->~Sprite();
}

void Enemy::renderEnemy(BITMAP* buffer)
{
	this->enemySprite->draw(buffer);
	this->enemySprite->move(SPRITE_MOVE_LEFT);
}

Sprite* Enemy::getSprite()
{
	return enemySprite;
}